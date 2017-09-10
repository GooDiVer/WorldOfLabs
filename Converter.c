#include <stdio.h>

 main() {
	int a;
	char c;
	char t;
	
	scanf("%d", &a);
	c = getchar();
	while (c != '\n') {
		t = c;
		c = getchar();
	}
		
	if (t == 'C') {
		printf("%.2f F\n",1.8*a + 32);
		printf("%.2f K", a + 273.15);
	}
	else if (t == 'K') {
		printf("%.2f C \n", a - 273.15);
		printf("%.2f F \n", 1.8*(a - 273.15) + 32);
	}
	else if (t == 'F') {
		printf("%.2f C \n", (a - 32)/1.8);
		printf("%.2f K \n", (a - 32)/1.8 + 273.15);
	}
	
	else {
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
	
	
	
 }