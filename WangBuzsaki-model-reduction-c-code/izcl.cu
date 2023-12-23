#include <stdio.h>
#include <iostream>
#include <math.h>


#define I	7
#define dt	0.01
#define a    0.02
#define b    0.2
#define c  -65.
#define d    6.


// Set GPU parallelization 
#define BLOCKS  4
#define THREADS 256

// Set simulation time
#define TIME_ITERATIONS 6000000l


__global__
void run(float *v, float *u)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	for(unsigned long t   = 0; t<TIME_ITERATIONS;    ++t){
		v[i] += dt*(0.04f*v[i]*v[i]+5.f*v[i]+140.f-u[i]+I);
		u[i] += dt*a*(b*v[i]-u[i]);
		if (v[i] > 30.f){
			v[i] = c;
			u[i] = u[i] + d;
		}
	}
	
}

int main(void)
{
	int N = BLOCKS*THREADS;
	float *v, *u;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&v, N*sizeof(float));
	cudaMallocManaged(&u, N*sizeof(float));
	

	// initialize arrays on the host
	for (int i = 0; i < N; i++) {
		v[i] = -70.f;
		u[i] = -14.f;
	}

	// Run kernel on the GPU
	run<<<BLOCKS, THREADS>>>(v, u);

	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();
	
	//check for errors
	cudaError_t e = cudaGetLastError();
	if(e){
		printf("ERROR (%d): %s\n",e,cudaGetErrorString(e));
	}

	// Free memory
	cudaFree(v);
	cudaFree(u);

	return 0;
}
