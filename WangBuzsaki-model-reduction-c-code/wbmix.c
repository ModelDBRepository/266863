#include <stdio.h>
#include <math.h>

#define I	7
#define gna	35.
#define gk	9.
#define gl	0.1
#define ena	55.
#define ek	(-90.)
#define el	(-65.)
#define dt	0.01

inline double Ninf(double v);
inline double Ntau(double v);

double Ninf(double v){
	return (0.0964837408311+0.00095221890206*v)+\
	((v>-71.0303053169)?(0.743014681244+0.0104605305852*v):0.)+\
	((v>-4.02151450044)?(-0.0343121915059+-0.00853215660471*v):0.);
}
double Ntau(double v){
	return (1.78046831377+0.00985969575028*v)+\
	((v>-57.5852330206)?(-1.29845989067+-0.0225484872173*v):0.)+\
	((v>5.61104313787)?(-0.0499171171021+0.00889622764887*v):0.);
}





int main(int argc, char** argv){
	int t = 0;
	double vinf, vtau, ninf, ntau, v=-63.,n=0;
	for(; t<60000000; ++t){
		vinf = (v+61.);
		vinf = (I+5e-4*vinf*vinf*(55.-v)-0.13)* ((v<-61.)?(1. + 0.034*(61.+v)):1.);
		vtau =(v>-38.)? 0.2:((-38.-v)*0.05+0.2);
		ninf = Ninf(v);
		ntau = Ntau(v);

		n += dt*(ninf - n)/ntau;
		v += dt*(vinf-gk*n*n*n*n*(v-ek))/vtau;
		//printf("%g %g\n",dt*t,v);

	}
	return 0;
}
