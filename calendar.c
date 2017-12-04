#include <stdio.h>
int isVisokos(int cYear) {
	if( (cYear % 4 == 0) && (cYear % 100 !=0) || cYear % 400 == 0)
		return 1;
	else
		return 0;
}
int main() {
	int cYear = 1;
	int cMonth = 1;
	int cDay = 1;
	int counter = 6;
	
	int inD = 14, inM = 11, inY = 2017;
	
	printf("Please, input data. Format: \"DD MM YYYY\" ");
	scanf("%d %d %d", &inD, &inM, &inY);
	
	while(cYear < inY) {
		if(isVisokos(cYear)) {
			counter += 366;
		}
		else 
			counter += 365;
		cYear++;
	}
	while (cMonth < inM) {
		switch(cMonth) {
			case 1:
				counter += 31;
				break;
			case 2:
				if(isVisokos(cYear)) {
					counter += 29;
				}
				else
					counter += 28;
				break;
			case 3:
				counter +=31;
				break;
			case 4:
				counter +=30;
				break;
			case 5:
				counter +=31;
				break;
			case 6:
				counter +=30;
				break;
			case 7:
				counter +=31;
				break;
			case 8:
				counter +=31;
				break;
			case 9:
				counter +=30;
				break;
			case 10:
				counter +=31;
				break;
			case 11:
				counter +=30;
				break;	
		}
		cMonth++;
	}
	
	counter += inD;
	
	if (counter > 7) {
		counter = counter % 7 + 1;
	}

	if (counter == 1) {
		printf("Monday");
	} 
	else if (counter == 2) {
		printf("Tuesday");
	} 
	else if (counter == 3) {
		printf("Wednesday");
	} 
	else if (counter == 4) {
		printf("Thursday");
	} 
	else if (counter == 5) {
		printf("Friday");
	} 
	else if (counter == 6) {
		printf("Saturday");
	} 
	else if (counter == 7) {
		printf("Sunday");
		}
	
	
}