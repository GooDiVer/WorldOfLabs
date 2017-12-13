#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc,char** argv) {
	DIR* ptr = opendir(argv[1]);
	struct dirent* file;
	
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