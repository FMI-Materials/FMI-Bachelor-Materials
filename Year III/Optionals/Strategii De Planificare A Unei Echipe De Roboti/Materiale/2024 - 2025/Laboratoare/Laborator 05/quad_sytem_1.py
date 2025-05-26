from roblib import *  # Ensure this is in your Python path or in the same directory

# Initialize the figure and 3D plot
fig = figure()
ax = fig.add_subplot(111, projection = '3d')

# Define physical parameters for the quadrotor
m, g, b, d, l = 10, 9.81, 2, 1, 1
I = array([[10, 0, 0], [0, 10, 0], [0, 0, 20]])
dt = 0.01
B = array([[b, b, b, b], [-b * l, 0, b * l, 0], [0, -b * l, 0, b * l], [-d, d, -d, d]])

# Initialize list to store the path of the drone
path = []


# Define the clock function to update the quadrotor state
def clock_quadri(p, R, vr, wr, w):
    w2 = w * abs(w)
    τ = B @ w2.flatten()
    p = p + dt * R @ vr
    vr = vr + dt * (-adjoint(wr) @ vr + inv(R) @ array([[0], [0], [g]]) + array([[0], [0], [-τ[0] / m]]))
    R = R @ expw(dt * wr)
    wr = wr + dt * (inv(I) @ (-adjoint(wr) @ I @ wr + τ[1:4].reshape(3, 1)))
    return p, R, vr, wr


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
    dp = E @ vr
    zd = -10
    vd = 10
    fd = f_vdp(array([[x], [y]]))
    # Desired states
    td0 = 300 * tanh(z - zd) + 60 * vr[2]  # Desired thrust or related control input
    φd = 0.5 * tanh(10 * sawtooth(angle(fd) - angle(dp)))  # Desired roll angle
    θd = -0.3 * tanh(vd - vr[0])  # Desired pitch angle
    ψd = angle(dp)  # Desired yaw angle

    # Inverse of Block 3
    wrd = 5 * inv(eulerderivative(φ, θ, ψ)) @ array([[float(sawtooth(φd - φ).item())],
                                                     [float(sawtooth(θd - θ).item())],
                                                     [float(sawtooth(ψd - ψ).item())]], dtype = float)

    # Inverse of Block 2
    td13 = I @ ((100 * (wrd - wr)) + adjoint(wr) @ I @ wr)

    # Inverse of Block 1
    W2 = inv(B) @ vstack(([td0], td13))
    w = sqrt(abs(W2)) * sign(W2)
    return w


# Initialize state variables
p = array([[0], [0], [-5]])  # Position: x, y, z (front, right, down)
R = eye(3)  # Initial rotation matrix (identity matrix)
vr = array([[1], [1], [0]])  # Initial linear velocity
wr = array([[0], [0], [0]])  # Initial angular velocity
α = array([[0, 0, 0, 0]]).T  # Initial angles for the rotor blades

# Simulation loop
for t in arange(0, 5, dt):
    X = hstack((p.flatten(), eulermat2angles(R), vr.flatten(), wr.flatten())).reshape(-1, 1)
    w = control(X)
    p, R, vr, wr = clock_quadri(p, R, vr, wr, w)

    # Store the position in the path list
    path.append(p.flatten())

    clean3D(ax, -70, 70, -70, 70, 0, 70)
    draw_quadrotor3D(ax, p, R, α, 5 * l)
    α = α + dt * 30 * w
    pause(0.001)

# Convert path list to numpy array for easier handling
path = array(path)

# Plot the 2D path of the drone (x vs y)
figure()
plot(path[:, 0], path[:, 1])
xlabel('X Position')
ylabel('Y Position')
title('2D Path of the Drone')
grid(True)
show()

pause(1)
