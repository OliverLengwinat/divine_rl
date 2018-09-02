import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel, TrippleIntModel
from divine_rl.world import World, Agent, Object, KinematicObserver, BaseObserver, ReplayMemory, RoadNetwork
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
		
		road_network = RoadNetwork()
		# load reference lines
		for line in world.line_segment:

			# add line segments
			ref_line = Line()
			for segment in line.line_segment:
				if segment.type == commons_pb2.EdgeInfo.LINE:
					p_start = Point(segment.start_point.e[0], segment.start_point.e[1])
					p_end = Point(segment.end_point.e[0], segment.end_point.e[1])
					ref_line.append(road_network.create_line(p_start, p_end))
				elif segment.type == commons_pb2.EdgeInfo.BEZIER:
					p_0 = Point(segment.start_point.e[0], segment.start_point.e[1])
					p_1 = Point(segment.start_point.e[2], segment.start_point.e[3])
					p_2 = Point(segment.end_point.e[0], segment.end_point.e[1])
					p_3 = Point(segment.end_point.e[2], segment.end_point.e[3])
					ref_line.append(road_network.create_bezier(p_0, p_1, p_2, p_3))
			road_network.set_line_segment(line.id, ref_line)

		# add reference roads
		for road in world.reference_line:
			ids = []
			for idx in road.segment_id:
				ids.append(idx)
			road_network.add_reference_road(road.id, ids)
		self.world.set_road_network(road_network)
		
		# load objects
		for obj in world.object:
			shape = self.get_nested_list(obj.shape)# multiple states with each state containing 2x e
			if obj.type == object_pb2.Object.AGENT:
				agent = Agent()
				agent.set_type(obj.type)
				agent.set_shape(self.create_polygon(shape))
				shape_offset = self.get_list(obj.shape.center)
				agent.set_shape_offset(Point(shape_offset[0], shape_offset[1]))
				kinematic_model = eval(obj.model.name)
				kinematic_model.set_state( np.array([self.get_list(obj.model.state)]))

				if obj.HasField('reference_line_id'):
					#kinematic_model.set_reference_line(self.world.get_reference_line(obj.reference_line_id))
					kinematic_model.set_road_network(road_network)
					kinematic_model.set_reference_road_id(obj.reference_line_id)

				agent.set_pose(kinematic_model.get_pose())
				agent.set_kinematic_model(kinematic_model)
				agent.set_reward(obj.reward)
				agent.set_id(obj.id)
				self.world.add_object(agent)
			elif obj.type == object_pb2.Object.OBJECT:
				tmp_obj = Object()
				tmp_obj.set_type(obj.type)
				tmp_obj.set_shape(self.create_polygon(shape))
				tmp_obj.set_reward(obj.reward)
				tmp_obj.set_id(obj.id)
				self.world.add_object(tmp_obj)
			elif obj.type == object_pb2.Object.BOUNDING_BOX:
				bounding_box = self.create_polygon(shape)
				self.world.set_bounding_box(bounding_box)

	def debug_world_plot(self):
		self.viewer.draw_world(self.world, color='gray')

	def debug_agents_plot(self):
		for agent in self.agents:
			self.viewer.draw_point(agent.get_pose(), color='blue')
			polygon = agent.get_transformed_shape()
			self.viewer.draw_polygon(polygon, color='blue')

	def debug_plot_show(self):
		self.viewer.show()



if __name__ == '__main__':

	# setup environment
	env = Environment("tests/python/structured_world.pb.txt")
	env.debug_world_plot()

	# setup obsever
	obs = KinematicObserver()
	obs.set_world(env.world)

	# run environment
	for i in range(0, 1):
		#u = np.array([[random.uniform(-0.5, 0.5), 0.0]])
		u = np.array([[random.uniform(-0.0, 0.0)]])
		running = True

		for i in range(0,20):
			for agent in env.agents:
				# state = obs.get_state(agent, env.world) 
				result = obs.observe(agent.step(u, 0.25))
				if result.is_final:
					print(result.state, result.action, result.next_state, result.reward)
					running = False
					env.reset()
			# plot agents
			env.debug_agents_plot()

	# show plots
	env.debug_plot_show()

	# replay memory
	replay_memory = obs.memory.sample(50)
	replay_batch = zip(replay_memory.states, replay_memory.actions, replay_memory.next_states, replay_memory.rewards)

	

	