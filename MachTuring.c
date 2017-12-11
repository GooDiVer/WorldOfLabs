#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct T {
	int c;
	int maxC;
	int* lenta;
} Cell;

int tFunction(Cell* cell,char* state) {

		if(!strcmp(state,"movl")) {
			if(cell->c > 0)
				cell->c--;
			else
				return 1;
		}
		if(!strcmp(state,"movr")) {
			if(cell->c >= cell->maxC) {
				cell->maxC++;
				cell->lenta = realloc(cell->lenta,cell->maxC);
				cell->lenta[cell->maxC] = 0;
			}
			cell->c++;
			
		}
		if(!strcmp(state,"inc")) {
			if(cell->lenta[cell->c] == 255) {
				cell->lenta[cell->c] = 0;
				return 1;
			}
			cell->lenta[cell->c] = (cell->lenta[cell->c] + 1)%256; 
		}
		if(!strcmp(state,"dec")) {
			if(cell->lenta[cell->c] == 0) {
				return 1;
			}
			else
				cell->lenta[cell->c] -= 1;
		}
		
		if(!strcmp(state,"print")) {
			printf("%d\n",cell->lenta[cell->c]);
		}
		if(!strcmp(state,"printc")) {
			putchar(cell->lenta[cell->c]);
			putchar('\n');
		}
		if(!strcmp(state,"get")) {
			scanf("%d",(&(cell->lenta[cell->c])));
			if(cell->lenta[cell->c] > 255) 
			{
				cell->lenta[cell->c] = 0;
				return 1;
			}
			
		}
		return 0;
		
}

void mainTFunc(Cell* cell, FILE* fp) 
{
	char state[100];
	int outError;
	int loop_start;

	
	while (fscanf(fp,"%s",state) != EOF) 
	{
		char spam[255];
		if(state[0] == '*') 
		{
			fgets(spam,255,fp);
		}
		outError = tFunction(cell,state);
		
		if(!strcmp(state,"begin"))
		{
			loop_start = ftell(fp);
			while(fscanf(fp,"%s",state) != EOF) 
			{
				if(!strcmp(state,"end") && cell->lenta[cell->c] == 0)
					break;
				else if(!strcmp(state,"end")) 
				{
					fseek(fp,loop_start,SEEK_SET);
					continue;
				}
				
				if(cell->lenta[cell->c] == 0) 
				{
					do 
					{
						fscanf(fp,"%s",state);
					} while(strcmp(state,"end"));
					break;
				}
				else
					outError = tFunction(cell,state);
			}
		}

		if(outError == 1)
			printf("Error occurred \n");
	}
}


int main(int argc, char** argv) {
	
	Cell out_Alphabet = {.c = 0, .maxC = 254, .lenta = (int*)malloc(255*sizeof(int))};
	int i;
	for(i = 0; i < 255; i++) {
		out_Alphabet.lenta[i] = 0;
	}
	
	FILE *in_Alphabet = fopen(argv[1], "r");
	mainTFunc(&out_Alphabet,in_Alphabet);
	return 0;
}