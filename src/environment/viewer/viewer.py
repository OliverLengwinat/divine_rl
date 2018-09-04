import matplotlib.pyplot as plt
from google.protobuf import text_format
from src.proto import world_pb2, commons_pb2, object_pb2

class Viewer(object):
	def __init__(self):
		pass

	def draw_world(self, world, color='gray'):
		for obj in world.get_objects():
			properties = commons_pb2.Properties()
			properties_byte = str.encode(obj.get_properties() )
			properties.ParseFromString( properties_byte )

			if obj.get_type() == 1:
				polygon = obj.get_shape()
				self.draw_polygon(polygon, color=properties.edgecolorcolor())

		# draw bounding box
		bb = world.get_bounding_box().to_numpy()
		plt.plot(bb[:,0], bb[:,1], color='gray', linestyle='dotted')
		for _, line in world.get_road_network().get_line_segments().items():
			pts = line.to_numpy()
			plt.plot(pts[:,0], pts[:,1], color='black')

	def draw_polygon(self, polygon, color='gray'):
		pts = polygon.to_numpy()
		plt.plot(pts[:,0], pts[:,1], color=color)

	def draw_point(self, point, color='gray'):
		pts = point.to_numpy()
		plt.plot(pts[0,0], pts[0,1], marker='o', color=color)

	def show(self):
		plt.axis("equal")
		plt.show()