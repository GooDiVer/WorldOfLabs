#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define INIT_SIZE 10
#define NUMBER '0'


/*define out stack*/
typedef struct Stack_tag 
{
	int size;
	int top;
	int* stArr;
} Stack;

Stack* createStack(void); 
void deleteStack(Stack**);
void resize(Stack*);
void push(Stack*, int);
int pop(Stack*);
int peek(Stack*);
/*method below get user input and put it in out stack*/
int userInput(char*);

int main() 
{
	Stack* p = createStack();
	
	/*in this array we introduce the numbers*/
	char* s;
	s = malloc(100*sizeof(char));
	/*in case of NOT NUMBERS we return "c" which may contain + or - or * or / */
	char c;
	/*by the 'naoborot' we can trick subtraction or division*/
	int naoborot;

	while((c = userInput(s)) != EOF) 
	{
		switch (c) 
		{
			/*is 'c' a number? translate char array to number*/
			case NUMBER:
				push(p,atoi(s));
				break;
			/*NOT NUMBER retrurned? if 'c' is (* or / or + or -) - make some stack operations */
			case '+':
				push(p,pop(p) + pop(p));
				break;
			case '-':
				naoborot = pop(p);
				push(p,pop(p) - naoborot);
			case '*':
				push(p,pop(p)*pop(p));
				break;
			case '/':
				naoborot = pop(p);
				push(p,pop(p)/naoborot);
				break;
			case '\n':
				printf("%d", peek(p));
		}
	}
	
	/*free memory*/
	free(s);
	deleteStack(&p);
}

Stack* createStack() 
{
	Stack* out = NULL;
	out = malloc(sizeof(Stack));
	
	out->stArr = malloc(INIT_SIZE*sizeof(int));
	out->size = INIT_SIZE;
	out->top = 0;
	return out;
}

void deleteStack(Stack** st) 
{
	free((*st)->stArr);
	free(*st);
	*st = NULL;
}

void resize(Stack* st) 
{
	st->size = st->size + 1;
	st->stArr = realloc(st->stArr,st->size*sizeof(int));
	if (st->stArr == NULL) 
	{
		exit(-1);
	}
}

void push(Stack* st, int a) 
{
	if(st->top >= st->size) 
	{ /*Если просто =, то некорректно работает*/
		resize(st);
	}
	st->stArr[st->top] = a;
	st->top++;
}

int pop(Stack* st) 
{
	if(st->top == 0)
		exit(-1);
	
	st->top--;
	return st->stArr[st->top];
}

int peek(Stack* st) 
{
	if (st->top == 0)
		exit(-2);
	return(st->stArr[st->top - 1]);
}

int userInput(char s[]) 
{
	char c;
	int i = 0;
	do 
	{
		s[i] = c = getchar();
	} while(c == ' ' || c == '\t');
	
	if(isdigit(c)) 
	{
		do
		{		
			s[++i] = c = getchar();
		} while(isdigit(c));
	}
	else
		return c;
	
	s[i] = '\0';
	
	return NUMBER;
}
