#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<mutex>
#include<thread>
#include<atomic>
using std::unique_lock;
using std::mutex;

int main(int argc, char** argv)
{
  int input[2],output[2];
  pipe(input);
  pipe(output);
  pid_t pid=fork();
  if(pid==0){
    if(dup2(input [0],0 )==-1){printf("error ");exit(1);};
    if(dup2(output[1],STDOUT_FILENO)==-1){printf("error1");exit(1);};
    if(dup2(output[1],STDERR_FILENO)==-1){printf("error2");exit(1);};
    close(input[1]);
    close(output[0]);
    execl("/usr/bin/bash","bash","--login",(char*)NULL);
  }
  /*
    stdin <-input[1]
    stdout ->output[0]
  */
  close(input[0]);
  close(output[1]);
  std::mutex mtx;
  std::atomic<bool> exit;
  exit=false;
  char buf[256]{0};
  std::thread thr([&](){
    while(!exit){
      memset(buf,0,sizeof buf);
      int r_num=read(output[0],buf,256);
      if(r_num){
        unique_lock<mutex> lck(mtx);
	printf("buf>> %s",buf);
        lck.unlock();
      }
    }
  });
  char msg[256];
  int len=0;
  while(true){
    memset(msg,0,sizeof msg);
    len=0;
    sleep(1);
    {
      unique_lock<mutex> lck(mtx);
      printf("msg>>");
    }
    {
      char c;
      do{
	c=getchar();
	msg[len++]=c;
      }while(c!='\n'&&c!='\r');
    }
    printf("%s\n", msg);
    //msg[len-1]=0;
    if(kill(pid,0)==-1){
      printf("pid(%d) id died ..\n",pid);
      break;
    }
    write(input[1],msg,strlen(msg));
    if(!strncmp(msg, "exit", 4)){
      break;
    }
  }
  printf("EXIT ...\n");
  exit=true;
  thr.join();
  kill(pid,SIGKILL);//stop
  close(input[1]);
  close(output[0]);
  int status=0;
  waitpid(pid,&status,0);
  printf("return: %d\n",status);
}
