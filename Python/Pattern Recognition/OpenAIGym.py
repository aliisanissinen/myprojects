# DATA.ML.100-2020-2021-1
# Introduction to Patter Recognition and Machine Learning
# Exercise 5
# Aliisa Nissinen
# Last edited 13.10.2020

import gym
import random
import numpy
import time

# Environment
env = gym.make("Taxi-v3")


# Taxi needs to drive passenger from pick up location to passenger's
# destination

def train(Q_reward, num_of_episodes, alpha, gamma, num_of_steps):
    # 1000 episodes
    for i in range(num_of_episodes):
        state = env.reset()
        alpha -= 0.00001
        done = False

        if alpha <= 0:          # Nothing to learn
            break
        for k in range(num_of_steps):
            action = random.randint(0, 5)
            newstate, reward, done, info = env.step(action)
            Q_reward[state, action] = (1-alpha)*Q_reward[state, action]+alpha*(
                    reward+gamma*numpy.max(Q_reward[newstate, :]))
            
            if done:             # drop off, 20 points
                break

            state = newstate

        print('Episode ', i + 1)
    print('Training done')
    return Q_reward


def main():
    # Training parameters for Q learning
    alpha = 0.9  # Learning rate
    gamma = 0.9  # Future reward discount factor
    num_of_episodes = 1000
    num_of_steps = 500  # per each episode

    # Q tables for rewards
    Q_reward = -1 * numpy.ones((500, 6))

    Q_reward = train(Q_reward, num_of_episodes, alpha, gamma, num_of_steps)

    avg_reward = 0
    avg_steps = 0

    for i in range(10):
        state = env.reset()
        tot_reward = 0
        tot_steps = 0
        for t in range(50):
            action = numpy.argmax(Q_reward[state, :])
            state, reward, done, info = env.step(action)
            tot_reward += reward
            tot_steps += 1
            env.render()
            time.sleep(1)
            if done:
                print("Total reward %d" % tot_reward)
                print("Total actions %d" % tot_steps)
                avg_steps += tot_steps
                avg_reward += tot_reward
                break

    print("Average total reward %d" % (avg_reward/10))
    print("Average total actions %d" % (avg_steps/10))


main()
