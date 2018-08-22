import unittest
import numpy as np
#import matplotlib.pyplot as plt
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel


class KinematicTests(unittest.TestCase):

	def test_single_track_model(self):
		state = np.array([[0,0,0,5]])
		u = np.array([[0.5,0.5]])
		model = SingleTrackModel()

		for i in range(0, 10):
			state = model.step(state, u, 0.1)
			print(state)


	
if __name__ == '__main__':
	unittest.main()