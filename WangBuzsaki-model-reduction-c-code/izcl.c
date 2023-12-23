#include <stdio.h>
#include <math.h>

#define a    0.02
#define b    0.2
#define c  -65.
#define d    6.
#define v0 -70.
#define u0 -14
#define dt   0.01
#define I   14.


int main(int argc, char** argv){
	int t = 0;
	double v=v0, u=u0;
	for(; t<60000000; ++t){
		v += dt*(0.04*v*v+5*v+140-u+I);
		u += dt*a*(b*v-u);
		if (v > 30){
			v = c;
			u = u + d;
		}
	}
	return 0;
}
