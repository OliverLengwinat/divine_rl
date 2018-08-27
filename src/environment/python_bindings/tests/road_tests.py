import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object, RoadNetwork
from src.proto import world_pb2, commons_pb2, object_pb2
from google.protobuf import text_format
import matplotlib.pyplot as plt

class PRoadTests(unittest.TestCase):

	def test_road(self):
		rn = RoadNetwork()
		p0 = Point(0.0, 0.0)
		p1 = Point(0.0, 2.0)
		p2 = Point(5.0, 2.0)
		p3 = Point(10.0, 2.0)
		
		line = rn.calculate_bezier(p0, p1, p2, p3)
		pts = line.to_numpy()

		plt.plot(pts[:,0], pts[:,1])
		plt.axis("equal")
		plt.show()
		pass
		


if __name__ == '__main__':
	unittest.main()