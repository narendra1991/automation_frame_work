#pragma once
#include "exp_gp_common.h"
#include "exp_gp_error.h"

#define GP_MSG_BASE_INTVAL 1000
//#define GP_ERR_BASE_INTVAL GP_MSG_BASE_INTVAL

#define GP_MSG_SEN_D_BASE 1000
#define GP_MSG_SKY_D_BASE 2000
#define GP_MSG_BCK_D_BASE 3000
#define GP_MSG_DEV_D_BASE 4000
#define GP_MSG_VID_D_BASE 5000
#define GP_MSG_LLC_D_BASE 6000

#define GP_MSG_SYN (GP_MSG_SNT_D_BASE + 10)
#define GP_MSG_ACK (GP_MSG_SNT_D_BASE + 11)
#define GP_MSG_ARM (GP_MSG_SNT_D_BASE + 20)

#define GP_MSG_PRIORITY_HIGHEST 0x01
#define GP_MSG_PRIORITY_LEAST	0x0F

#define GP_MSG_TYPE_CMD 		0
#define GP_MSG_TYPE_CMD_RESP 	1
#define GP_MSG_TYPE_DATA		2
#define GP_MSG_TYPE_REQ			3
#define GP_MSG_TYPE_REQ_RESP	4

#define GP_MSG_HDR_LEN 			(12)

typedef struct 
{
	GPUint32 	mnID;
	GPUint32 	mnTS;
	GPUint16 	mnCount;
	GPUint16	mnLength;	
}tGP_MsgHeader;

typedef struct
{
	tGP_MsgHeader	mHdr;
	GPUint8			mpData[1];
}tGP_Msg;

typedef struct 
{
	GPUint32 	mnTS;
	GPUint16 	mnCount; 
	GPUint16	mnLength;	
	GPInt16 	mnMsgID;
	GPUint16 	mnPriority;
	GPUint16 	mnMsgType;
	GPBool 		mbAckReq;				
}tGP_MsgHeader_Ext;


GPResult gGP_MarshallMessageHdr(tGP_MsgHeader *apIOHdr,	tGP_MsgHeader_Ext *apIHdrExt);

GPResult gGP_UnMarshallMessageHdr(tGP_MsgHeader *apIOHdr, tGP_MsgHeader_Ext *apIHdrExt);
							
