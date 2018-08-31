import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object, KinematicObserver, BaseObserver, ReplayMemory
from src.proto import world_pb2, commons_pb2, object_pb2
from google.protobuf import text_format
from viewer.viewer import Viewer
import threading
import time
import random

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

	def collides(self, obj):
		self.world.collides(obj)

	def reset(self):
		self.world.reset()
		self.load_world(self.proto_path)

	def load_proto(self, path):
		f = open(path, 'r')
		world = world_pb2.World()
		text_format.Parse(f.read(), world)
		f.close()
		return world

	def get_nested_list(self, rep):
		ret = []
		for e1 in rep.e:
			tmp_ret = []
			for e2 in e1.e:
				tmp_ret.append(e2)
			ret.append(tmp_ret)
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
			shape = self.get_nested_list(obj.shape)# multiple states with each state containing 2x e
			if obj.type == object_pb2.Object.AGENT:
				agent = Agent()
				agent.set_type(obj.type)
				agent.set_shape(self.create_polygon(shape))
				shape_offset = self.get_list(obj.shape.center)
				agent.set_shape_offset(Point(shape_offset[0], shape_offset[1]))
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
			elif obj.type == object_pb2.Object.BOUNDING_BOX:
				bounding_box = self.create_polygon(shape)
				self.world.set_bounding_box(bounding_box)

	def debug_world_plot(self):
		self.viewer.draw_world(self.world, color='gray')

	def debug_agents_plot(self):
		for agent in self.agents:
			polygon = agent.get_transformed_shape()
			self.viewer.draw_polygon(polygon, color='blue')

	def debug_plot_show(self):
		self.viewer.show()



if __name__ == '__main__':

	# setup environment
	env = Environment("tests/python/world.pb.txt")
	env.debug_world_plot()

	# setup obsever
	obs = KinematicObserver()
	obs.set_world(env.world)

	# run environment
	for i in range(0, 8):
		u = np.array([[random.uniform(-0.5, 0.5), 0.0]])
		running = True
		while running:
			for agent in env.agents:
				sh = obs.observe(agent.step(u, 0.25))
				if sh[1].is_final():
					running = False
					env.reset()
			
			# plot agents
			env.debug_agents_plot()

	# show and sample
	env.debug_plot_show()
	print(obs.memory.sample(10))


	