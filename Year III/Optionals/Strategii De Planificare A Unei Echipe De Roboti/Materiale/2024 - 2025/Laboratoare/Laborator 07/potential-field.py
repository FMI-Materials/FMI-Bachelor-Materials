# -*- coding: utf-8 -*-
"""
Created on Tue Mar 22 09:23:46 2022

@author: florin stoican, code adapted from https://matplotlib.org/stable/gallery/mplot3d/surface3d.html
"""

import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

obstacle=np.array([-1,-1])
a1=1
a2=0.5
fig, ax = plt.subplots(subplot_kw={"projection": "3d"})

# Make data.
X = np.arange(-2.5, 2.5, 0.1)
Y = np.arange(-2.5, 2.5, 0.1)
X, Y = np.meshgrid(X, Y)
Z = a1/(a2+np.sqrt((X-obstacle[0])**2 + (Y-obstacle[1])**2))

obstacle=np.array([0,2])
Z = Z+a1/(a2+np.sqrt((X-obstacle[0])**2 + (Y-obstacle[1])**2))

# Plot the surface.
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)

plt.show()

#%%
v,u=np.gradient(Z)

plt.figure()

plt.quiver(X,Y,-u,-v)
plt.show()



