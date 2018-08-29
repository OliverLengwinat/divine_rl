import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object, KinematicObserver, BaseObserver, ReplayMemory
from src.proto import world_pb2, commons_pb2, object_pb2
from google.protobuf import text_format
from viewer.viewer import Viewer
import threading
import time
import importlib


# TODO: add start method
class Environment(threading.Thread):
	def __init__(self, path, dt = 0.25):
		threading.Thread.__init__(self)
		self.dt = dt
		self.world = World()
		self.observer = KinematicObserver()
		self.viewer = Viewer()
		self.proto_path = path
		self.load_world(path)
	
	@property
	def agents(self):
		return self.world.get_agents()

	@property
	def objects(self):
		return self.world.get_objects()

	def set_observer(self, observer):
		observer.set_world(self.world)
		self.observer = observer

	def collides(self, obj):
		self.world.collides(obj)
	
	def observe(self, step):
		state_history =  self.observer.observe(step)
		return state_history

	def reset(self):
		self.world = World()
		self.load_world(self.proto_path)

	def load_proto(self, path):
		f = open(path, 'r')
		world = world_pb2.World()
		text_format.Parse(f.read(), world)
		f.close()
		return world

	def get_xy_list(self, rep):
		ret = []
		for e in rep.e:
			ret.append([e.x, e.y])
		return ret

	def get_list(self, rep):
		ret = []
		for e in rep.e:
			ret.append(e)
		return ret

	def create_polygon(self, list):
		poly = Polygon()
		for p in list:
			poly.append(Point(p[0],p[1]))
		return poly

	def load_world(self, path):
		world = self.load_proto(path)
		for obj in world.object:
			shape = self.get_xy_list(obj.shape)
			if obj.type == object_pb2.Object.AGENT:
				agent = Agent()
				agent.set_type(obj.type)
				agent.set_shape(self.create_polygon(shape))
				kinematic_model = eval(obj.model.name) 
				kinematic_model.set_state( np.array([self.get_list(obj.model.state)]) )
				agent.set_pose(kinematic_model.get_pose())
				agent.set_kinematic_model(kinematic_model)
				self.world.add_object(agent)
			elif obj.type == object_pb2.Object.OBJECT:
				tmp_obj = Object()
				tmp_obj.set_type(obj.type)
				tmp_obj.set_shape(self.create_polygon(shape))
				self.world.add_object(tmp_obj)

	def debug_world_plot(self):
		self.viewer.draw_world(self.world)

	def debug_agents_plot(self):
		for agent in self.agents:
			polygon = agent.get_transformed_shape()
			self.viewer.draw_polygon(polygon)

	def debug_plot_show(self):
		self.viewer.show()

	def sample_memory(self, N = 500):
		return self.observer.get_replay_memory().sample(N)


if __name__ == '__main__':

	# setup environment
	env = Environment("tests/python/world.pb.txt")
	obs = KinematicObserver()
	env.set_observer(obs)
	env.debug_world_plot()

	# simulate and plot
	u = np.array([[0.5,0.5]])
	for frame in range(1,20):
		for agent in env.agents:
			env.observe(agent.step(u, 0.25))
		env.debug_agents_plot() # caution slow!

		# reset after 10 time steps
		if frame % 10 == 0:
			env.reset()
			u = np.array([[-0.5,-0.5]])

	# show plot
	env.debug_plot_show()
	
	# sample 10 items from replay memory 
	print(env.sample_memory(10))