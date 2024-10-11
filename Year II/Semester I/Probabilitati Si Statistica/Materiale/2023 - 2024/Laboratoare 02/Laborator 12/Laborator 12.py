import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import scipy.special

gamma = np.load('sample_Gamma.npy')
negativ_binomial = np.load('sample_NegativBinom.npy')

# ============ A  ============
# plt.hist(gamma, bins=50, color='blue', alpha=0.7, label='Gamma Distribution')
# plt.hist(negativ_binomial, bins=50, color='orange', alpha=0.7, label='Negative Binomial Distribution')
#
# plt.xlabel('Values')
# plt.ylabel('Frequency')
# plt.title('Histogram of Gamma and Negative Binomial Distributions')
# plt.legend()

# plt.show()
# ============================

# ============ B VARIANTA 1 ============
n = len(gamma)
sumXi = np.sum(gamma)
theta = np.linspace(0.00001,0.99999,100)

lege = lambda t : -1 * np.sum(t * np.log((n * t)/sumXi) - np.log(sp.special.gamma(t)) - (n * t)/sumXi * gamma + (t-1) * np.log(gamma))
res = sp.optimize.minimize(lege, 1)

print(f"Aproximare: {res.x}, {(n * res.x) / sumXi}")
# ======================================

# ============ B VARIANTA 2 ============
derivata = lambda t: n * np.log((n * t)/sumXi) - n * sp.special.digamma(t) + np.sum(np.log(gamma))

res2 = sp.optimize.fsolve(derivata, 1)

print(f"Aproximare 2: {res2}, {(n * res2) / sumXi}")
# ======================================


# ============ C ============
from matplotlib import cm
from matplotlib.ticker import LinearLocator

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

theta1 = np.linspace(0.1, 10, 100)
theta2 = np.linspace(0.01, 1, 100)

vals = np.zeros(len(theta1), len(theta2))

for i, th1 in enumerate(theta1):
    for j, th2 in enumerate(theta2):
        vals[i, j] = lege(i,j)

X = np.arange(-5, 5, 0.25)
Y = np.arange(-5, 5, 0.25)
X, Y = np.meshgrid(X, Y)
R = np.sqrt(X**2 + Y**2)
Z = np.sin(R)

# Plot the surface.
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)

# Customize the z axis.
ax.set_zlim(-1.01, 1.01)
ax.zaxis.set_major_locator(LinearLocator(10))
# A StrMethodFormatter is used automatically
ax.zaxis.set_major_formatter('{x:.02f}')

# Add a color bar which maps values to colors.
fig.colorbar(surf, shrink=0.5, aspect=5)

plt.show()
# ===========================
