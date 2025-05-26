from scipy.integrate import solve_ivp
import numpy as np
import pylab          # plotting of results

def f(t, zeta):
    a=-1
    """this is the rhs of the ODE to integrate, i.e. dy/dt=f(y,t)"""
    return [zeta[1], -a*(1-zeta[0]*zeta[0])*zeta[1]-zeta[0]+zeta[2],0] 

T=1

u_all=[1, 1.5, 0.9, 1, 1, 2, 0, 0, 0,0,0]
y0 = [1,1,u_all[0]]           # initial value y0=y(t0)

t0=0
tf=0

y_all=[]
t_all=[]

pylab.xlabel('t'); pylab.ylabel('y_0(t)')
test=1
for u in u_all:
    u=0.1
    t0 = tf             # integration limits for t: start at t0=0
    tf = t0+T             # and finish at tf=2
    
    ts = np.linspace(t0, tf, 20)  # 100 points between t0 and tf
    
    sol = solve_ivp(fun=f, t_span=[t0, tf], y0=y0, t_eval=ts)  # computation of SOLution 
    
    t_all=np.concatenate((t_all,sol.t),axis=0) 
      
    if test==1:
        y_all=sol.y
        test=0
    else:
        y_all=np.concatenate((y_all,sol.y),axis=1)
        
    y0=[sol.y[0,-1],sol.y[1,-1],u]
    
pylab.plot(t_all, y_all[0,], 'o-')
pylab.plot(t_all, y_all[1,], 'o-')

pylab.figure()
pylab.plot(y_all[0,],y_all[1,], 'o-')