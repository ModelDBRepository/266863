all: wbpwl wbcl wbpol wbtbl wbmix

wbcl : wbcl.c
	gcc -o wbcl wbcl.c -lm

wbpwl: wbpwl.c
	gcc -o wbpwl wbpwl.c -lm

wbpol: wbpol.c
	gcc -o wbpol wbpol.c -lm

wbtbl: wbtbl.c
	gcc -o wbtbl wbtbl.c -lm

wbmix: wbmix.c
	gcc -o wbmix wbmix.c -lm

#============ GPU ===============#
gpu: wbcl-gpu wbpwl-gpu wbpol-gpu wbtbl-gpu wbmix-gpu

wbcl-gpu : wbcl.cu
	nvcc -o wbcl-gpu wbcl.cu

wbpwl-gpu : wbpwl.cu
	nvcc -o wbpwl-gpu wbpwl.cu

wbpol-gpu : wbpol.cu
	nvcc -o wbpol-gpu wbpol.cu

wbtbl-gpu : wbtbl.cu
	nvcc -o wbtbl-gpu wbtbl.cu

wbmix-gpu : wbmix.cu
	nvcc -o wbmix-gpu wbmix.cu

#=================================#
iz  : izcl izcl-gpu

izcl : izcl.c
	gcc -o izcl izcl.c -lm
izcl-gpu : izcl.cu
	nvcc -o izcl-gpu izcl.cu
