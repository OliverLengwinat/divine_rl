import unittest
import numpy as np
from divine_rl.commons import Point, Line, Polygon, SingleTrackModel
from divine_rl.world import World, Agent, Object, KinematicObserver, BaseObserver, ReplayMemory
from src.proto import world_pb2, commons_pb2, object_pb2
from google.protobuf import text_format
from viewer.viewer import Viewer

import time


# load proto
f = open('src/environment/python_bindings/tests/object.pb.txt', 'r')
obj = world_pb2.World() # replace with your own message
text_format.Parse(f.read(), obj)
f.close()

# create world
world = World()
world.load_proto(obj.SerializeToString())

# create observer
o = KinematicObserver()
o.set_world(world)


# set model to be used
# TODO: set triple integrator model for line following
# model = ThreeIntModel(ref_line)

model = SingleTrackModel()
u = np.array([[0.5,0.5]])
for agent in world.get_agents():
	agent.set_kinematic_model(model)


viewer = Viewer()
start = time.time()
# simulate

for i in range(0,20):
	for agent in world.get_agents():
		o.observe(agent.step(u, 0.25)) # save these and update later
	viewer.draw_world(world)


memory = o.get_replay_memory()
print(memory.sample(10))


viewer.show()
end = time.time()
print(end - start)
	