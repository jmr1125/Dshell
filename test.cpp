// #include"incfile.cpp"
// #include"shell_runner.h"
// #include<iostream>
// using std::cin;
// using std::cout;
// using std::endl;
// regex command(R"(^((?:".+")|(?:[^"][^ ]+[^"])|(?:[\w^ ]+))(.*)$)");
// int main(){
//   while(true){
//     string cmd;
//     cout<<"command: ";
//     cin>>cmd;
//     if(cmd=="exit"){
//       break;
//     }
//     cmatch cm;
//     if(regex_match(cmd.c_str(),cm,command)){
//       char *args[100];
//       int argid=1;
//       memset(args,0,sizeof args);
//       args[0]=new char [string(cm[1]).size()+1];
//       memcpy(args[0],string(cm[1]).c_str(),string(cm[1]).size());
//       args[0][string(cm[1]).size()]=0;
//       int pos=0;
//       char str[100]{0};
//       memcpy(str,string(cm[2]).c_str(),string(cm[2]).size());
//       cout<<">>"<<string(cm[1]).c_str()<<endl;
//       cout<<">>"<<string(cm[2]).c_str()<<endl;
//       str[string(cm[2]).size()]=' ';
//       int len=strlen(str);
//       for(int i=0;i<len;++i){
// 	if(str[i]==' '){
// 	  int lenn=i-pos+1;
// 	  args[argid]=new char[lenn+1];
// 	  memset(args[argid],0,lenn+1);//+1 to end the str with '\0'
// 	  for(int j=pos;j<=i;++j){
// 	    args[argid][j-pos]=str[j];
// 	  }
// 	  pos=i+1;
// 	  ++argid;
// 	}
//       }

//       for(int i=0;i<argid;++i){
// 	cout<<i<<' '<<args[i]<<endl;;
//       }
//       int input[2],output[2];
//       pid_t pid=start(cmd.c_str(),args,input,output);
//       string msg;
//       char buf[100];
//       atomic<bool> exit;
//       exit=0;
//       mutex mtx;
//       thread th_read([&](){
// 	while(!exit){
// 	  memset(buf,0,sizeof buf);
// 	  int r_num=read(input[0],buf,100);
// 	  if(r_num){
// 	    lock_guard<mutex> lc(mtx);
// 	    cout<<r_num<<endl;
// 	    cout<<"output>"<<buf<<endl;
// 	  }
// 	}
//       });
//       while(true){
// 	unique_lock<mutex> lc(mtx);
// 	cout<<"input>";
// 	msg="";
// 	cin>>msg;
// 	lc.unlock();
// 	if(string(msg)=="exit"){
// 	  break;
// 	}
// 	write(output[1],msg.c_str(),msg.size());
//       }
//       exit=true;
//       th_read.join();
//       cout<<"receive "<<(long long)stop(pid)<<endl;
      

//       for(int i=0;i<100;++i){
// 	if(args[i]){
// 	  delete[] args[i];
// 	}
//       }
      
//     }else{
//       cout<<"can't match regex"<<endl;
//     }
    
//   }
// }
#include<unistd.h>
#include<sys/wait.h>
//#include<sys/prctl.h>
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
    // while(true){
    //   char str[512]{0};
    //   scanf("%s",str);
    //   printf("%s",str);
    //   fflush(stdout);
    // }
    execl("/usr/bin/sh","sh",(char*)NULL);
    //exit(0);
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
      //printf("Reading ...\n");
      int r_num=read(output[0],buf,256);
      if(r_num){
        unique_lock<mutex> lck(mtx);
	//printf("len: %d\nbuf(%s)\n",r_num,buf);
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
    while((msg[len++]=getchar())!=EOF);
    msg[len-1]=0;
    // {
    //   unique_lock<mutex> lck(mtx);
    //   printf("msg: (%s)\n",msg);
    // }
    // printf("%d\n",kill(pid,0));
    if(kill(pid,0)==-1){
      printf("pid(%d) id died ..\n",pid);
      break;
    }
    // printf("write\n");
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
