from numpy.linalg import linalg
import pandas as pd
from roblib import *  # Ensure this is in your Python path or in the same directory
import numpy as np
import matplotlib.pyplot as plt

# Initialize the figure and 3D plot
fig1 = figure()
ax1 = fig1.add_subplot(111, projection='3d')

# Define physical parameters for the quadrotor
m, g, b, d, l = 0.275, 9.81, 2, 1, 1
I = array([[10, 0, 0], [0, 10, 0], [0, 0, 20]])
dt = 0.01
B = array([[b, b, b, b], [-b * l, 0, b * l, 0], [0, -b * l, 0, b * l], [-d, d, -d, d]])
h = 0        # x-coordinate of the center
k = 0        # y-coordinate of the center
r = 120      # Radius in cm
num_points = 1000  # Number of waypoints for smooth path
# Initialize list to store the path of the drone
path = []
alpha_history = []
tau_history = []
w_history = []
wrd_history=[]
# Define the clock function to update the quadrotor state
def clock_quadri(p, R, vr, wr, w):
    w2 = w * abs(w)
    τ = B @ w2.flatten()
    p = p + dt * R @ vr
    vr = vr + dt * (-adjoint(wr) @ vr + inv(R) @ array([[0], [0], [g]]) + array([[0], [0], [-τ[0] / m]]))
    R = R @ expw(dt * wr)
    wr = wr + dt * (inv(I) @ (-adjoint(wr) @ I @ wr + τ[1:4].reshape(3, 1)))
    return p, R, vr, wr,τ


def circular_trajectory(t, radius=120.0, angular_velocity=1.0):

    x = radius * np.cos(angular_velocity * t)
    y = radius * np.sin(angular_velocity * t)
    return np.array([x, y])


def f_vdp(x):
    x = x.flatten()
    vdp0 = x[1]
    vdp1 = -(0.001 * (x[0] ** 2) - 1) * x[1] - x[0]
    dx = array([[vdp0], [vdp1]])
    return dx

# Define the control function to calculate rotor speeds
def control(X):
    X = X.flatten()
    x, y, z, φ, θ, ψ = list(X[0:6])
    vr = X[6:9].reshape(3, 1)
    wr = X[9:12].reshape(3, 1)
    E = eulermat(φ, θ, ψ)
    print(E)
    print('nextstep')
    dp = E @ vr
    zd = -10
    vd = 10
    fd = circular_trajectory(t, radius=120.0, angular_velocity=0.628)
    # fd= f_vdp(array([[x],[y]]))
    td0 = 60 * tanh(z - zd) + 12* vr[2]  # Desired thrust or related control input
    φd = 0.5 * tanh(10 * sawtooth(angle(fd) - angle(dp)))  # Desired roll angle
    θd = -0.3 * tanh(vd - vr[0])  # Desired pitch angle
    ψd = angle(dp)  # Desired yaw angle
    R_D= eulermat(float(sawtooth(φd).item()),float(sawtooth(θd).item()), float((sawtooth(ψd).item())))
    #Inverse Block 3
    wrd_s=5*((inv(E) @ R_D )-eye(linalg.matrix_rank(E)))
    wrd=adjoint_inv(wrd_s)
    wrd_history.append(wrd.flatten())
    # wrd = 5 * inv(eulerderivative(φ, θ, ψ)) @ array([[float(sawtooth(φd - φ).item())],
    #                                                  [float(sawtooth(θd - θ).item())],
    #                                                  [float(sawtooth(ψd - ψ).item())]], dtype=float)
    #Inverse Block 2
    td13 = I @ ((100 * (wrd - wr)) + adjoint(wr) @ I @ wr)
    #Inverse Block 1
    W2 = inv(B) @ vstack(([td0], td13))
    w = sqrt(abs(W2)) * sign(W2)
    return w

# Initialize state variables
p = array([[5], [-3], [-5]])  # Position: x, y, z (front, right, down)
R = eye(3)  # Initial rotation matrix (identity matrix)
vr = array([[2], [-4], [3]])  # Initial linear velocity
wr = array([[0], [0], [4]])  # Initial angular velocity
α = array([[-8, -10, -9, -5]]).T  # Initial angles for the rotor blades

# Simulation loop
for t in arange(0, 20, dt):
    X = hstack((p.flatten(), eulermat2angles(R), vr.flatten(), wr.flatten())).reshape(-1, 1)
    w = control(X)
    p, R, vr, wr,τ= clock_quadri(p, R, vr, wr, w)
    path.append(p.flatten())
    alpha_history.append(α.flatten())
    tau_history.append(τ.flatten())
    w_history.append(w.flatten())
    clean3D(ax1, -80, 80, -80, 80, 0, 80)
    path_array = array(path)
    ax1.plot(-path_array[:, 0], path_array[:, 1], -path_array[:, 2], color='blue', linewidth=1)
    draw_quadrotor3D(ax1, p, R, α, 5 * l, 3)
    α = α + dt * 100 * w
    pause(0.001)

# Convert path list to numpy array for easier handling
path = array(path)
alpha_history = array(alpha_history)
tau_history = np.array(tau_history)
w_history = np.array(w_history)
wrd_history = np.array(wrd_history)
# Plot the 3D path of the drone in a new figure
fig2 = plt.figure()
ax2 = fig2.add_subplot(111, projection='3d')
ax2.plot(-path[:, 0], path[:, 1], -path[:, 2], color='red')
ax2.set_xlabel('X Position')
ax2.set_ylabel('Y Position')
ax2.set_zlabel('Z Position')
ax2.set_title('3D Trajectory of Quadcopter')





time_array = np.arange(0, len(alpha_history) * dt, dt)
fig2, axs_w = plt.subplots(3, 1, figsize=(10, 8), sharex=True)

# Define labels for Pitch, Roll, and Yaw
labels = ['Pitch', 'Roll', 'Yaw']

for i in range(3):
    axs_w[i].plot(time_array, wrd_history[:, i], label=f'Angular Velocity {labels[i]}')
    axs_w[i].set_ylabel(f'Angular Velocity ({labels[i]})')
    axs_w[i].set_title(f'Angular Velocity - {labels[i]}')
    axs_w[i].grid(True)

axs_w[-1].set_xlabel('Time (s)')
plt.tight_layout()




# Plot the tau (torques) over time in subplots
fig3, axs_tau = plt.subplots(4, 1, figsize=(10, 8), sharex=True)
titles = ['Thrust', 'Roll Torque', 'Pitch Torque', 'Yaw Torque']
for i in range(4):
    axs_tau[i].plot(np.arange(0, len(tau_history) * dt, dt), tau_history[:, i], label=f'Torque {titles[i]}')
    axs_tau[i].set_ylabel(f'{titles[i]} (τ)')
    axs_tau[i].set_title(f'{titles[i]}')
    axs_tau[i].grid(True)

axs_tau[-1].set_xlabel('Time (s)')
plt.tight_layout()


fig5, axs_w = plt.subplots(4, 1, figsize=(10, 8), sharex=True)

for i in range(4):
    axs_w[i].plot(time_array, w_history[:, i], label=f'Angular Velocity w{i + 1}')
    axs_w[i].set_ylabel('Angular Velocity of Rotors (w)')
    axs_w[i].set_title(f'Angular Velocity w{i + 1}')
    axs_w[i].grid(True)

axs_w[-1].set_xlabel('Time (s)')
plt.tight_layout()

wrd_df = pd.DataFrame(wrd_history, columns=[f'wrd{i+1}' for i in range(wrd_history.shape[1])])

# Define the path where you want to save the CSV file
csv_path = './wrd_history.csv'


# Save the DataFrame to a CSV file
wrd_df.to_csv(csv_path, index=False)

print(f'wrd data has been exported to {csv_path}')


# Display all figures
plt.show()


