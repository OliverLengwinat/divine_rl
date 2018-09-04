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
		a.set_world(w)

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
		w.add_object(a)
		
		self.__class__.world = w

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



	def test_world(self):


		w = self.__class__.world

		
		objects = w.get_objects()
		u = np.array([[0.5,1.5]])

		agents = w.get_agents()

		for i in range(0,20):
			for a in agents:
				a.step(u, 0.25)
				status = w.collides(a.get_id())
				print(status)


		objects = w.get_objects()

		print(objects[0].get_kinematic_model().get_state())
		print(objects)
		

	
if __name__ == '__main__':
	unittest.main()