from casadi import *
import numpy as np
import matplotlib.pyplot as plt

# Construct the formation graph
N = 5  # Number of agents
W = np.random.rand(N, N)
W[W <= 0.5] = 0  # Adjacency matrix constructed randomly

n = 2  # Dimension of the integrator dynamics (usually in 2D, so n = 2)

# Construct the graph's Laplacian
L = -W
for i in range(N):
    L[i, i] = np.sum(W[i, :])

# Control strategy
init_angles = np.random.rand(1, N) * 2 * np.pi
r_init = 10
pinit = r_init * np.vstack((np.cos(init_angles), np.sin(init_angles)))
star_angles = np.random.rand(1, N) * 2 * np.pi
r_star = 5
pstar = r_star * np.vstack((np.cos(star_angles), np.sin(star_angles)))

kp = 50

# Define the ODE for CasADi integration
SX_p = SX.sym('p', n*N)
SX_kp = SX.sym('kp', n*N)
ode = SX_kp * (pstar.flatten() - SX_p) + np.kron(L, np.eye(n)) @ SX_p

# Time setup
t0 = 0
tf = 1
tsamples = int(1e2)
time = np.logspace(-2, np.log10(tf), tsamples+1)

# Integrate with CasADi
intg_options = {'grid': time}
dae = {'x': SX_p, 'p': SX_kp, 'ode': ode}
intg = integrator('intg', 'cvodes', dae, intg_options)

trajectory = intg(x0=pinit.flatten(), p=kp)['xf'].full()

p_vals = trajectory.reshape(n, N,tsamples)

# Plotting
plt.figure()
tt = np.linspace(0, 2*np.pi, 100)
plt.plot(r_init * np.cos(tt), r_init * np.sin(tt), 'r--')
plt.plot(r_star * np.cos(tt), r_star * np.sin(tt), 'b--')

colors = plt.cm.hsv(np.linspace(0, 1, N))
for i in range(N):
    plt.scatter(pinit[0, i], pinit[1, i], s=150, color=colors[i], marker='d', label='Initial' if i == 0 else "")
    plt.scatter(pstar[0, i], pstar[1, i], s=150, color=colors[i], marker='s', label='Target' if i == 0 else "")
    plt.plot(p_vals[0, i, :], p_vals[1, i, :], '*--', color=colors[i])

plt.axis('equal')
plt.title('formation of single integrators with proportional control')
plt.show()

plt.figure() 
for i in range(N):
    plt.plot(time[0:-1], p_vals[0, i, :]- pstar[0, i], '*--', color=colors[i])
    plt.plot(time[0:-1], p_vals[1, i, :]- pstar[1, i], '*--', color=colors[i])
plt.title('time series for the target error of each agent')
plt.show()

