#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char text[1024];
int main(int argc, char *argv[])
{
	FILE *tfp = NULL;
	int result = 0;
	system("ls /sys/class/net/ >temp.txt");
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
	printf("\nResult: %d\n", result);
	system("rm temp.txt");
	fclose(tfp);
}
