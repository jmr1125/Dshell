#include"shell_runner.h"
int main(){
  int input[2],output[2];
  char **args=new char*[3];
  args[0]=new char[4]{"tee"};
  args[1]=NULL;
  pid_t pid=start("tee",args,input,output);
  char msg[1024]="hi";
  write(output[1],msg,2);
  char buf[1024];
  read(input[0],buf,10);
  puts(buf);
  stop(pid);
}
