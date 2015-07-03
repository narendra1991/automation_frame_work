#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <sys/un.h>

#include "exp_gp_common.h"
#include "exp_gp_error.h"
#include "exp_gp_message.h"
#include "exp_gp_priorityqueue.h"

typedef struct
{
	GPInt16 nCMD_ID;
	GPInt16 nCount;
	GPInt16 nLength;
}tGP_Msg_Header;

typedef struct
{
	tGP_Msg_Header mHdr;
	GPInt8 mpData[1];
}tGP_BuckD_Msg;
