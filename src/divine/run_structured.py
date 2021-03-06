import numpy as np
import random
from src.environment.environment import Environment

if __name__ == '__main__':

	# load environment
	env = Environment("tests/python/structured_world.pb.txt")
	env.debug_world_plot()

	# randomly chosen system input
	u = np.array([[random.uniform(-0.5, 0.5)]])

	# run until complete
	running = True
	while running:
		#for agent in env.agents:
		state, reward, is_final, _ = env.step(u)


		if is_final:
			running = False
			env.reset()
		
		# plot agents
		env.debug_agents_plot()

	# show plots
	env.debug_plot_show()

