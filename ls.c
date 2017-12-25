#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc,char** argv) {
	
	struct dirent* file;
	char* papka;
	if(argc == 1)
		papka = ".";
	else
		papka = argv[1];
	
	DIR* ptr = opendir(papka);
		
		if(ptr != NULL) 
		{
			while((file = readdir(ptr)) != NULL)
				printf("%s\n",file->d_name);
		}
		else 
			printf("Dir error occured.");
	
	closedir(ptr);
	return 0;
}