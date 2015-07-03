#include "network.h"
extern int sent_bytes;
extern int read_bytes;
extern int socket_test;
extern char buf_s[BUFFSIZE];
extern char buf_r[BUFFSIZE];
char command[512];
char master_test[128];
char sub_test[256];
char master_buf[896];
int accept_connection(int server_socket)
{
	int client_socket;                          /* Socket descriptor for client */
	struct sockaddr_in client_address;          /* Client address */
	unsigned int client_length;                 /* Length of client address data structure */

/* Set the size of the in-out parameter */
	client_length = sizeof(client_address);

/* Wait for a client to connect */
	if ((client_socket = accept(server_socket, (struct sockaddr *) &client_address, &client_length)) < 0) {
		printf("accept() failed");
	}

/* client_socket is connected to a client! */
	printf("Handling client %s\n", inet_ntoa(client_address.sin_addr));

	return client_socket;
}
int validate_wifi_size(char *sub)
{
	int size = 0;
	if((strcmp(sub, "wifi_1447_1024") == 0) || (strcmp(sub, "wifi_1447_10240") == 0) || (strcmp(sub, "wifi_1447_1024*1024_stress") == 0))
	{
		size = 1447;
	}
	else if((strcmp(sub, "wifi_1440_1024") == 0) || (strcmp(sub, "wifi_1440_10240") == 0))
	{
		size = 1440;
	}
	else if((strcmp(sub, "wifi_1200_1024") == 0) || (strcmp(sub, "wifi_1200_10240") == 0))
	{
		size = 1200;
	}
	else if((strcmp(sub, "wifi_1024_1024") == 0) || (strcmp(sub, "wifi_1024_10240") == 0))
	{
		size = 1024;
	}
	else if((strcmp(sub, "wifi_980_1024") == 0) || (strcmp(sub, "wifi_980_10240") == 0))
	{
		size = 980;
	}
	else if((strcmp(sub, "wifi_800_1024") == 0) || (strcmp(sub, "wifi_800_10240") == 0))
	{
		size = 800;
	}
	else if((strcmp(sub, "wifi_720_1024") == 0) || (strcmp(sub, "wifi_720_10240") == 0))
	{
		size = 720;
	}
	else if((strcmp(sub, "wifi_640_1024") == 0) || (strcmp(sub, "wifi_640_10240") == 0))
	{
		size = 640;
	}
	else if((strcmp(sub, "wifi_512_1024") == 0) || (strcmp(sub, "wifi_512_10240") == 0))
	{
		size = 512;
	}
	else if((strcmp(sub, "wifi_480_1024") == 0) || (strcmp(sub, "wifi_480_10240") == 0))
	{
		size = 480;
	}
	else if((strcmp(sub, "wifi_320_1024") == 0) || (strcmp(sub, "wifi_320_10240") == 0))
	{
		size = 320;
	}
	else if((strcmp(sub, "wifi_256_1024") == 0) || (strcmp(sub, "wifi_256_10240") == 0))
	{
		size = 256;
	}
	else if((strcmp(sub, "wifi_128_1024") == 0) || (strcmp(sub, "wifi_128_10240") == 0))
	{
		size = 128;
	}
	else if((strcmp(sub, "wifi_108_1024") == 0) || (strcmp(sub, "wifi_108_10240") == 0))
	{
		size = 108;
	}
	else if((strcmp(sub, "wifi_100_1024") == 0) || (strcmp(sub, "wifi_100_10240") == 0))
	{
		size = 100;
	}
	return size;
}
int validate_wifi_counter(char *sub)
{
	int counter = 0;
	if((strcmp(sub, "wifi_1447_1024") == 0) || (strcmp(sub, "wifi_1440_1024") == 0) || (strcmp(sub, "wifi_1200_1024") == 0) || (strcmp(sub, "wifi_1024_1024") == 0) || (strcmp(sub, "wifi_980_1024") == 0) || (strcmp(sub, "wifi_800_1024") == 0) || (strcmp(sub, "wifi_720_1024") == 0) || (strcmp(sub, "wifi_640_1024") == 0) || (strcmp(sub, "wifi_512_1024") == 0) || (strcmp(sub, "wifi_480_1024") == 0) || (strcmp(sub, "wifi_100_1024") == 0) || (strcmp(sub, "wifi_108_1024") == 0) || (strcmp(sub, "wifi_128_1024") == 0) || (strcmp(sub, "wifi_320_1024") == 0) || (strcmp(sub, "wifi_256_1024") == 0))
	{
		counter = 1024;
	}
	else if(strcmp(sub, "wifi_1447_1024*1024_stress") == 0)
	{
		counter = 1024 * 1024;
	}
	else if((strcmp(sub, "wifi_1200_10240") == 0) || (strcmp(sub, "wifi_1440_10240") == 0) || (strcmp(sub, "wifi_1024_10240") == 0) || (strcmp(sub, "wifi_980_10240") == 0) || (strcmp(sub, "wifi_800_10240") == 0) || (strcmp(sub, "wifi_720_10240") == 0) || (strcmp(sub, "wifi_640_10240") == 0) || (strcmp(sub, "wifi_512_10240") == 0) || (strcmp(sub, "wifi_480_10240") == 0) || (strcmp(sub, "wifi_320_10240") == 0) || (strcmp(sub, "wifi_256_10240") == 0) || (strcmp(sub, "wifi_128_10240") == 0) || (strcmp(sub, "wifi_108_10240") == 0) || (strcmp(sub, "wifi_100_10240") == 0))
	{
		counter = 10240;
	}
	return counter;
}
int send_receive(char *master, char *sub, char *command, int clnt_sock)
{
	int len = 0;
	len = strlen(master);
	do
	{
		memset(buf_r, '\0', BUFFSIZE);
		read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			read_bytes = strlen(buf_r);
		}
		if(strncmp(buf_r, master, len) == 0)
		{
			read_bytes = 0;	
			printf("\nReceived Master from Client: %s\n", buf_r);
			break;
		}
	}while(1);
	do
	{
		sent_bytes = send(clnt_sock, buf_r, BUFFSIZE, 0 );
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			sent_bytes = strlen(buf_r);
		}
		if(sent_bytes == len)
		{
			sent_bytes = 0;
			printf("\nSent back Master data to Client: %s\n", buf_r);
			break;
		}
	}while(1);
	len = strlen(sub);
	do
	{
		memset(buf_r, '\0', BUFFSIZE);
		read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			read_bytes = strlen(buf_r);
		}
		if(strncmp(sub, buf_r, len) == 0)
		{
			read_bytes = 0;	
			printf("\nReceived Sub from Client: %s\n", buf_r);
			break;
		}
	}while(1);
	do
	{
		sent_bytes = send(clnt_sock, buf_r, BUFFSIZE, 0 );
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			sent_bytes = strlen(buf_r);
		}
		if(sent_bytes == len)
		{
			sent_bytes = 0;
			printf("\nSent back received Sub to Client: %s\n", buf_r);
			break;
		}
	}while(1);
	if(strcmp(master,"WIFI_TEST") && strcmp(master,"SKY_TEST"))
	{
		len = strlen(command);
		do
		{
			memset(buf_r, '\0', BUFFSIZE);
			read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				read_bytes = strlen(buf_r);
			}
			if(strncmp(buf_r, command, len) == 0)
			{
				read_bytes = 0;	
				printf("\nReceived command from Client: %s\n", buf_r);
				break;
			}
		}while(1);
		do
		{
			sent_bytes = send(clnt_sock, buf_r, BUFFSIZE, 0 );
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				sent_bytes = strlen(buf_r);
			}
			if(sent_bytes == len)
			{
				sent_bytes = 0;
				printf("\nSent back received command to Client: %s\n", buf_r);
				break;
			}
		}while(1);
		system("rm test_result.txt");
		if(strcmp(master,"LTP_TEST"))
		{
			system(command);
			{
				FILE *rfp = fopen("test_result.txt", "r");
				if(rfp)
				{
					int result = 200;
					fscanf(rfp, "%d", &result);
					fclose(rfp);
					memset(buf_s, '\0', BUFFSIZE);
					if(result == 1)
					{
						strncpy(buf_s, "FAIL", 4);
					}
					else if(result == 0)
					{
						strncpy(buf_s, "PASS", 4);
					}
					else if(result == -1)
					{
						strncpy(buf_s, "NOT_TESTED", 10);
					}
					len = strlen(buf_s);
					do
					{
						sent_bytes = send(clnt_sock, buf_s, BUFFSIZE, 0 );
						if(buf_s[BUFFSIZE - 1] == '\0')
						{
							sent_bytes = strlen(buf_s);
						}
						if(sent_bytes == len)
						{
							sent_bytes = 0;
							printf("\nSent Result to Client: %s\n", buf_s);
							break;
						}
					}while(1);
					do
					{
						memset(buf_r, '\0', BUFFSIZE);
						read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
						if(buf_r[BUFFSIZE - 1] == '\0')
						{
							read_bytes = strlen(buf_r);
						}
						if(strncmp(buf_r, buf_s, len) == 0)
						{
							read_bytes = 0;	
							printf("\nReceived back Result from Client: %s\n", buf_r);
							break;
						}
					}while(1);
				}	
				else
				{
					printf("\nFailed to open the file\n");
					exit(1);
				}
			}
		}
		else
		{
			system(command);
			printf("\nNeed analysis code for LTP\n");
		}
	}
	else if(strcmp(master,"SKY_TEST") == 0)
	{
		len = strlen(command);
		do
		{
			memset(buf_r, '\0', BUFFSIZE);
			read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				read_bytes = strlen(buf_r);
			}
			if(strncmp(buf_r, command, len) == 0)
			{
				read_bytes = 0;	
				printf("\nReceived command from Client: %s\n", buf_r);
				break;
			}
		}while(1);
		do
		{
			sent_bytes = send(clnt_sock, buf_r, BUFFSIZE, 0 );
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				sent_bytes = strlen(buf_r);
			}
			if(sent_bytes == len)
			{
				sent_bytes = 0;
				printf("\nSent back received command to Client: %s\n", buf_r);
				break;
			}
		}while(1);
		system("rm test_result.txt");
		sleep(2);
		printf("\nBefore triggering the command\n");
		sleep(3);
		system(command);
		printf("\nAfter triggering the command\n");
		{
			FILE *rfp = fopen("test_result.txt", "r");
			if(rfp)
			{
				int result = 200;
				fscanf(rfp, "%d", &result);
				fclose(rfp);
				memset(buf_s, '\0', BUFFSIZE);
				if(result == 1)
				{
					strncpy(buf_s, "FAIL", 4);
				}
				else if(result == 0)
				{
					strncpy(buf_s, "PASS", 4);
				}
				else if(result == -1)
				{
					strncpy(buf_s, "NOT_TESTED", 10);
				}
				len = strlen(buf_s);
				do
				{
					sent_bytes = send(clnt_sock, buf_s, BUFFSIZE, 0 );
					if(buf_s[BUFFSIZE - 1] == '\0')
					{
						sent_bytes = strlen(buf_s);
					}
					if(sent_bytes == len)
					{
						sent_bytes = 0;
						printf("\nSent Result to Client: %s\n", buf_s);
						break;
					}
				}while(1);
				do
				{
					memset(buf_r, '\0', BUFFSIZE);
					read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
					if(buf_r[BUFFSIZE - 1] == '\0')
					{
						read_bytes = strlen(buf_r);
					}
					if(strncmp(buf_r, buf_s, len) == 0)
					{
						read_bytes = 0;	
						printf("\nReceived back Result from Client: %s\n", buf_r);
						break;
					}
				}while(1);
			}	
			else
			{
				printf("\nFailed to open the file\n");
				exit(1);
			}
		}
	}
	else
	{
		int ref_counter = 0;
		int counter = 0;
		int size = 0;
		ref_counter = validate_wifi_counter(sub);
		size = validate_wifi_size(sub);
		if(!size)
		{
			printf("\nSetting valid size of 1024 for invalid size input to wifi test\n");
			size = 1024;
		}
		do
		{
			memset(buf_r, '\0', BUFFSIZE);
			read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
			if(buf_r[BUFFSIZE - 1] == '\0')
			{
				read_bytes = strlen(buf_r);
			}
			if(read_bytes == size)
			{	
				printf("\nReceived Wifi data for %d\n", counter);
				do
				{
					sent_bytes = send(clnt_sock, buf_r, read_bytes, 0 );
					if(sent_bytes == read_bytes)
					{
						sent_bytes = 0;
						read_bytes = 0;
						counter++;
						printf("\nSent back Received data to Client: %d\n", counter);
						if(counter == ref_counter)
						{
							printf("\nFinished execution with specified buf size: %d\n", size);
							goto QUIT;
						}
						break;
					}
				}while(1);			
			}
		}while(1); 
		QUIT:
		printf("\nThe end of WIFI\n");
	}
	return 0;
}
int handle_client (int clnt_sock)
{           /* Buffer for incomming data */

	int nIndex = 0;
	int nIndex1 = 0;
	int str_count = 0;
	FILE *sfp = NULL;
	long int read_length = 0;
	int len = 12;
	do
	{
		memset(buf_r, '\0', BUFFSIZE);
		read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			read_bytes = strlen(buf_r);
		}
		if((strncmp(buf_r, "test_config1", len) == 0) || (strncmp(buf_r, "test_config2", len) == 0) || (strncmp(buf_r, "test_config3", len) == 0))
		{
			read_bytes = 0;	
			printf("\nReceived Master from Client: %s\n", buf_r);
			break;
		}
	}while(1);
	do
	{
		sent_bytes = send(clnt_sock, buf_r, BUFFSIZE, 0 );
		if(buf_r[BUFFSIZE - 1] == '\0')
		{
			sent_bytes = strlen(buf_r);
		}
		if(sent_bytes == len)
		{
			sent_bytes = 0;
			printf("\nSent back Master data to Client: %s\n", buf_r);
			break;
		}
	}while(1);
	printf("\nServer is going to work on config: %s\n", buf_r);
	sfp = fopen(buf_r, "r");
	do
	{
		if(fgets(master_buf, 896, sfp) != NULL)
        	{
			printf("Read string: %s\n", master_buf);
		    read_length = strlen(master_buf);
            printf("length of read string: %ld\n", read_length);
            memset(master_test, '\0', 128);
			memset(sub_test, '\0', 256);
            str_count = 0;
            for(nIndex = 0; nIndex < read_length; nIndex++)
            {
            	if(master_buf[nIndex] != ',')
                {
                	if(str_count == 0)
                    {
                    	master_test[nIndex1] = master_buf[nIndex];
                        nIndex1++;
                    }
                    else if(str_count == 1)
                    {
		            	sub_test[nIndex1] = master_buf[nIndex];
                        nIndex1++;
                    }
                    else if(str_count == 2)
                    {
						command[nIndex1] = master_buf[nIndex];
                        nIndex1++;
                    }
				}
                else
                { 
					if(str_count == 0)
                    {
						master_test[nIndex1] = '\0';
                        printf("Master Test: %s\n", master_test);
					    nIndex1 = 0;
                        str_count++;
                    }
                    else if(str_count == 1)
                    {
                    	sub_test[nIndex1] = '\0';
                        printf("Sub Test: %s\n", sub_test);
                        nIndex1 = 0;
                       str_count++;
                    }
                    else if(str_count == 2)
                    {
                    	command[nIndex1] = '\0';
                        printf("Command: %s\n", command);
                        nIndex1 = 0;
                        str_count++;
                        send_receive(master_test, sub_test, command, clnt_sock);
					}  	
				}
			}
		}
		else
		{
			printf("\nFinished parsing config\n");
			while(!read_bytes)
			{
				memset(buf_r, '\0', BUFFSIZE);
				read_bytes = read (clnt_sock, buf_r, BUFFSIZE);
				if(buf_r[BUFFSIZE - 1] == '\0')
				{
					read_bytes = strlen(buf_r);
				}
			}
			if((read_bytes == 4) && (!(strncmp(buf_r, "quit", 4))))
			{
				printf("\nread QUIT message from client to server [%s]\n", buf_r);
				read_bytes = 0;
				do
				{
					sent_bytes = send(clnt_sock, buf_r, BUFFSIZE, 0 );
					if(buf_r[BUFFSIZE - 1] == '\0')
					{
						sent_bytes = strlen(buf_r);
					}
					if(sent_bytes == 4)
					{
						printf("\nSent back Quit to client: %s\n", buf_r);
						sent_bytes = 0;
						break;
					}
				}while(1);
			}
			break;
			fclose(sfp);
		}
	}while(1);
	return 0;
}
int main(int argc, char *argv[])
{
    int clnt_sock = 0;
	if(argc < 2)
	{
		printf("\n./server 3000\n");
		return 1;
	}
	int ADRESS_PORT = atoi(argv[1]);
	socket_test = make_socket(ADRESS_PORT, SERVER_SOCKET, "none");
	if(socket_test <= 0)
	{
		printf("\nFailed to created socket\n");
		return 1; 
	}
	else
	{
		printf("\nCreated socket successfully\n");
	}
    clnt_sock = accept_connection(socket_test);
	if(clnt_sock <= 0)
	{
		printf("\nFailed to created socket\n");
		return 1; 
	}
	else
	{
		printf("\nCreated socket successfully\n");
	}
   	handle_client(clnt_sock);
	close_socket(socket_test);
    return 0;
}
