from scipy.integrate import solve_ivp
import numpy as np
import pylab          # plotting of results

def f(t, y):
    """this is the rhs of the ODE to integrate, i.e. dy/dt=f(y,t)"""
    return [-2 * y[0]+y[1],0] 

T=1

u_all=[1, 1.5, 0.9, 1, 1, 2, 0, 0, 0,0,0]
y0 = [1,u_all[0]]           # initial value y0=y(t0)

t0=0
tf=0

y_all=[]
t_all=[]

for u in u_all:
    t0 = tf             # integration limits for t: start at t0=0
    tf = t0+T             # and finish at tf=2
    
    ts = np.linspace(t0, tf, 20)  # 100 points between t0 and tf
    
    sol = solve_ivp(fun=f, t_span=[t0, tf], y0=y0, t_eval=ts)  # computation of SOLution 
    
    t_all=np.concatenate((t_all,ts),axis=0) 
    # t_all=t_all+ts       
    y_all=np.concatenate((y_all,sol.y[0]),axis=0)
    # y_all=y_all+sol.y[0]
    y0=[sol.y[0,-1],u]
    
pylab.plot(t_all, y_all, 'o-')
pylab.xlabel('t'); pylab.ylabel('y_0(t)')