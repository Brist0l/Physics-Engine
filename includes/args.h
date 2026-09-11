#ifndef ARGS_H
#define ARGS_H 

extern struct t_thing{
	char sliced_args[1024][1024];
}thing;

struct t_thing sendargs(int argc,char *argv[]);
int pyboolconverter(char *boolvals);

#endif
