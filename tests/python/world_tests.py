import unittest
import numpy as np
#import matplotlib.pyplot as plt
from divine_rl.commons import Point, Pose, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object
from src.proto import world_pb2, commons_pb2, object_pb2

class WorldTests(unittest.TestCase):

	def test_agents(self):
		state = np.array([[0,0,0,5]])
		u = np.array([[0.5,5.5]])
		
		model = SingleTrackModel()

		w = World()

		# this is the agent config
		# a = Agent(protobuf_agent)

		a = Agent()
		a.set_pose(Pose(0,0,0.0))
		model.set_state(state)

		poly = Polygon()
		poly.append(Point(3.85, 0))
		poly.append( Point(3.772, -0.495) )
		poly.append(Point(3.426, -0.887))
		poly.append(Point(2.914, -0.956))
		poly.append(Point(1.457, -0.956))
		poly.append(Point(0, -0.956))
		poly.append(Point(-0.512, -0.886))
		poly.append(Point(-1.02, -0.589))
		poly.append(Point(-1.119, 0))
		poly.append(Point(-1.02, 0.589))
		poly.append(Point(-0.512, 0.886))
		poly.append(Point(0, 0.956))
		poly.append(Point(1.457, 0.956))
		poly.append(Point(2.914, 0.956))
		poly.append(Point(3.426, 0.887))
		poly.append(Point(3.772, 0.495))
		poly.append(Point(3.85, 0))


		a.set_shape(poly)
		a.set_kinematic_model(model)

		# end agent conf

		self.__class__.agent = a
		self.__class__.polygon = poly

		pts = a.get_transformed_shape().to_numpy()
		#plt.plot(pts[:,0], pts[:,1])
		
		for i in range(0, 10):
			#a.step(u, 0.25)
			pts = a.get_transformed_shape().to_numpy()
		"""
			plt.plot(pts[:,0], pts[:,1])

		plt.axis('equal')
		plt.show()
		"""
		

	def test_objects(self):
		# obj = Object(protobuf_object)
		obj = Object()
		obj.set_shape(self.__class__.polygon)
		print(obj.get_shape().to_numpy())
		self.__class__.object = obj
	


	def test_world(self):


		w = World()
		#w.load_from_proto()
	
		w.add_object(self.__class__.agent)
		w.add_object(self.__class__.object)
		
		objects = w.get_objects()
		u = np.array([[0.5,1.5]])

		agents = w.get_agents()

		for i in range(0,20):
			for a in agents:
				a.step(u, 0.25)
				status = w.collides(a)
				print(status)


		objects = w.get_objects()

		print(objects[0].get_kinematic_model().get_state())
		print(objects)
		print("hello world")
		
		
	
if __name__ == '__main__':
	unittest.main()