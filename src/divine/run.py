import numpy as np
import random

from src.environment.environment import Environment
from divine_rl.world import KinematicObserver

if __name__ == '__main__':
	# setup environment
	env = Environment("tests/python/structured_world.pb.txt")
	env.debug_world_plot()
	
	# setup obsever
	#obs = KinematicObserver()
	#obs.set_world(env.world)
	
	u = np.array([[random.uniform(-0.5, 0.5)]])

	# run environment
	for i in range(0, 1):
		running = True
		while running:
			for agent in env.agents:
				state, action, next_state, reward, is_final = agent.step(u, 0.25)
				if is_final:
					print(state, action, next_state, reward)
					running = False
					env.reset()
			
			# plot agents
			env.debug_agents_plot()

	# show plots
	env.debug_plot_show()

	# replay memory
	#replay_memory = obs.memory.sample(50)
	#replay_batch = zip(replay_memory.states, replay_memory.actions, replay_memory.next_states, replay_memory.rewards)

	
