import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object
from src.proto import world_pb2, commons_pb2, object_pb2
from google.protobuf import text_format

class ProtobufTests(unittest.TestCase):

	def test_a_load_protobuf(self):
		f = open('src/python/tests/object.pb.txt', 'r')
		obj = object_pb2.Object() # replace with your own message
		text_format.Parse(f.read(), obj)
		f.close()
		self.assertEqual(obj.name, "Hello")
		self.__class__.pb = obj

	def test_serialize_to_string(self):
		pb_string = self.__class__.pb.SerializeToString()
		w = World()
		w.load_proto(pb_string)
		self.assertEqual(self.__class__.pb.name, "Hello")



if __name__ == '__main__':
	unittest.main()