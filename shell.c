#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void commands_buffer(char* command) {
	char c;
	int i = 0;
	printf("verbash:~%s$ ",getcwd(NULL,50));
	while((c = getchar())!= 26 && c != '\n' && c !=EOF) {
		command[i++] = c;
	}	
	command[i] = '\0';
}

char** parser(char* string) 
{
	int argsBuff = 100;
	char** args = (char**)malloc(argsBuff*sizeof(char*));
	char* token;
	int i = 0;
	token = strtok(string," ");
	
	if(token != NULL) 
	{
		while(token != NULL) 
		{
			args[i++] = token;
			token = strtok(NULL," ");
			if( i >= argsBuff) 
			{
				argsBuff *= argsBuff;
				args = realloc(args,argsBuff);
			}
		}
	}
	else if ((token = strtok(string,"\0")) != NULL) 
	{
		args[i++] = token;
	}
	
	args[i] = NULL;
	
	return args;
	
}

char** shinput(char* command, char** args) 
{
	if(args)
		free(args);
	
	commands_buffer(command);
	args = parser(command);
	
	return args;
}

void chdim(char *path) 
{
	int l = strlen(path);
	int i;
		for(i = 0; i < l; i++) 
		{
			if(path[i] == '\\')
				path[i] = '/';
		}
	chdir(path);
}


int main() {
	char** args = NULL;
	char command[255];
	int status;
	
	do {
		args = shinput(command,args);
		pid_t pid = fork();
		
		if(pid == 0) 
		{
			
			execvp(args[0],args);
			_exit(0);
		}
		else {
			if(!strcmp(args[0],"cd") || !strcmp(args[0],"chdir"))
			{
				if(args[1])
					chdim(args[1]);
				else 
					chdim("/home");
			}
			printf("Waiting started\n");
			waitpid(-1,&status,WUNTRACED);
			if(!strcmp(args[0],"exit"))
				exit(0);
			printf("Waitig ended. STATUS IS %d\n",status);
			}
	} while(1);
	return 0;

}