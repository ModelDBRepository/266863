#include <stdio.h>
#include <iostream>
#include <math.h>


#define I	7
#define gna	35.
#define gk	9.
#define gl	0.1
#define ena	55.
#define ek	(-90.)
#define el	(-65.)
#define dt	0.01

// Set GPU parallelization 
#define BLOCKS  4
#define THREADS 256

// Set simulation time
#define TIME_ITERATIONS 6000000l

__global__
void run(float *v, float *h, float *n)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	float minf, hinf, htau, ninf, ntau, a, b, vm, dv=(ena-ek)/201., ras;
	float tbl[201][6];
	int  vi;
	for(unsigned long t=0; t<20l; t++){
		tbl[t][0] = vm = ek+dv*t;
		a = 0.1*(vm+35.)/(1.0-exp(-(vm+35.)/10.)) ;
		b = 4.0*exp(-(vm+60.)/18.);
		tbl[t][1] = a/(a+b);
		a = 0.07*exp(-(vm+58.)/20.);
		b = 1.0/(1.0+exp(-(vm+28.)/10.));
		tbl[t][2] =  a/(a+b);
		tbl[t][3] = 1./(a+b);
		a = 0.01*(vm+34.)/(1.0-exp(-(vm+34.)/10.));
		b = 0.125*exp(-(vm+44.)/80.);
		tbl[t][4] =  a/(a+b);
		tbl[t][5] = 1./(a+b);
	}
	for(unsigned long t   = 0; t<TIME_ITERATIONS;    ++t){
		vi = (int)floor((v[i]-ek)/dv);
		ras   = (v[i] - tbl[vi][0])/dv;
		minf = tbl[vi][1] + (tbl[vi+1][1] - tbl[vi][1])*ras;
		hinf = tbl[vi][2] + (tbl[vi+1][2] - tbl[vi][2])*ras;
		htau = tbl[vi][3] + (tbl[vi+1][3] - tbl[vi][3])*ras;
		ninf = tbl[vi][4] + (tbl[vi+1][4] - tbl[vi][4])*ras;
		ntau = tbl[vi][5] + (tbl[vi+1][5] - tbl[vi][5])*ras;
		
		n[i] += dt*(ninf - n[i])/ntau;
		h[i] += dt*(hinf - h[i])/htau;
		v[i] += dt*(-gna*minf*minf*minf*h[i]*(v[i]-ena)-gk*n[i]*n[i]*n[i]*n[i]*(v[i]-ek)-gl*(v[i]-el)+I);
	}
	
}

int main(void)
{
	int N = BLOCKS*THREADS;
	float *v, *h, *n;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&v, N*sizeof(float));
	cudaMallocManaged(&h, N*sizeof(float));
	cudaMallocManaged(&n, N*sizeof(float));

	// initialize arrays on the host
	for (int i = 0; i < N; i++) {
		v[i] = -63.f;
		h[i] = n[i] = 0.f;
	}

	// Run kernel on the GPU
	run<<<BLOCKS, THREADS>>>(v, h, n);

	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();
	
	//check for errors
	cudaError_t e = cudaGetLastError();
	if(e){
		printf("ERROR (%d): %s\n",e,cudaGetErrorString(e));
	}

	// Free memory
	cudaFree(v);
	cudaFree(h);
	cudaFree(n);

	return 0;
}
