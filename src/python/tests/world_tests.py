import unittest
import numpy as np
#import matplotlib.pyplot as plt
from divine_rl.commons import Point, Pose, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object, BaseType


class WorldTests(unittest.TestCase):

	def test_agents(self):
		state = np.array([[0,0,0,5]])
		u = np.array([[0.5,0.5]])
		
		model = SingleTrackModel()

		w = World()

		a = Agent(0)
		a.set_pose(Pose(0,0,0.0))
		a.set_state(state)

		poly = Polygon() 
		poly.append(Point(-1.0, -1.0))
		poly.append(Point(2.5, -1.0))
		poly.append(Point(2.5, 1.0))
		poly.append(Point(-1.0, 1.0))
		poly.append(Point(-1.0, -1.0))

		a.set_shape(poly)
		a.set_kinematic_model(model)

		self.__class__.agent = a
		self.__class__.polygon = poly

		
		for i in range(0, 10):
			a.step(u, 0.25)
			pts = a.get_transformed_shape().to_numpy()
		
		"""
			plt.plot(pts[:,0], pts[:,1])

		plt.axis('equal')
		plt.show()
		"""

	def test_objects(self):
		obj = Object(0)
		obj.set_shape(self.__class__.polygon)
		print(obj.get_shape().to_numpy())
		self.__class__.object = obj
	
	def test_world(self):
		w = World()
		b = BaseType(0)
		w.add_object(b)
		pass

	
if __name__ == '__main__':
	unittest.main()