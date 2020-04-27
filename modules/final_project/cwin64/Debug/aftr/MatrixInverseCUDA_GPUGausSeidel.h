#pragma once

//SLN: I found this source code on a nvidia forum:
//http://forums.nvidia.com/index.php?showtopic=81195
//Original code is in repo at: \Aftr\trunk\usr\util\CUDA MatrixInversionv1.1

#ifdef __cplusplus
   extern "C" {
#endif

#define BLOCKSIZE 16
#define BLOCKSIZEMINUS1 15

#define USELOOPUNROLLING 1  
#define AVOIDBANKCONFLICTS 0    //this just runs faster :X

int GPUGausSeidel (float* matrix, 
                   float* output, 
                   int size);

#ifdef __cplusplus
   }
#endif

