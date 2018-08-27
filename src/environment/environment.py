import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object, KinematicObserver
from src.proto import world_pb2, commons_pb2, object_pb2
from google.protobuf import text_format


# load proto
f = open('src/environment/python_bindings/tests/object.pb.txt', 'r')
obj = world_pb2.World() # replace with your own message
text_format.Parse(f.read(), obj)
f.close()

model = SingleTrackModel()


# create world
world = World()
world.load_proto(obj.SerializeToString())

# step world
u = np.array([[0.5,1.5]])
for agent in world.get_agents():
	#agent.step(u, 0.25)
	agent.set_kinematic_model(model)

o = KinematicObserver()
o.set_world(world)


for i in range(0,20):
	for agent in world.get_agents():
		o.observe(agent.step(u, 0.25))
		print(agent.get_state())

# TODO: visualize world
# [[mat0,..., matN], [a0, ..., aN], [mat0, .., matN], [r0,..., rN]] = o.sample()
	