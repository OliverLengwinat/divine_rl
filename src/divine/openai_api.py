import numpy as np
import random
from src.environment.environment import EnvironmentHolding


if __name__ == '__main__':

  # load environment
  gym = EnvironmentHolding("tests/python/structured_world.pb.txt")

   
  game_version = "v0"
  env = gym.make(game_version)
  env = env.env
  #agent = dqn_agent.DQNAgent()