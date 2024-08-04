import collections
import random
import matplotlib.pyplot as plt

# A simple deque, uniform priority replay buffer
class ReplayBuffer:
    def __init__(self, buffer_size):
        self.buffer_size = buffer_size

        # Not so optimal for sampling but works...
        self.replayMem = collections.deque(maxlen=buffer_size)

    # Add a new experience to the buffer
    def add(self, state, action, reward, next_state, done):
        self.replayMem.append((state, action, reward, next_state, done))

    # Get a sample batch from the memory
    def sample(self, batch_size):
        if batch_size <= len(self.replayMem):
            return random.sample(self.replayMem, batch_size)
        else:
            assert False

    def __len__(self):
        return len(self.replayMem)


# Given the start and end epsilon, the number of steps allowed to explore fully the env,
# final_eps_step - when to apply the final_eps, gives you back the epsilon value for each step
class LinearScheduleEpsilon():
    def __init__(self, start_eps = 1.0, final_eps = 0.1,
                 pre_train_steps = 10, final_eps_step = 10000):
        self.start_eps = start_eps
        self.final_eps = final_eps
        self.pre_train_steps = pre_train_steps
        self.final_eps_step = final_eps_step
        self.decay_per_step = (self.start_eps - self.final_eps) \
                                /  (self.final_eps_step - self.pre_train_steps)


    def getValue(self, step):
        if step <= self.pre_train_steps:
            return 1.0 # full exploration in the beginning
        else:
            epsValue = (1.0 - self.decay_per_step * (step - self.pre_train_steps))
            epsValue = max(self.final_eps, epsValue)
            return epsValue

# Demo linear schedule
def testLinearSchedule():
    lse = LinearScheduleEpsilon(start_eps=1.0, final_eps=0.1, pre_train_steps=10, final_eps_step=100)
    values = [lse.getValue(f) for f in range(0, 300)]
    plt.plot(values)
    plt.show()

if __name__ == "__main__":
    testLinearSchedule()
