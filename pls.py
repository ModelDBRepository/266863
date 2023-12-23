from numpy import *
#from sympy import *

P1  = lambda x,x1                      : x1-x
P2  = lambda x,x1,x2                   : P1(x,x1)*P1(x,x2)
P32 = lambda x,x1,x2                   : P1(x,x2)*P1(x,x1)**2
P3  = lambda x,x1,x2,x3                : P2(x,x1,x2)*P1(x,x3)
L0  = lambda x,x0,y0,a                 : y0 + a*(x-x0)
L1  = lambda x,x0,y0,a0,a1             : L0(x,x0,y0,a0) if x<=x0 else L0(x,x0,y0,a1)
L2  = lambda x,x0,y0,x1,y1,a0,a2       : L0(x,x0,y0,a0) if x<=x0 else L1(x,x1,y1,(y1-y0)/(x1-x0),a2)
L3  = lambda x,x0,y0,x1,y1,x2,y2,a0,a3 : L0(x,x0,y0,a0) if x<=x0 else L2(x,x1,y1,x2,y2,(y1-y0)/(x1-x0),a3)
S1  = lambda x,x0,y0,y1                : y0 if x < x0 else (y1 if x >x0 else (y0+y1)/2)
S2  = lambda x,x0,x1,y0,y1,y2          : S1(x,x0,y0,S1(x,x1,y1,y2) )
S3  = lambda x,x0,x1,x2,y0,y1,y2,y3    : S1(x,x0,y0,S2(x,x1,x2,y1,y2,y3))

symP1  = lambda symX,x,x1                      : x1-symX
symP2  = lambda symX,x,x1,x2                   : symP1(symX,x,x1)*symP1(symX,x,x2)
symP32 = lambda symX,x,x1,x2                   : symP1(symX,x,x2)*symP1(symX,x,x1)**2
symP3  = lambda symX,x,x1,x2,x3                : symP2(symX,x,x1,x2)*symP1(symX,x,x3)
symL0  = lambda symX,x,x0,y0,a                 : y0 + a*(symX-x0)
symL1  = lambda symX,x,x0,y0,a0,a1             : symL0(symX,x,x0,y0,a0) if x<=x0 else symL0(symX,x,x0,y0,a1)
symL2  = lambda symX,x,x0,y0,x1,y1,a0,a2       : symL0(symX,x,x0,y0,a0) if x<=x0 else symL1(symX,x,x1,y1,(y1-y0)/(x1-x0),a2)
symL3  = lambda symX,x,x0,y0,x1,y1,x2,y2,a0,a3 : symL0(symX,x,x0,y0,a0) if x<=x0 else symL2(symX,x,x1,y1,x2,y2,(y1-y0)/(x1-x0),a3)
symS1  = lambda symX,x,x0,y0,y1                : y0 if x < x0 else (y1 if x >x0 else (y0+y1)/2)
symS2  = lambda symX,x,x0,x1,y0,y1,y2          : symS1(symX,x,x0,y0,symS1(symX,x,x1,y1,y2) )
symS3  = lambda symX,x,x0,x1,x2,y0,y1,y2,y3    : symS1(symX,x,x0,y0,symS2(symX,x,x1,x2,y1,y2,y3))

