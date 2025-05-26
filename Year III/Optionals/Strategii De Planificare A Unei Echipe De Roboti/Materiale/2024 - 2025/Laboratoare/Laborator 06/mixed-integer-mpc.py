# -*- coding: utf-8 -*-
"""
Created on Mon Mar 14 22:43:45 2022

@author: florin stoican
"""

import numpy as np
from matplotlib import pyplot as plt
from casadi import *


#%% #########  initialize the problem elements             #######################
plant={'dx':4, 'du':2, 'dy':2, 'dz':4, 'Te':0.5, 'umin':[-0.5, -0.5], 'umax':[0.5, 0.5]}
controller={'Npred':8, 'Nsim':50, 'x0':[-3,-1,0.2,-0.2]}
obstacle={"V":[[1,  1],\
                 [-1,  1],\
                 [-1,  -1],\
                 [1,  -1]]}
M=1000

#%% #########  construct the solver object which implements the MPC problem ######
solver = casadi.Opti()

# inputs and states over the prediction horizon
X = solver.variable(plant['dx'], controller['Npred'] + 1)  # contains the states (position + velocity)
U = solver.variable(plant['du'], controller['Npred'])  # contains the inputs (acceleration)
Z = solver.variable(plant['dz'], controller['Npred'])  # contains the inputs (acceleration)

discrete=np.zeros(plant['dx']*(controller['Npred'] + 1),dtype=bool)
discrete=np.append(discrete,np.zeros(plant['du']*controller['Npred'],dtype=bool))
discrete=np.append(discrete,np.ones(plant['dz']*controller['Npred'],dtype=bool))

# initial state and target state
X_init = solver.parameter(plant['dx'], 1)
X_target = solver.parameter(plant['dx'], 1)

objective = 0
solver.subject_to(X[:, 0] == X_init)

for k in range(controller['Npred']):
    
    # @ does matrix multiplication in Casadi
    solver.subject_to(X[0, k + 1] == (X[0, k] + plant['Te']*X[2,k]))
    solver.subject_to(X[1, k + 1] == (X[1, k] + plant['Te']*X[3,k]))
    solver.subject_to(X[2, k + 1] == (X[2, k] + plant['Te']*U[0,k]))
    solver.subject_to(X[3, k + 1] == (X[3, k] + plant['Te']*U[1,k]))
    
    solver.subject_to(-X[0, k + 1] <= -1+M*Z[0,k])
    solver.subject_to( X[0, k + 1] <= -1+M*Z[1,k])
    solver.subject_to(-X[1, k + 1] <= -1+M*Z[2,k])
    solver.subject_to( X[1, k + 1] <= -1+M*Z[3,k])
    solver.subject_to(Z[0,k]+Z[1,k]+Z[2,k]+Z[3,k]==3)
    
    solver.subject_to(plant['umin'] <= U[:, k])
    solver.subject_to(U[:, k] <= plant['umax'])

    objective = objective + \
                casadi.transpose(X[:, k] - X_target) @ (X[:, k] - X_target) + \
                casadi.transpose(U[:, k]) @ (U[:, k])

solver.minimize(objective)

solver_options = {'print_time': 0, 'discrete':discrete}
solver.solver('bonmin', solver_options)



#%% ############################## run the simulation ############################

x0 = controller['x0']
u0 = np.zeros(plant['du'])

states = x0
controls = np.array([])

zvals = np.array([])
    
solver.set_value(X_target, [2,2,0,0])

for i in range(controller['Nsim']):
    solver.set_value(X_init, x0)
        
    sol = solver.solve()
    u0 = sol.value(U[:, 0])    
    
    x0[0]=x0[0]+plant['Te']*x0[2]
    x0[1]=x0[1]+plant['Te']*x0[3]
    x0[2]=x0[2]+plant['Te']*u0[0]
    x0[3]=x0[3]+plant['Te']*u0[1]
    

    controls = np.append(controls, u0)
    states   = np.append(states, x0)
    zvals    = np.append(zvals, sol.value(Z[:,0]))

controls = np.reshape(controls, (2, -1), order='F')
states   = np.reshape(states,   (4, -1), order='F')

#%% #########################  plot the results ##################################

stop_time = np.shape(controls)[1]
time = np.linspace(0, plant['Te'] * stop_time, stop_time-1)
    
fig = plt.figure()
plt.grid()

plt.xlabel('Distance on x axis (m)')
plt.ylabel('Distance on y axis (m)')
plt.suptitle('Position 2D space')

plt.plot(states[0, 0:-1], states[1, 0:-1])
plt.scatter(states[0, 0:-1], states[1, 0:-1],30,'r')

ax = fig.add_subplot(1, 1, 1)
pgon = plt.Polygon(obstacle["V"],color='g', alpha=0.5)
ax.add_patch(pgon)


fig = plt.figure()

plt.xlabel('time')
plt.ylabel('u1 and u2')
plt.suptitle('Controls')

plt.plot(time,controls[0, 0:-1])
plt.plot(time,controls[1, 0:-1])
plt.grid()

plt.show()
    