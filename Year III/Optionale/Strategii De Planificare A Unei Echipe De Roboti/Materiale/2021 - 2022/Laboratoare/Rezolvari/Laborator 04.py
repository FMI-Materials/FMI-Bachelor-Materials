# -*- coding: utf-8 -*-
"""
Created on Mon Mar  7 22:22:58 2022

@author: florin stoican - modified code from https://stackoverflow.com/questions/48428140/imitate-ode45-function-from-matlab-in-python
"""

import numpy as np
from scipy import integrate
import matplotlib.pyplot as plt

# define the forced (with input) Van der Pol oscillator
def vdp1(t, y):
    return np.array([y[1], (1 - 10*y[0]**2)*y[1] - y[0]+y[2],0])

# take a sequence of piecewise constant inputs (their values and the times at which they change)
t = [0, 3, 5, 20]
u = [1, 2, 0]

# initial state (position and velocity)
x0=1
dx0=0

i=0

# arrays in which to store the data
t_all=[]
y_all=[]

# take all sub-intervals defined by the time sequence and integrate the vdp1 function
while i<len(t)-1:
    # the integrate class integrates in points given explicitly; we construct such a time sequence
    tt = np.linspace(t[i], t[i+1], 100)  
    
    # prepare the inputs to be given to the integration procedure (initial time and initial state value)
    t0=t[i]
    y0 = [x0, dx0, u[i]]

    # prepare the array in which the state will be stored; make sure that the array is initialized with the current initial state
    y = np.zeros((len(tt), len(y0)))
    y[0, :] = y0

    # among the existing methods, chose RK45 ("Dormand Prince variant of the Runge-Kutta of order 4-5")
    r = integrate.ode(vdp1).set_integrator("dopri5")
    # set the initial value from which the integration starts
    r.set_initial_value(y0, t0)

    # for each intermediary point of the integration, call the integrate method and store the result
    for j in range(1, tt.size):
        y[j, :] = r.integrate(tt[j]) 
        if not r.successful():
            raise RuntimeError("Could not integrate")
    
    # since the procedure repeats for multiples indices i (the sub-intervals over which the control remains constant), we need to store all the time/state values
    if i == 0:
        t_all = tt
        y_all = y
    else:
        t_all = t_all + tt
        y_all = y_all + y
    
    # update the initial state of the next integration call to be the last value of the current integration
    x0=y[-1,0]
    dx0=y[-1,1]
    
    # go to the next sub-interval
    i=i+1
    
# plot the time-series (y_0(t) and y_1(t))
plt.plot(t_all, y_all[:,0:2])
plt.show()

# plot in the phase space (y_1=y_1(y_0))
plt.figure()
plt.plot(y_all[:,0],y_all[:,1])