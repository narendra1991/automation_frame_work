#ifndef EXP_GP_COMMON_H
#define EXP_GP_COMMON_H

#include <stdio.h>

typedef void*				GPHndl;

typedef signed char 		GPInt8;
typedef signed short 		GPInt16;
typedef signed int 			GPInt32;
typedef signed long long 	GPInt64;

typedef unsigned char 		GPUint8;
typedef unsigned short 		GPUint16;
typedef unsigned int		GPUint32;
typedef unsigned long long 	GPUint64;

typedef float			GPFlt32;
typedef double			GPFlt64;

typedef GPInt32			GPResult;

typedef enum
{
	kFALSE = 0,
	kTRUE,
}GPBool;

#endif
