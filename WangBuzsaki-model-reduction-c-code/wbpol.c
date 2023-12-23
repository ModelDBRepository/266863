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

inline double Minf(double v);
inline double Ninf(double v);
inline double Ntau(double v);
inline double Hinf(double v);
inline double Htau(double v);

double Minf(double x){
	return 0.953881978928+x*(0.00764436291528+x*(-0.000176887049516+x*(-1.95108741101e-07+x*(1.66385198983e-08+x*(1.67105570231e-11)))));
};

double Hinf(double x){
	return -0.0310904478177+x*(0.00192650413623+x*(8.72227960325e-05+x*(-2.94688600355e-06+x*(6.87296459746e-11+x*(2.70678460466e-10)))));
}

double Ninf(double x){
	return 0.824494447868+x*(0.00719826506481+x*(-0.000110730240325+x*(-1.53119478562e-07+x*(9.39864044908e-09+x*(3.03369442673e-12)))));
}

double Htau(double x){
	return 0.162350260789+x*(-0.00768669406983+x*(0.000298711718949+x*(-8.22822927459e-07+x*(-3.45692137243e-08+x*(1.43004040707e-10)))));
}

double Ntau(double x){
	return 0.492403741388+x*(-0.012052097973+x*(0.00010471373932+x*(1.69326656183e-06+x*(-1.44449337737e-08+x*(-1.12462063995e-10)))));
}

int main(int argc, char** argv){
	int t = 0;
	double n=0, h=0, minf, ninf, hinf, ntau, htau, a, b, v=-63.;
	for(; t<60000000; ++t){
		minf = Minf(v);
		ninf = Ninf(v);
		ntau = Ntau(v);
		hinf = Hinf(v);
		htau = Htau(v);

		n += dt*(ninf - n)/ntau;
		h += dt*(hinf - h)/htau;
		v += dt*(-gna*minf*minf*minf*h*(v-ena)-gk*n*n*n*n*(v-ek)-gl*(v-el)+I);
		//printf("%g %g\n",dt*t,v);

	}
	return 0;
}
