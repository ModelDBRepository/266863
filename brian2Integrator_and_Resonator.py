from brian2 import *
from brian2pls import *

set_device('cpp_standalone', directory='CODE')
prefs.devices.cpp_standalone.openmp_threads = 1

###  Type 1  ###
#--- v_\infty
T1v0,T1v1,T1v2 = -65.,-45., 55.
T1a0,T1a1      = 3.6e-6,-1e-4
T1vmin,T1vmax  = -55.45176241886681, 18.78509575220014
#--- \tau_v
T1v3           = -35.
T1r0,T1r1      = 0.04, -0.004
#--- w_\infty
T1v4,T1v5      = -40.,-5
#--- \tau_w
T1v6,T1v7      = T1vmin,T1vmax
T1s0,T1s1,T1s2 = 5.,7.6,1.8
T1equ="""
dv/dt = ( P3(v,T1v0,T1v1,T1v2)*L1(v,T1v0,T1a0,T1a1,0)+I*int(t>200*ms)-w*w )/L1(v,T1v3,T1r0,T1r1,0)/ms : 1
dw/dt = ( L2(v,T1v4,0,T1v5,1,0,0) - w )/S2(v,T1v6,T1v7,T1s0,T1s1,T1s2)/ms               : 1
I : 1
"""
plsT1 = NeuronGroup(1,T1equ,threshold="v>30")
rT1   = StateMonitor(plsT1,['v','w'],record=True)
plsT1.v =-65.
plsT1.w = 0.
plsT1.I = 0.07

###  Type 2  ###
T2v0,T2v2       = -65., 55.
T2a0,T2a1      = 3.25e-6,-1e-4
#--- \tau_v
T2v3           = -35.
T2r0,T2r1      = 0.04, -0.004
#--- n_\infty
T2v4,T2v5      = -75.,-7.
#--- \tau_n
T2v6,T2v7      = -55.5,18.
T2s0,T2s1,T2s2 = 5.,7.6,1.8
T2equ="""
dv/dt = ( P32(v,T2v0,T2v2)*L1(v,T2v0,T2a0,T2a1,0)+I*int(t>200*ms)-w*w )/L1(v,T2v3,T2r0,T2r1,0)/ms : 1
dw/dt = ( L2(v,T2v4,0,T2v5,1,0,0) - w )/S2(v,T2v6,T2v7,T2s0,T2s1,T2s2)/ms               : 1
I : 1
"""
plsT2 = NeuronGroup(1,T2equ,threshold="v>30")
rT2   = StateMonitor(plsT1,['v','w'],record=True)
plsT2.v =-65.
plsT2.w = 0.
plsT2.I = 0.07

run(1000*ms)
figure(1,figsize=(16,8))
subplot(231)
title("Type 1 Integrator",fontsize=18)
plot(rT1.t/ms,rT1.v[0])
ylabel("v")
subplot(232)
plot(rT1.t/ms,rT1.w[0])
ylabel("w")
subplot(233)
ylabel("w")
xlabel("v")
x = linspace(-67,55,(55+67)*10)
plot(rT1.v[0],rT1.w[0],lw=2)
plot(x,sqrt(vectorize(P3)(x,T1v0,T1v1,T1v2)*vectorize(L1)(x,T1v0,T1a0,T1a1,0)        ),"k-")
plot(x,sqrt(vectorize(P3)(x,T1v0,T1v1,T1v2)*vectorize(L1)(x,T1v0,T1a0,T1a1,0)+plsT1.I),"k--")
plot(x,vectorize(L2)(x,T1v4,0,T1v5,1,0,0),"-",lw=3)

subplot(234)
title("Type 2 Resonator",fontsize=18)
plot(rT2.t/ms,rT2.v[0])
ylabel("v")
subplot(235)
plot(rT2.t/ms,rT2.w[0])
ylabel("w")
subplot(236)
ylabel("w")
xlabel("v")
x = linspace(-67,55,(55+67)*10)
plot(rT2.v[0],rT2.w[0],lw=2)
plot(x,sqrt(vectorize(P32)(x,T2v0,T2v2)*vectorize(L1)(x,T2v0,T2a0,T2a1,0)        ),"k-")
plot(x,sqrt(vectorize(P32)(x,T2v0,T2v2)*vectorize(L1)(x,T2v0,T2a0,T2a1,0)+plsT2.I),"k--")
plot(x,vectorize(L2)(x,T2v4,0,T2v5,1,0,0),"-",lw=3)
show()
