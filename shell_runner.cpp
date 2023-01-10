#include"shell_runner.h"//https://www.thinbug.com/q/6171552
#define block_size (1024)
pid_t start(const char* cmd,char*const argv[],int *inpipefd,int *outpipefd){
  //char *s[block_size];
  // FILE*fp=popen(cmd,"r");
  // FILE*fp1=popen(cmd,"w");
  pid_t pid = 0;
  int status;

  pipe(inpipefd);
  pipe(outpipefd);
  pid = fork();
  if (pid == 0)
  {
    dup2(outpipefd[0], STDIN_FILENO);
    dup2(inpipefd[1], STDOUT_FILENO);
    dup2(inpipefd[1], STDERR_FILENO);
    //prctl(PR_SET_PDEATHSIG, SIGTERM);
    //execl(cmd,cmd,(char*)NULL);
    execvp(cmd,argv);
    exit(1);
  }
  close(outpipefd[0]);
  close(inpipefd[1]);


  return pid;
}
/*
    while(1)
  {

    write(outpipefd[1], msg, strlen(msg));
    read(inpipefd[0], buf, 256);

    printf("Received answer: %s\n", buf);
  }
*/
int stop(pid_t pid){
  int status;
  kill(pid, SIGKILL);
  waitpid(pid, &status, 0);
  return status;
}
