#include <stdio.h>
#include <iostream>
#include <math.h>
// Kernel function to add the elements of two arrays

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
	float minf, ninf, hinf, ntau, htau;
	for(unsigned long t   = 0; t<TIME_ITERATIONS;    ++t){
		minf =  0.953881978928+v[i]*(0.00764436291528+v[i]*(-0.000176887049516+v[i]*(-1.95108741101e-07+v[i]*(1.66385198983e-08+v[i]*(1.67105570231e-11)))));
		
		ninf =  0.824494447868+v[i]*(0.00719826506481+v[i]*(-0.000110730240325+v[i]*(-1.53119478562e-07+v[i]*(9.39864044908e-09+v[i]*(3.03369442673e-12)))));
		ntau =  0.492403741388+v[i]*(-0.012052097973+v[i]*(0.00010471373932+v[i]*(1.69326656183e-06+v[i]*(-1.44449337737e-08+v[i]*(-1.12462063995e-10)))));
		
		hinf =  -0.0310904478177+v[i]*(0.00192650413623+v[i]*(8.72227960325e-05+v[i]*(-2.94688600355e-06+v[i]*(6.87296459746e-11+v[i]*(2.70678460466e-10)))));
		htau = 	 0.162350260789+v[i]*(-0.00768669406983+v[i]*(0.000298711718949+v[i]*(-8.22822927459e-07+v[i]*(-3.45692137243e-08+v[i]*(1.43004040707e-10)))));

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
