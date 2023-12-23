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
inline double na(double v);
inline double nb(double v);
inline double ha(double v);
inline double hb(double v);


double Minf(double v){
	double a = 0.1*(v+35.)/(1.0-exp(-(v+35.)/10.)) ;
	double b = 4.0*exp(-(v+60.)/18.);
	return a/(a+b);
};

double ha(double v) { return 0.07*exp(-(v+58.)/20.);               };
double hb(double v) { return 1.0/(1.0+exp(-(v+28.)/10.));          };

double na(double v) { return 0.01*(v+34.)/(1.0-exp(-(v+34.)/10.)); };
double nb(double v) { return 0.125*exp(-(v+44.)/80.);              };


int main(int argc, char** argv){
	int t = 0;
	double n=0, h=0, minf, ninf, hinf, ntau, htau, a, b, v=-63.;
	for(; t<60000000; ++t){
		minf = Minf(v);
		
		a = na(v);
		b = nb(v);
		ninf =  a/(a+b);
		ntau = 1./(a+b);
		
		a = ha(v);
		b = hb(v);
		hinf =  a/(a+b);
		htau = 1./(a+b);

		n += dt*(ninf - n)/ntau;
		h += dt*(hinf - h)/htau;
		v += dt*(-gna*minf*minf*minf*h*(v-ena)-gk*n*n*n*n*(v-ek)-gl*(v-el)+I);
		//printf("%g %g\n",dt*t,v);
	}
	return 0;
}
