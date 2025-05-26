import numpy as np
import itertools
import casadi as ca
import matplotlib.pyplot as plt
from scipy.special import comb
from scipy.integrate import quad

# define the Bezier basis function of index i and degree n, at time instant t
def B(i, n, t):
    return comb(n, i) * (t**i) * ((1 - t)**(n - i))

# construct the Bezier curve from control points P, at time instant t
def z(t, P):
    n = P.shape[0] - 1
    return sum(P[i] * B(i, n, t) for i in range(n + 1))

def plot_bezier_curve(trajectory,Pval, W = None, title='unspecified'):
    plt.figure(figsize=(8, 6))
    plt.plot(trajectory[:, 0], trajectory[:, 1])
    plt.plot(Pval[:, 0], Pval[:, 1], 'o--', color='red')
    if W is not None:
        plt.scatter(W[:, 0], W[:, 1], color='blue')

    plt.title(title)
    plt.xlabel('X')
    plt.ylabel('Y')
    if W is not None:
        plt.legend(['Bezier curve', 'control polygon', 'Waypoints'])
    else:
        plt.legend(['Bezier curve', 'control polygon'])
    plt.grid(True)
    plt.show(block=False)

# %%  a simple example with hard-coded values for the control points
P = np.array([[0, 0], [1, 1], [3, 2], [5, 1], [6, 0]])
t_values = np.linspace(0, 1, 100)
trajectory = np.array([z(t, P) for t in t_values])
plot_bezier_curve(trajectory, P, None, title='Example of Bezier curve for a list of random control points')

# %% this time, for a given list of waypoints, find the curve that passes through the waypoints

#  list of waypoints and the times at which we pass through them
W = np.array([
    [0, 0],
    [1, 2],
    [3, 1],
    [4, 2],
    [5, 1]
])
tw = [0, 0.4, 0.6, 0.8, 1]
m = np.shape(W)[0]

#  define the number of Bezier curves; it has to be at least the number of waypoints
n = 10

# define and solve the optimization problem

# instantiate the Opti class
solver = ca.Opti()

# define the variables
P = solver.variable(2, n+1)
epsilon = solver.variable(1)


# define a function that computes the energy along the path
def path_energy(P):
    integral_sum = 0
    for i, k in itertools.product(range(n-1), range(n-1)):
        integrand = (P[:, i+1] - P[:, i]).T @ (P[:, k+1] - P[:, k]) * n**2 * quad(lambda t: B(i, n - 1, t) * B(k, n - 1, t), 0, 1)[0]
        integral_sum += integrand
    return integral_sum
#  and use it to define the cost
solver.minimize(path_energy(P) + 100 * epsilon)

# define the constraints

# pass through the waypoints
for j in range(m):
    Bs = [B(i, n, tw[j]) for i in range(n+1)]
    solver.subject_to(P @ Bs == W[j, :])
# limit the values for the control points
solver.subject_to(epsilon>=0)
for i in range(n+1):
    solver.subject_to(P[:, i] <= epsilon)
    solver.subject_to(P[:, i] >= -epsilon)

# attach a solver
solver.solver('ipopt')

# and solve the optimization problem
sol = solver.solve()

# retrieve the numerical solution (the value of the control points)
P_opt = sol.value(P)

P_opt = zip(P_opt[0], P_opt[1])
P_opt = np.array(list(P_opt))
print(P_opt.shape)

t_values = np.linspace(0, 1, 100)
trajectory = np.array([z(t, P_opt) for t in t_values])
plot_bezier_curve(trajectory, P_opt, W, title='Bezier curve passing through list of waypoints')

# %%  illustrate theta (the remaining state) and U_V, u_theta (the control actions) using the computed value of z(t)

z1 = trajectory[:, 0]
z2 = trajectory[:, 1]

dP = P_opt.shape[0] * (P_opt[1:,:]-P_opt[:-1,:])
dtrajectory = np.array([z(t, dP) for t in t_values])
z1_dot = dtrajectory[:,0]
z2_dot = dtrajectory[:,1]

ddP = P_opt.shape[0] * (P_opt.shape[0] - 1) \
        * (P_opt[2:,:]-2 * P_opt[1:-1,:] + P_opt[:-2,:])
ddtrajectory = np.array([z(t, ddP) for t in t_values])
z1_dot_dot = ddtrajectory[:,0]
z2_dot_dot = ddtrajectory[:,1]


u_V = np.sqrt(z1_dot**2 + z2_dot**2)

L=1

u_theta = np.arctan(L*(z2_dot_dot*z1_dot - z2_dot*z1_dot_dot)/(z1_dot**2 + z2_dot**2)**(3/2))

plt.figure(figsize=(8, 6))
plt.plot(t_values, u_V)
plt.title('u_V(t)')
plt.xlabel('t')
plt.ylabel('u_V')
plt.grid(True)
plt.show(block=False)

plt.figure(figsize=(8, 6))
plt.plot(t_values, u_theta)
plt.title('u_theta(t)')
plt.xlabel('t')
plt.ylabel('u_theta')
plt.grid(True)
plt.show(block=False)

plt.show()