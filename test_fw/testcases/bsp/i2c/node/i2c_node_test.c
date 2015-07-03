#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char text[1024];
int main(int argc, char *argv[])
{
	FILE *tfp = NULL;
	FILE *rfp = NULL;
	int result = 0;
	if(argc == 2)
	{
		system("ls /dev/ >temp.txt");
		rfp = fopen("test_result.txt", "w");
		tfp = fopen("temp.txt", "r");
		while(fscanf(tfp, "%s", text) != EOF)
		{
			if(strncmp(text, argv[1], strlen(argv[1])) == 0)
			{
				result = 0;
				break;
			}
			else
			{
				result = 1;
			}	
			printf("string read: %s\n", text);
		}
		fprintf(rfp, "%d", result);
		system("rm temp.txt");
		fclose(tfp);
		return 0;
	}
	else
	{
		printf("\nApplication usage is: \n./node_test drive_node\n");
		return 1;
	}
}
