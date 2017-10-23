#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) 
{
	
	int a = atof(argv[1]);
	
	/*If we passed specific temperature (2 arg)*/
	if (argc > 2) 
	{
		if (*argv[2] == 'C' || *argv[2] == 'c') 
		{
			printf("%.2f F\n",1.8*a + 32);
			printf("%.2f K", a + 273.15);
		}
		else if (*argv[2] == 'K' || *argv[2] == 'k') 
		{
			printf("%.2f C \n", a - 273.15);
			printf("%.2f F \n", 1.8*(a - 273.15) + 32);
		}
		else if (*argv[2] == 'F' || *argv[2] == 'f') 
		{
			printf("%.2f C \n", (a - 32)/1.8);
			printf("%.2f K \n", (a - 32)/1.8 + 273.15);
		}
	}
	/*if we passed only figures (1 arg)*/
	else if (argc == 2) 
	{
		printf("%d C: \n",a);
		printf("%.2f F\n",1.8*a + 32);
		printf("%.2f K\n\n", a + 273.15);
		
		printf("%d F: \n",a);
		printf("%.2f C \n", (a - 32)/1.8);
		printf("%.2f K \n\n", (a - 32)/1.8 + 273.15);
		
		printf("%d K: \n",a);
		printf("%.2f C \n", a - 273.15);
		printf("%.2f F \n", 1.8*(a - 273.15) + 32);
		
	}
	
	return 0;
	
 }
