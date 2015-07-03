#ifndef EXP_GP_PRIORITYQUEUE_H
#define EXP_GP_PRIORITYQUEUE_H

#include "exp_gp_common.h"

typedef GPResult (*fPriorityQueue_Print)(GPHndl, GPInt32);

GPResult gGP_PriorityQueue_Display(GPHndl apQ, fPriorityQueue_Print apFunc);

GPResult gGP_PriorityQueue_Init(GPHndl *apQ);

GPResult gGP_PriorityQueue_EnQ(GPHndl apQ, GPHndl data, GPInt32 anPriority);

GPResult gGP_PriorityQueue_DeQ(GPHndl apQ, void **data);

GPResult gGP_PriorityQueue_Deinit(GPHndl apQ);

#endif
