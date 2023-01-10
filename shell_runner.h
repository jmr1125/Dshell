#include"incfile.cpp"
#include<unistd.h>
#include<sys/wait.h>
//#include<sys/prctl.h>
#include<signal.h>
#include<string.h>
#include<stdio.h>
pid_t start(const char*,char*const[],int *,int *);
int stop(pid_t);
