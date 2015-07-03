#include "gpTestBuckD.h"

#define SOCK_PATH_SERVER "/tmp/sen_bck_sen"

int createsock();
int connectsock();
int execute_testcase(char *argv[]);

tGP_Msg *buf;
//tGP_BuckD_Msg *buf;
struct sockaddr_un remote;
int sock,rval;
//void *str;
char *str;
int count=180;
FILE *rfp = NULL;

int main(int argc, char *argv[])
{
	int status,i,num_itera;
	pid_t child_pid, wpid, pid;
	str = (char *)malloc(100);	
	
	rfp = fopen("test_result.txt", "w");
	if (argc < 2) 
		{ 
			printf("\n[QA] : enter test_id as 1000\n");
			printf("\n[QA] : usage:%s <test_id>\n", argv[0]);
			return 1; 
		}

	if(atoi(argv[1]) != 1000)
		{
			printf("\n[QA] : invalid test id\n");
			return 1;		
		}
	
	//printf("\n[QA] : enter the iterations\n");
	//scanf("%d",&num_itera);
	printf("\n\n\n\n\n");
	
	//for(i=0;i<num_itera;i++)
	//{
	//printf("[QA] : Starting iteration %d\n",i);
	child_pid = fork();
	if (child_pid == 0)
	{
		printf("[QA] : In child process : BuckD start\n");
		pid = getpid();
		printf("[QA] : pid in child process is %d\n", pid);
		execv("./BuckD",NULL);
		//sleep(60);
	}
	if(child_pid > 0)
	{
			printf("[QA] : In parent process : gpTestBuckD start\n");
			pid = getpid();
			printf("[QA] : pid in parent process is %d\n", pid);
			sleep(5);
			printf("[QA] : Complete parent process\n");
			createsock();
			connectsock();
			execute_testcase(argv);
			kill (child_pid, SIGTERM);;
			close(sock);
	}
	//printf("[QA] : End of iteration %d\n\n\n\n",i);
	//}
fclose(rfp);
return 0;
}

int createsock()
{
		printf( "\n[QA] : Creating socket...........\n" );		
		sock = socket(AF_UNIX, SOCK_SEQPACKET, 0); 

		if (sock < 0) 
		{ 
			perror("[QA] : opening stream socket"); 
			return 1; 
		}
}

int connectsock()
{
		int n;
		printf( "\n [QA] : Doing connect.................\n" );
		remote.sun_family = AF_UNIX; 
		strcpy(remote.sun_path, SOCK_PATH_SERVER);
		//unlink(remote.sun_path);

		while(count != 0)
		{
		sleep(1);
		//if (connect(sock, (struct sockaddr *) &remote, sizeof(struct sockaddr_un)) == -1) 
		n = connect(sock, (struct sockaddr *) &remote, SUN_LEN(&remote));
		if (n == -1) 
		//if (connect(sock, NULL, NULL) == -1) 
		{
			perror("[QA] : connecting stream socket"); 
			//fprintf(rfp,"%d", 1);
			//return 1; 
		}
		if (n == 0) 
		{
		//fprintf(rfp,"%d", 0);
		break;
		}		
		count--;
		//if (count == 0) fprintf(rfp,"%d", 1);
		}
		
count=180;
}

int execute_testcase( char *argv[] )
{
		switch (atoi(argv[1]))
		{
  		case 1000:
				//memset(str, 0, 100);
				while(count != 0)
				{
					sleep(1);
					rval = recv(sock, (tGP_Msg *)str, 100,0);
					//rval = recv(sock, (tGP_BuckD_Msg *)str, 100,0);
					if (rval == 0) 
					{
					printf("[QA] : Received bytes is %d\n",rval);
					}				
					//else if (rval < 0) 
					//{
					//perror("[QA] : reading stream message"); 
					//}				
					else
					{
					buf = malloc(rval);
					//buf = (tGP_Msg *) str;
					//buf = (tGP_BuckD_Msg *) str;
					buf = str;
					printf("ip Address = %s %hd %hd %hd %hd \n",buf->mpData,
									buf->mHdr.mnID,
									buf->mHdr.mnTS,
									buf->mHdr.mnCount,
									buf->mHdr.mnLength);
					/*printf("ip Address = %s %hd %hd %hd\n",buf->mpData[1],
									buf->mHdr.nCMD_ID,
									buf->mHdr.nCount,
									buf->mHdr.nLength);*/
					rval == 0;
					fprintf(rfp,"%d", 0);
					break;
					}
				count--;
				if (count == 0) fprintf(rfp,"%d", 1);
				}
				count = 180;				
				break;		
		default :  
		                printf("[QA] : Invaild Input\n");
		}
}
