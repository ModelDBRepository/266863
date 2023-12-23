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
void run(float *v, float *n)
{
	int i = blockIdx.x * blockDim.x + threadIdx.x;
	float ninf, ntau, vinf, vtau;
	for(unsigned long t   = 0; t<TIME_ITERATIONS;    ++t){
		vinf = (v[i]+61.);
		vinf = (I+5e-4*vinf*vinf*(55.-v[i])-0.13)* ((v[i]<-61.)?(1. + 0.034*(61.+v[i])):1.);
		vtau =(v[i]>-38.)? 0.2:((-38.-v[i])*0.05+0.2);

		ninf =  (0.0964837408311+0.00095221890206*v[i])+\
				((v[i]>-71.0303053169)?(0.743014681244+0.0104605305852*v[i]):0.)+\
				((v[i]>-4.02151450044)?(-0.0343121915059+-0.00853215660471*v[i]):0.);
		ntau =  (3.89986986823+0.0365576715394*v[i])+\
				((v[i]>-60.3962620374)?(-4.73857532036+-0.0784580893008*v[i]):0.)+\
				((v[i]>-26.7339539639)?(1.09061524502+0.0407951344007*v[i]):0.);
		

		n[i] += dt*(ninf - n[i])/ntau;
		v[i] += dt*(vinf-gk*n[i]*n[i]*n[i]*n[i]*(v[i]-ek))/vtau;
	}
	
}

int main(void)
{
	int N = BLOCKS*THREADS;
	float *v, *n;

	// Allocate Unified Memory – accessible from CPU or GPU
	cudaMallocManaged(&v, N*sizeof(float));
	cudaMallocManaged(&n, N*sizeof(float));

	// initialize arrays on the host
	for (int i = 0; i < N; i++) {
		v[i] = -63.f;
		n[i] = 0.f;
	}

	// Run kernel on the GPU
	run<<<BLOCKS, THREADS>>>(v, n);

	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();
	
	//check for errors
	cudaError_t e = cudaGetLastError();
	if(e){
		printf("ERROR (%d): %s\n",e,cudaGetErrorString(e));
	}

	// Free memory
	cudaFree(v);
	cudaFree(n);

	return 0;
}
