
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuComplex.h"
#include <vector>
#include "CPUSingleThread.h"
#include <math.h>
#include <stdio.h>
#include "cuda/std/cmath"
#include <Windows.h>

// Cuda Device function to calculate Complex Exponents
__device__ cuDoubleComplex CuCmplxExp(double base, cuDoubleComplex exp)
{
    cuDoubleComplex res;
    float r, i;
    
    sincosf(exp.y * logf(base), &i, &r); // sincosf may show up as error, but compiles with nvcc
    res.x = pow(base, exp.x) * r;
    res.y = pow(base, exp.x) * i;
    return res;
}

// Equivelant function to calculate Complex Exponents for the host device
//__device__ cuDoubleComplex CuCmplxExp(double base, cuDoubleComplex exp)
//{
//    cuDoubleComplex res;
//    float r, i;
//
//    sincosf(exp.y * logf(base), &r, &i);
//    res.x = base * r;
//    res.y = base * i;
//    return res;
//}

__global__ void addKernel(cuDoubleComplex *CudaInput, cuDoubleComplex*CudaOutput, int accuracy, int size, int KernelNum)
{
    
    int i = blockDim.x * blockIdx.x + threadIdx.x + KernelNum;
    CudaOutput[i] = make_cuDoubleComplex(0, 0);
    if (i < size) {
        
        for (int c1 = 1; c1 < accuracy; c1++) {

            if ((c1 % 2) == 0) {
                CudaOutput[i] = cuCsub(CudaOutput[i], cuCdiv(make_cuDoubleComplex(1, 0), CuCmplxExp((double)c1, CudaInput[i])));
                
            }
            else {
                CudaOutput[i] = cuCadd(CudaOutput[i], cuCdiv(make_cuDoubleComplex(1, 0), CuCmplxExp((double)c1, CudaInput[i])));
            }
            
        }

    }
}

//Function to Generate Reiman Values using CUDA
std::vector <RiemanPair> GenerateValuesCuda(double ymin, double ymax, double step, double accuracy)
{
    std::vector<cuDoubleComplex> BaseValues;

    for (double c1 = ymin; c1 < ymax; c1 += step) {
        BaseValues.emplace_back(make_cuDoubleComplex(0.5, c1));
    }

    int size = BaseValues.size();
    
    cuDoubleComplex* InputValues = new cuDoubleComplex[BaseValues.size()];
    cuDoubleComplex* ReturnValues = new cuDoubleComplex[BaseValues.size()];
    InputValues = BaseValues.data();


    cuDoubleComplex*CudaInput = 0;
    cuDoubleComplex*CudaOutput = 0;

    

    cudaError_t cudaStatus;
    cudaStatus = cudaSetDevice(0);


    cudaStatus = cudaMalloc((void**)&CudaInput, BaseValues.size() * sizeof(cuDoubleComplex));
    cudaStatus = cudaMalloc((void**)&CudaOutput, BaseValues.size() * sizeof(cuDoubleComplex));


    cudaStatus = cudaMemcpy(CudaInput, InputValues, BaseValues.size() * sizeof(cuDoubleComplex), cudaMemcpyHostToDevice);
    cudaStatus = cudaMemcpy(CudaOutput, ReturnValues, BaseValues.size() * sizeof(cuDoubleComplex), cudaMemcpyHostToDevice);



    for (int KernelNumber = 0; KernelNumber <= (ceil((float)BaseValues.size() / (32 * 32))); KernelNumber++) {
        addKernel << <32, 32 >> > (CudaInput, CudaOutput, accuracy, BaseValues.size(), (32*32)*KernelNumber);
        
        cudaStatus = cudaGetLastError();
        if (cudaSuccess != cudaStatus) {

            fprintf(stderr, "Cuda error: %s.\n",
            cudaGetErrorString(cudaStatus));
            exit(EXIT_FAILURE);

        }
    }


    cudaStatus = cudaDeviceSynchronize();
    cudaStatus = cudaMemcpy(ReturnValues, CudaOutput, BaseValues.size() * sizeof(cuDoubleComplex), cudaMemcpyDeviceToHost);

    std::vector<RiemanPair> ReturnData;

    for (int i = 0; i < BaseValues.size(); i++) {
        ReturnData.emplace_back(
            std::complex<double>(InputValues[i].x, InputValues[i].y),
            std::complex<double>(ReturnValues[i].x, ReturnValues[i].y)
        );

    }
    cudaFree(CudaInput);
    cudaFree(CudaOutput);
    
    return ReturnData;
}
