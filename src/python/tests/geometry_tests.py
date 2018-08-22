import unittest
import numpy as np
import matplotlib.pyplot as plt
from divine_rl.commons import Point, Line, Polygon


class GeometryTests(unittest.TestCase):

	def test_create_points(self):
		p0 = Point(1.0, 2.0)
		p1 = Point(1.0, 2.0)
		self.assertTrue(np.allclose(p0.to_numpy(), p1.to_numpy()))

	def test_create_lines(self):
		line = Line()
		p0 = Point(0.0, 3.0)
		p1 = Point(10.0, 3.0)

		line.append(p0)
		line.append(p1)
		self.assertTrue(np.allclose(line.to_numpy(), np.array([[0.0, 3.0], [10.0, 3.0]])))

		self.__class__.line = line

		
	def test_create_polygons(self):
		poly = Polygon()
		p0 = Point(0.0, 0.0)
		p1 = Point(2.0, 0.0)
		p2 = Point(2.0, 1.0)
		p3 = Point(0.0, 1.0)
		p4 = Point(0.0, 0.0)

		poly.append(p0)
		poly.append(p1)
		poly.append(p2)
		poly.append(p3)
		poly.append(p4)
		self.assertTrue(np.allclose(poly.to_numpy(), np.array([[0.0, 0.0], [2.0, 0.0], [2.0, 1.0], [0.0, 1.0], [0.0, 0.0]])))

		self.__class__.polygon = poly

	def test_distances(self):

		# line to poly
		self.assertEqual(self.__class__.line.distance(self.__class__.polygon), 2.0)

		# poly point
		p0 = Point(5.0, 0.0)
		self.assertEqual(self.__class__.polygon.distance(p0), 3.0)

		# line point
		self.assertEqual(self.__class__.line.distance(p0), 3.0)

	def test_transformations(self):
		transformed_poly = self.__class__.polygon.translate(Point(1.0, 1.0))
		self.assertTrue(np.allclose(transformed_poly.to_numpy(), np.array([[1.0, 1.0], [3.0, 1.0], [3.0, 2.0], [1.0, 2.0], [1.0, 1.0]])))

		pts = self.__class__.polygon.rotate(-90).to_numpy()
		plt.plot(pts[:, 0], pts[:, 1])
		plt.axis('equal')
		plt.show()


	def test_collisions(self):
		pass
	
if __name__ == '__main__':
	unittest.main()