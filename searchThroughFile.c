#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct twoLevel {
	char *s;
	int l;
	int sy;
	struct twoLevel *nextWord;
} wordTree;

typedef struct oneLevel {
	char letter;
	struct oneLevel *nextLetter;
	struct twoLevel *slovo;
} letterTree;

/*--------------------CREATORS OF TREES--------------------*/
letterTree* getLetterTree(char c) {
	letterTree* tmp = (letterTree*)malloc(sizeof(letterTree));
	tmp->slovo = NULL;
	tmp->nextLetter = NULL;
	tmp->letter = c;
	return tmp;
	
}

wordTree* getWordTree(char* c) {
	wordTree* tmp = (wordTree*)malloc(sizeof(wordTree));
	tmp->nextWord = NULL;
	tmp->s = c;
	return tmp;
}

/*--------------------FITCHA--------------------*/
void putWordBetween(wordTree **slovo, char *word, int line, int sym) {
	wordTree* tmp = (wordTree*)malloc(sizeof(wordTree));
	tmp->s = word;
	tmp->nextWord = (*slovo)->nextWord;
	tmp->l = line;
	tmp->sy = sym;
	(*slovo)->nextWord = tmp;
}

/*--------------------ADDERS OF WORDS--------------------*/
void insertWord(wordTree **slovo, char* word, int line, int sym) {
	short protectFromRecursion = 0;
	if (*slovo == NULL) {
		*slovo = getWordTree(word);
		(*slovo)->l = line;
		(*slovo)->sy = sym;
		protectFromRecursion = 1;
		
	}
	if((*slovo)->s != word) {
		insertWord(&((*slovo)->nextWord), word, line, sym);
	}
	if((*slovo)->s == word) {
		if((*slovo)->nextWord) {
			putWordBetween(slovo,word, line, sym);
		}
		else if (protectFromRecursion == 0)
			insertWord(&((*slovo)->nextWord),word, line, sym);
	}
}

void insertTree(letterTree** head, char* word, int line, int sym){
	/*полученный узел пуст?*/
	if(*head == NULL) {
		*head = getLetterTree(word[0]);
	}
	
	/*узел не пуст, но полученное слово не совпадает с символом узла => перейти в след узел*/
	if ((*head)->letter != word[0]) {
		insertTree(&((*head)->nextLetter), word, line, sym);
	}
	if((*head)->letter == word[0]){
		insertWord(&((*head)->slovo), word, line, sym);
	}
}

/*--------------------SERACHERS FOR WORD--------------------*/
void searchWord(wordTree* slovo, char* word) {
	
	if (!strcmp(slovo->s, word)) {
		printf("%d : %d %s \n",slovo->l,slovo->sy,slovo->s);
		if(slovo->nextWord)
			searchWord(slovo->nextWord, word);
	}
	else if(slovo->nextWord) {
		searchWord(slovo->nextWord, word);
	}
	else
		printf("Word wasn't found");
}

void searchIt(letterTree* head, char* word) {
	if(head->letter == word[0]) {
		searchWord(head->slovo, word);
		
	} 
	else if (head->nextLetter) {
		searchIt(head->nextLetter,word);
	}
	else
		printf("Word wasn't found");
}


/*---------------------CONCATINATION------------------*/
char* concat(char *s1, char *s2) {

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);

        char *result = malloc(len1 + len2 + 1);

        if (!result) {
            fprintf(stderr, "malloc() failed: insufficient memory!\n");
            return NULL;
        }

        memcpy(result, s1, len1);
        memcpy(result + len1, s2, len2 + 1);

        return result;
    }
	
	/*МЕСТО ДЛЯ mainInsertFunction(FILE* fp,*head)*/

int main(int argc, char** argv) {
	
	
	
	int sym = 0;
	int flag = 0;
	int posAll = 0;
	int line = 1;
	char *string = "";
	unsigned short inWord = 0;
	int c;
	FILE* fp = fopen(argv[1],"r");
	letterTree* head = NULL;
	
	while((c = fgetc(fp)) != EOF ) {
		if(c != ' ' && c != '\n') {
			if (inWord == 0) {
				sym = ftell(fp) - posAll; 
			}
			char s1[2] = ""; 
			s1[0] = c;
			s1[1] = '\0';
            string = concat(string,s1);
			inWord = 1;
		}
		else if (c == '\n') {
			/*если слово до этого не было пробела*/
			if(inWord == 1) {
				insertTree(&head,string,line,sym);
			}
			line++;
			posAll = ftell(fp);
			string = "";
			inWord = 0;
		}
		else if(c == ' ') {
			/*если было слово, вводим, иначе был пробел, который нигде не нужен*/
			if (inWord == 1) {
				insertTree(&head,string,line,sym);
				flag = 1;
			}
			inWord = 0;
			string = "";
		}
	}
	
	if(strcmp("",string))
		insertTree(&head,string,line,sym);
	
	/*  C:/file/test.txt */
	unsigned long length = strlen(argv[2]);
	char posim[length];

	
	if(!flag) {
		freopen(argv[1],"r",fp);
		int symCounter = 1;
		int counter = 0;
		int gotWord = 0;
		
		while(counter < length && (c = fgetc(fp)) != EOF) {
				posim[counter] = c;
				counter++;
			}
		posim[counter] = '\0';
		if(!strcmp(argv[2],posim)) {
			gotWord = 1;
			printf("%d %s \n",symCounter,posim);
		}
		while((c = fgetc(fp)) != EOF) {
			memcpy(posim,posim + 1, length - 1);
			posim[length - 1] = c;
			posim[length] = '\0';
			symCounter++;
			
			if(!strcmp(argv[2],posim)) {
			gotWord = 1;
			printf("%d %s \n",symCounter,posim);
			}
		}
		if (gotWord == 0)
			printf("Word wasn't found!");
		
	}
	else
		searchIt(head,argv[2]);
	return 1;
}
