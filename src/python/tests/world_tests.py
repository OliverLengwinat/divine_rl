import unittest
import numpy as np
import matplotlib.pyplot as plt
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent


class WorldTests(unittest.TestCase):

	def test_agents(self):
		state = np.array([[0,0,0,5]])
		u = np.array([[0.5,0.5]])
		model = SingleTrackModel()

		w = World()
		a = Agent(0)
		a.set_kinematic_model(model)


		pass


	
if __name__ == '__main__':
	unittest.main()