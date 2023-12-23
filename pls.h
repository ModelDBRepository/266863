#ifndef __PLS_H__
#define __PLS_H__
//Core Functions
#define P1(X,X0)       ((X0)-(X))
#define P2(X,X0,X1)    (P1((X),(X0))*P1((X),(X1)))
#define P32(X,X0,X1)   (P1((X),(X0))*P1((X),(X0))*P1((X),(X1)))
#define P3(X,X0,X1,X2) (P1((X),(X0))*P1((X),(X1))*P1((X),(X2)))

#define L0(X,X0,Y0,A0) ((Y0)+(A0)*((X)-(X0)))
#define L1(X,X0,Y0,A0,A1) (((X) <= (X0))?L0((X),(X0),(Y0),(A0)):L0((X),(X0),(Y0),(A1)))
#define L2(X,X0,Y0,X1,Y1,A0,A2) (((X) <= (X0))?L0((X),(X0),(Y0),(A0)):L1((X),(X1),(Y1),((Y1)-(Y0))/((X1)-(X0)),(A2)))
#define L3(X,X0,Y0,X1,Y1,X2,Y2,A0,A3) (((X) <= (X0))?L0((X),(X0),(Y0),(A0)):L2((X),(X1),(Y1),(X2),(Y2),((Y1)-(Y0))/((X1)-(X0)),(A3)))

#define S1(X,X0,Y0,Y1)  (((X)<(X0))?((Y0)):(((X)>(X0))?((Y1)):(((Y1)+(Y0))*0.5)))
#define S2(X,X0,X1,Y0,Y1,Y2) (S1((X),(X0),(Y0),S1((X),(X1),(Y1),(Y2))))
#define S3(X,X0,X1,X2,Y0,Y1,Y2,Y3) (S1((X),(X0),(Y0),S2((X),(X1),(X2),(Y1),(Y2),(Y3))))

#endif //__PLS_H__