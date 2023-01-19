#include"shell_runner.h"//https://www.thinbug.com/q/6171552
pid_t start(const char* cmd,char*const argv[],int *inpipefd,int *outpipefd){
  pid_t pid = 0;
  int status;

  pipe(inpipefd);
  pipe(outpipefd);
  pid = fork();
  if (pid == 0)
  {
    if(dup2(outpipefd[0], STDIN_FILENO)==-1){fprintf(stderr,"error dup stdin  -> pipe \n");};
    if(dup2(inpipefd[1], STDOUT_FILENO)==-1){fprintf(stderr,"error dup stdout -> pipe \n");};
    if(dup2(inpipefd[1], STDERR_FILENO)==-1){fprintf(stderr,"error dup stderr -> pipe \n");};
    close(inpipefd[0]);
    close(outpipefd[1]);
    execvp(cmd,argv);
    exit(1);
  }
  close(outpipefd[0]);
  close(inpipefd[1]);


  return pid;
}
int stop(pid_t pid){
  int status;
  kill(pid, SIGKILL);
  waitpid(pid, &status, 0);
  return status;
}
