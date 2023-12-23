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
		minf =  (0.0313077505826+0.000327941702344*v[i])+\
				((v[i]>-63.8824871877)?(0.984216321118+0.0154066687827*v[i]):0.)+\
				((v[i]>-6.79083019467)?(-0.0960057625861+-0.0141375590074*v[i]):0.);
		
		ninf =  (0.0964837408311+0.00095221890206*v[i])+\
				((v[i]>-71.0303053169)?(0.743014681244+0.0104605305852*v[i]):0.)+\
				((v[i]>-4.02151450044)?(-0.0343121915059+-0.00853215660471*v[i]):0.);
		ntau =  (3.89986986823+0.0365576715394*v[i])+\
				((v[i]>-60.3962620374)?(-4.73857532036+-0.0784580893008*v[i]):0.)+\
				((v[i]>-26.7339539639)?(1.09061524502+0.0407951344007*v[i]):0.);
		
		hinf =  (0.961765215359+-0.000371676284993*v[i])+\
				((v[i]>-81.574862488)?(-1.32606283442+-0.0162557777479*v[i]):0.)+\
				((v[i]>-25.0499306576)?(0.397064011884+0.0158509026357*v[i]):0.);
		htau = 	(1.78046831377+0.00985969575028*v[i])+\
				((v[i]>-57.5852330206)?(-1.29845989067+-0.0225484872173*v[i]):0.)+\
				((v[i]>5.61104313787)?(-0.0499171171021+0.00889622764887*v[i]):0.);

		n[i] += dt*(ninf - n[i])/ntau;
		h[i] += dt*(hinf - h[i])/htau;
		v[i] += dt*(-gna*minf*minf*minf*h[i]*(v[i]-ena)-gk*n[i]*n[i]*n[i]*n[i]*(v[i]-ek)-gl*(v[i]-el)+I);
		//printf("%g %g\n",dt*t,v);
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
