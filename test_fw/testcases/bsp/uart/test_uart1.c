
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
    	FILE *rfp = NULL;
	int uart1_filestream = -1;
	int stress = 0;
	unsigned int nIndex = 0;
	unsigned int nIndex1 = 0;
	unsigned char temp;
	unsigned int start = 0;
	int result = 0;
	unsigned int found = 0;
   	rfp = fopen("test_result.txt", "w");
	if(argc != 4)
	{
		printf("\nenter command like ./test_uart 115200 BUF_SIZE\n");
		fflush(rfp);
		fprintf(rfp,"%d", -1);
       		fclose(rfp);
		return 1;
	}
	stress = atoi(argv[3]);
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
	if(!stress)
	{
		result = -2;
		sleep(4);
		for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
		{
			tx_buffer[nIndex] = 'a' + rand()%26;
		}
		if (uart1_filestream != -1)
		{
			int count = 0;
			count = write(uart1_filestream, tx_buffer, BUF_SIZE);
			if (count < 0)
			{
				printf("UART TX error\n");
			}
		}
		for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
		{
			tx_buffer[nIndex] = toupper(tx_buffer[nIndex]);
		}
		printf("\nsent data:------->%s\n", tx_buffer);
		sleep(10);
		if (uart1_filestream != -1)
		{
			int rx_length;
			rx_length = read(uart1_filestream, (void*)rx_buffer, (BUF_SIZE + 16));
			printf("\nread data:------->%s\n", rx_buffer);
			start = 0;
			if((rx_length >= BUF_SIZE)&&(rx_length <= (BUF_SIZE + 16)))
			{
				for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
				{
					temp = tx_buffer[nIndex1];
					nIndex1 = start;
					for(; nIndex1 < rx_length; nIndex1++)
					{
						if(temp == rx_buffer[nIndex1])
						{
							found = 1;
							start = nIndex1;
							//printf("\nfound char %d\n", nIndex);
							break;
						}
						else
						{
							found = 0;
						}
					}
					if(!found)
					{
						printf("\nchar at %d not found\n",nIndex);
						result = 1;
						break;
					}
				}
				if(nIndex == BUF_SIZE)
				{
					result = 0;
				}
				else
				{
					result = 1;
				}
				if (rx_length <= 0)
				{
					printf("read error received no data\n");
					result = 1;
				}
				else
				{
					printf("\nRead bytes : %d\n", rx_length);
				}
			}
		}
		sleep(4);
	}
	else if(stress == 1)
	{
		int counter = 0;
		result = 0;
		while(counter != STRESS_COUNTER)
		{
			sleep(4);
			for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
			{
				tx_buffer[nIndex] = 'a' + rand() % 26;
			}
			if (uart1_filestream != -1)
			{
				int count = 0;
				count = write(uart1_filestream, tx_buffer, BUF_SIZE);
				if (count < 0)
				{
					printf("UART TX error\n");
				}
			}
			for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
			{
				tx_buffer[nIndex] = toupper(tx_buffer[nIndex]);
			}
			sleep(10);
			if (uart1_filestream != -1)
			{
				int rx_length = 0;
				rx_length = read(uart1_filestream, (void*)rx_buffer, (BUF_SIZE + 16));
				start = 0;
				if((rx_length >= BUF_SIZE)&&(rx_length <= (BUF_SIZE + 16)))
				{
				for(nIndex = 0; nIndex < BUF_SIZE; nIndex++)
				{
					temp = tx_buffer[nIndex1];
					nIndex1 = start;
					for(; nIndex1 < rx_length; nIndex1++)
					{
						if(temp == rx_buffer[nIndex1])
						{
							found = 1;
								start = nIndex1;
								//printf("\nfound char %d\n", nIndex);
								break;
						}
						else
						{
							found = 0;
						}
					}
					if(!found)
					{
						printf("\nchar at %d not found\n",nIndex);
						result |= 1;
						break;
					}
				}
				if(nIndex == BUF_SIZE)
				{
					result |= 0;
				}
				else
				{
					result |= 1;
				}
				if (rx_length <= 0)
				{
					printf("read error received no data\n");
					result |= 1;
				}
				else
				{
					printf("\nRead bytes : %d\n", rx_length);
				}
				}
			}
			sleep(4);
			counter++;
		}
	}
	close(uart1_filestream);
	printf("\nwriting to file result: %d\n", result);
	fflush(rfp);
	fprintf(rfp,"%d", result);
        fclose(rfp);
	return 0;
}
