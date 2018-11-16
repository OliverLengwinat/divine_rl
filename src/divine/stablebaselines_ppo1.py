import gym
import numpy as np

import os
from pathlib import Path #get home path with str(Path.home())

import matplotlib.pyplot as plt

from stable_baselines.common.policies import MlpPolicy
from stable_baselines.common.vec_env import SubprocVecEnv
from stable_baselines.common import set_global_seeds
#from stable_baselines import ACKTR

from stable_baselines.results_plotter import load_results, ts2xy
from stable_baselines import DDPG
from stable_baselines import PPO1
from stable_baselines.ddpg.noise import AdaptiveParamNoiseSpec
from stable_baselines.bench import Monitor
from stable_baselines.common.vec_env.dummy_vec_env import DummyVecEnv

import random
from src.environment.environment import EnvironmentHolding

from gym.envs.registration import registry, register, make, spec



# load environment
#mygym = None
#if (os.path.exists('tests/python/structured_world.pb.txt')):
#    mygym = EnvironmentHolding("tests/python/structured_world.pb.txt")
#else:
#    mygym = EnvironmentHolding("/experiment/tensorforce_train.runfiles/__main__/tests/python/structured_world.pb.txt")

#game_version = "v0"
#env = mygym.make(game_version)
#env = env.env
#agent = dqn_agent.DQNAgent()

# register our own env as a gym env
if (os.path.exists('tests/python/structured_world.pb.txt')):
    envpath = 'tests/python/structured_world.pb.txt'
else:
    envpath = "/experiment/stablebaselines_ppo1.runfiles/__main__/tests/python/structured_world.pb.txt"
register(
    id='DivineRlStructured-v0',
    entry_point='src.environment.environment:Environment',
    kwargs={'path': envpath},
    max_episode_steps=200,
    reward_threshold=1.0,
)

best_mean_reward, n_steps = -np.inf, 10

def callback(_locals, _globals):
    """
    Callback called at each step (for DQN an others) or after n steps (see ACER or PPO2)
    :param _locals: (dict)
    :param _globals: (dict)
    """
    global n_steps, best_mean_reward
    # Print stats every 1000 calls
    if (n_steps + 1) % 10 == 0:
    # Evaluate policy performance
        x, y = ts2xy(load_results(logdir), 'timesteps')

        if len(x) > 0:
            mean_reward = np.mean(y[-100:])
            print(x[-1], 'timesteps')
            print("Best mean reward: {:.2f} - Last mean reward per episode: {:.2f}".format(best_mean_reward, mean_reward))

            # New best model, you could save the agent here
            if mean_reward > best_mean_reward:
                best_mean_reward = mean_reward
                # Example for saving best model
                print("Saving new best model")
                _locals['self'].save(modelsdir + 'best_model.pkl')

    n_steps += 1
    return False


# Create log dir
if (os.path.isdir('/experiment')): #starting with Singularity
    print("logdir in /experiment")
    #logdir = "/experiment/tensorboardLogs/"
    logdir = "/experiment/StableLogs/"
    modelsdir = "/experiment/StableModels_out/"
else:
    #logdir = str(Path.home())+"/tensorboardLogs/"
    logdir = str(Path.home())+"/StableLogs/"
    modelsdir = str(Path.home())+"/StableModels_out/"
os.makedirs(logdir, exist_ok=True)
os.makedirs(modelsdir, exist_ok=True)


def make_env(env_id, rank, seed=0):
    """
    Utility function for multiprocessed env.

    :param env_id: (str) the environment ID
    :param num_env: (int) the number of environments you wish to have in subprocesses
    :param seed: (int) the inital seed for RNG
    :param rank: (int) index of the subprocess
    """
    def _init():
        env = gym.make(env_id)
        env.seed(seed + rank)
        return env
    set_global_seeds(seed)
    return _init

env_id = "DivineRlStructured-v0"
env = gym.make(env_id)
#num_cpu = 4  # Number of processes to use
# Create the vectorized environment
#env = SubprocVecEnv([make_env(env_id, i) for i in range(num_cpu)])
#env = gym.make(env_id)

env = Monitor(env, logdir, allow_early_resets=True)
env = DummyVecEnv([lambda: env]) #DON'T DELETE THIS! It might not crash the program but it breaks the environment (i.e. allow cars to intersect)


#model = ACKTR(MlpPolicy, env, verbose=1)
# Add some param noise for exploration
#param_noise = AdaptiveParamNoiseSpec(initial_stddev=0.2, desired_action_stddev=0.2)
#model = DDPG(MlpPolicy, env, param_noise=param_noise, memory_limit=int(1e6), verbose=0)
model = PPO1(MlpPolicy, env)

# Train the agent
model.learn(total_timesteps=50000, callback=callback)
#model.learn(total_timesteps=5000) #no information or saving before finished

model.save(modelsdir + 'final_model.pkl')

#show example runs
obs = env.reset()
for __ in range(3):
    while (True):
        action, _states = model.predict(obs)
        obs, rewards, done, info = env.step(action)
        if (done == True): break
        env.render()
