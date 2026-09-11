#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void gethelp(char *ok,char *path){
	FILE *fp = popen(ok,"r");

  	if (fp == NULL){
    		fprintf(stderr,"Failed to run command\n" );
    		exit(1);
  	}

	printf("helping");
	while (fgets(path,1024, fp) != NULL)
		printf("%s\n",path);
	exit(0);
}

struct t_thing{
	char sliced_args[1024][1024];
};

struct t_thing sendargs(int argc,char *args[]){
	struct t_thing thing;

	FILE *fp;
  	char *path = (char *)malloc(1024); // need to make it dynamic later using "getmem"

	char ok[50] = "python parser.py";

	int word = 0;
	size_t j;


	for(int i = 1; i < argc;i++){
		strcat(ok," ");
		strcat(ok,args[i]);
		if(strcmp(args[i],"-h") == 0|| strcmp(args[i],"--help") == 0)
			gethelp(ok,path);
	}

  	fp = popen(ok,"r");

  	if (fp == NULL){
    		printf("Failed to run command\n" );
    		exit(1);
  	}

//	printf("%s\n",ok);

	while (fgets(path,1024, fp) != NULL){
		for(size_t i = 0;i <= strlen(path);i++){
			if(word == 0)
				j = i;

//			printf("Word num->%d\tAscii->%d\tLetter->%c\ti->%ld\tj->%ld\n",word,*(path+i),*(path+i),i,j);

			if(*(path+i) == ' '){
				//*(*((sliced_args) + word) + j) = '\0';
				thing.sliced_args[word][j] = '\0';
				word++;
				j = 0;
				continue;
			}

			thing.sliced_args[word][j++] = *(path+i);
			if(*(path+i) == 10) // if char is line feed
				break;
		}
	}

  	pclose(fp);

  	return thing;
}

int pyboolconverter(char *boolvals){
	if(strcmp("True",boolvals) == 0)
		return 1;
	else
		return 0; // i.e false
}
