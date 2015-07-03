
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>		//Used for UART
#define STRESS_COUNTER 10240
unsigned int  BUF_SIZE = 0;
unsigned char tx_buffer[1024];
unsigned char rx_buffer[1024];
#include <time.h>
clock_t startm, stopm;
int main(int argc , char** argv)
{
    	FILE *wfp = NULL;
	FILE *rfp = NULL;
	int uart1_filestream = -1;
	unsigned int nIndex = 0;
	unsigned int nIndex1 = 0;
	unsigned char temp;
	unsigned int start = 0;
	unsigned int found = 0;
   	wfp = fopen("write_speed.txt", "w");
	rfp = fopen("read_speed.txt", "w");
	if(argc != 3)
	{
		printf("\nenter command like ./test_uart 115200 BUF_SIZE\n");
		fflush(wfp);
		fflush(rfp);
		fprintf(wfp,"%d", -1);
		fprintf(rfp,"%d", -1);
		fclose(wfp);
       		fclose(rfp);
		return 1;
	}
	BUF_SIZE = atoi(argv[2]);
	uart1_filestream = open("/dev/ttyS1", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode
	if (uart1_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}
	struct termios options;	
	tcgetattr(uart1_filestream, &options);
	if(atoi(argv[1]) == 300)
	{
		options.c_cflag = B300 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 600)
	{
		options.c_cflag = B600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 1200)
	{
		options.c_cflag = B1200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 2400)
	{
		options.c_cflag = B2400 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 4800)
	{
		options.c_cflag = B4800 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 9600)
	{
		options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 19200)
	{
		options.c_cflag = B19200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 38400)
	{
		options.c_cflag = B38400 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 57600)
	{
		options.c_cflag = B57600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 115200)
	{
		options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	else if(atoi(argv[1]) == 230400)
	{
		options.c_cflag = B230400 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	}
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart1_filestream, TCIFLUSH);
	tcsetattr(uart1_filestream, TCSANOW, &options);
	{
		int counter = 0;
		int nbytes_send = 0;
		int nbytes_rcv = 0;
		clock_t cstart = 0;
		clock_t cend = 0;
		clock_t total_send = 0;
		clock_t total_rcv = 0;
		sleep(4);
		for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
		{
			tx_buffer[nIndex] = 'a' + rand() % 26;
		}
		if (uart1_filestream != -1)
		{
			int runcount = 0;
			int iterate = 1024;
		
			while(runcount < iterate)
			{
				int count = 0;
				cstart = clock();
				count = write(uart1_filestream, tx_buffer, BUF_SIZE);
				cend = clock();
				total_send += (double)(end_t - start_t) / CLOCKS_PER_SEC;
				nbytes_send += count;
				if (count < 0)
				{
					printf("UART TX error\n");
				}
				else
				{
					int rx_length = 0;
					sleep(10);
					cstart = clock();
					rx_length = read(uart1_filestream, (void*)rx_buffer, (BUF_SIZE + 16));
					cend = clock();
					total_rcv += (double)(end_t - start_t) / CLOCKS_PER_SEC;
					nbytes_rcv += rx_length;
				}
				runcount++;
			}
			{
				double write_speed = 0;
				double read_speed = 0;
				write_speed = (double)(nbytes_send/total_send);
				read_speed = (double)(nbytes_rcv/total_rcv);
				printf("\nSending speed: %f\n", write_speed);
				printf("\nReceiving speed: %f\n", read_speed);
			}
		}
	}
	close(uart1_filestream);
	fflush(rfp);
        fclose(rfp);
	fflush(wfp);
        fclose(wfp);
	return 0;
}

