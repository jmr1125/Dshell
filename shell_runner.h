#include "incfile.cpp"
#include <sys/wait.h>
#include <unistd.h>
//#include<sys/prctl.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
pid_t start(const char *, int *);
int stop(pid_t);
