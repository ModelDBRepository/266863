from brian2 import *
##############################
###       Polynomial       ###
##############################
@implementation('cpp', '''
#define P1(X,X0)       ((X0)-(X))
''')
@implementation('cython', '''
cdef double P1(double X, double X0):
    return (X0-X)
''')
@check_units(arg=[1,1], result=1)
def P1(X,X0):
    return X0-X

@implementation('cpp', '''
#define P2(X,X0,X1)    (P1((X),(X0))*P1((X),(X1)))
''',dependencies={'P1':P1})
@implementation('cython', '''
cdef double P2(double X, double X0, double X1):
    return P1(X,X0)*P1(X,X1)
''',dependencies={'P1':P1})
@check_units(arg=[1,1,1], result=1)
def P2(X,X0,X1):
    return P1(X,X0)*P1(X,X1)

@implementation('cpp', '''
#define P32(X,X0,X1)   (P1((X),(X0))*P1((X),(X0))*P1((X),(X1)))
''',dependencies={'P1':P1})
@implementation('cython', '''
cdef double P32(double X, double X0, double X1):
    return P1(X,X0)*P1(X,X0)*P1(X,X1)
''',dependencies={'P1':P1})
@check_units(arg=[1,1,1], result=1)
def P32(X,X0,X1):
    return P1(X,X0)*P1(X,X0)*P1(X,X1)

    
@implementation('cpp', '''
#define P3(X,X0,X1,X2) (P1((X),(X0))*P1((X),(X1))*P1((X),(X2)))
''',dependencies={'P1':P1})
@implementation('cython', '''
cdef double P3(double X, double X0, double X1, double X2):
    return P1(X,X0)*P1(X,X1)*P1(X,X2)
''',dependencies={'P1':P1})
@check_units(arg=[1,1,1,1], result=1)
def P3(X,X0,X1,X2):
    return P1(X,X0)*P1(X,X1)*P1(X,X2)

##############################
###    piecewise-Linear    ###
##############################
@implementation('cpp', '''
#define L0(X,X0,Y0,A0) ((Y0)+(A0)*((X)-(X0)))
''')
@implementation('cython', '''
cdef double L0(double X, double X0, double Y0, double A0):
    return Y0+A0*(X-X0)
''')
@check_units(arg=[1,1,1,1], result=1)
def L0(X,X0,Y0,A0):
    return Y0+A0*(X-X0)

@implementation('cpp', '''
#define L1(X,X0,Y0,A0,A1) (((X) <= (X0))?L0((X),(X0),(Y0),(A0)):L0((X),(X0),(Y0),(A1)))
''',dependencies={'L0':L0})
@implementation('cython', '''
cdef double L1(double X, double X0, double Y0, double A0, double A1):
    return L0(X,X0,Y0,A0) if X <= X0 else L0(X,X0,Y0,A1)
''',dependencies={'L0':L0})
@check_units(arg=[1,1,1,1,1], result=1)
def L1(X,X0,Y0,A0,A1):
    return L0(X,X0,Y0,A0) if X <= X0 else L0(X,X0,Y0,A1)

@implementation('cpp', '''
#define L2(X,X0,Y0,X1,Y1,A0,A2) (((X) <= (X0))?L0((X),(X0),(Y0),(A0)):L1((X),(X1),(Y1),((Y1)-(Y0))/((X1)-(X0)),(A2)))
''',dependencies={'L0':L0,'L1':L1})
@implementation('cython', '''
cdef double L2(double X, double X0, double Y0, double X1, double Y1, double A0, double A2):
    return L0(X,X0,Y0,A0) if X <= X0 else L1(X,X1,Y1,(Y1-Y0)/(X1-X0),A2)
''',dependencies={'L0':L0,'L1':L1})
@check_units(arg=[1,1,1,1,1,1,1], result=1)
def L2(X,X0,Y0,X1,Y1,A0,A2):
    return L0(X,X0,Y0,A0) if X <= X0 else L1(X,X1,Y1,(Y1-Y0)/(X1-X0),A2)

@implementation('cpp', '''
#define L3(X,X0,Y0,X1,Y1,X2,Y2,A0,A3) (((X) <= (X0))?L0((X),(X0),(Y0),(A0)):L2((X),(X1),(Y1),(X2),(Y2),((Y1)-(Y0))/((X1)-(X0)),(A3)))
''',dependencies={'L0':L0,'L2':L2})
@implementation('cython', '''
cdef double L3(double X, double X0, double Y0, double X1, double Y1, double X2, double Y2, double A0, double A3):
    return L0(X,X0,Y0,A0) if X <= X0 else L2(X,X1,Y1,X2,Y2,(Y1-Y0)/(X1-X0),A3)
''',dependencies={'L0':L0,'L2':L2})
@check_units(arg=[1,1,1,1,1,1,1,1,1], result=1)
def L3(X,X0,Y0,X1,Y1,X2,Y2,A0,A3):
    return L0(X,X0,Y0,A0) if X <= X0 else L2(X,X1,Y1,X2,Y2,(Y1-Y0)/(X1-X0),A3)


##############################
###          Step          ###
##############################
@implementation('cpp', '''
#define S1(X,X0,Y0,Y1)  (((X)<(X0))?((Y0)):(((X)>(X0))?((Y1)):(((Y1)+(Y0))*0.5)))
''')
@implementation('cython', '''
cdef double S1(double X, double X0, double Y0, double Y1):
    return Y0 if X < X0 else ( Y1 if X > X0 else (Y1+Y0)*0.5 )
''')
@check_units(arg=[1,1,1,1], result=1)
def S1(X,X0,Y0,Y1):
    return Y0 if X < X0 else ( Y1 if X > X0 else (Y1+Y0)*0.5 )

@implementation('cpp', '''
#define S2(X,X0,X1,Y0,Y1,Y2) (S1((X),(X0),(Y0),S1((X),(X1),(Y1),(Y2))))
''',dependencies={'S1':S1})
@implementation('cython', '''
cdef double S2(double X, double X0, double X1, double Y0, double Y1, double Y2):
    return S1(X,X0,Y0,S1(X,X1,Y1,Y2))
''',dependencies={'S1':S1})
@check_units(arg=[1,1,1,1,1,1], result=1)
def S2(X,X0,X1,Y0,Y1,Y2):
    return S1(X,X0,Y0,S1(X,X1,Y1,Y2))

@implementation('cpp', '''
#define S3(X,X0,X1,X2,Y0,Y1,Y2,Y3) (S1((X),(X0),(Y0),S2((X),(X1),(X2),(Y1),(Y2),(Y3))))
''',dependencies={'S1':S1,'S2':S2})
@implementation('cython', '''
cdef double S3(double X, double X0, double X1, double X2, double Y0, double Y1, double Y2, double Y3):
    return S1(X,X0,Y0,S2(X,X1,X2,Y1,Y2,Y3))
''',dependencies={'S1':S1,'S2':S2})
@check_units(arg=[1,1,1,1,1,1,1,1], result=1)
def S3(X,X0,X1,X2,Y0,Y1,Y2,Y3):
    return S1(X,X0,Y0,S2(X,X1,X2,Y1,Y2,Y3))


