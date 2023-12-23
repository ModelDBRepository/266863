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

double Minf(double v){
	return (0.0313077505826+0.000327941702344*v)+\
	((v>-63.8824871877)?(0.984216321118+0.0154066687827*v):0.)+\
	((v>-6.79083019467)?(-0.0960057625861+-0.0141375590074*v):0.);
};

double Hinf(double v){
	return (0.961765215359+-0.000371676284993*v)+\
	((v>-81.574862488)?(-1.32606283442+-0.0162557777479*v):0.)+\
	((v>-25.0499306576)?(0.397064011884+0.0158509026357*v):0.);
}

double Ninf(double v){
	return (0.0964837408311+0.00095221890206*v)+\
	((v>-71.0303053169)?(0.743014681244+0.0104605305852*v):0.)+\
	((v>-4.02151450044)?(-0.0343121915059+-0.00853215660471*v):0.);
}

double Htau(double v){
	return (3.89986986823+0.0365576715394*v)+\
	((v>-60.3962620374)?(-4.73857532036+-0.0784580893008*v):0.)+\
	((v>-26.7339539639)?(1.09061524502+0.0407951344007*v):0.);
}

double Ntau(double v){
	return (1.78046831377+0.00985969575028*v)+\
	((v>-57.5852330206)?(-1.29845989067+-0.0225484872173*v):0.)+\
	((v>5.61104313787)?(-0.0499171171021+0.00889622764887*v):0.);
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
