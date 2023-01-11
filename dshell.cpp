#include"incfile.cpp"
#include"iow.h"
#include"evtlistener.h"
#include"shell_runner.h"
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	//box(local_win, 0 , 0);
	wborder(local_win,'|','|','-','-','+','+','+','+');
	wrefresh(local_win);
	return local_win;
}
void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
bool exit_cond(int ch){
  return (ch&0x7f)=='q';
}
regex command(R"(^((?:".+")|(?:[^"][^ ]+[^"])|(?:[\w^ ]+))(.*)$)");
void dshell(){
  int maxy,maxx;
  getmaxyx(stdscr,maxy,maxx);
  WINDOW *win=create_newwin(maxy,maxx,0,0);
  keypad(win,TRUE);
  wOut ost(win);
  wIn ist(win);


  int input[2],output[2];
  pid_t pid;
  
  while(true){
    string cmd;
    (ost<<curpos(3,3)).Clrtoeol();
    wborder(win,'|','|','-','-','+','+','+','+');
    ost<<"ready> ";
    ist.setecho(true);
    ist>>cmd;
    if(cmd=="exit"){
      break;
    }
    cmatch cm;
    if(regex_match(cmd.c_str(),cm,command)){
      (ost<<curpos(5,5)).Clrtoeol();
      (ost<<curpos(5,6)).Clrtoeol();
      (ost<<curpos(5,8)).Clrtoeol();
      (ost<<curpos(30,5)).Clrtoeol();
      char *args[100];
      int argid=1;
      memset(args,0,sizeof args);
      args[0]=new char [string(cm[1]).size()+1];
      memcpy(args[0],string(cm[1]).c_str(),string(cm[1]).size());
      args[0][string(cm[1]).size()]=0;
      int pos=0;
      char str[100]{0};
      memcpy(str,string(cm[2]).c_str(),string(cm[2]).size());
      ist.setecho(false);
      wborder(win,'|','|','-','-','+','+','+','+');
      (ost<<curpos(5,5)).Clrtoeol();
      ost<<curpos(5,5)<<">>"<<string(cm[1]).c_str();
      (ost<<curpos(5,6)).Clrtoeol();
      ost<<curpos(5,6)<<">>"<<string(cm[2]).c_str();
      (ost<<curpos(5,8)).Clrtoeol();
      ost<<curpos(5,8);
      str[string(cm[2]).size()]=' ';
      int len=strlen(str);
      for(int i=0;i<len;++i){
	if(str[i]==' '){
	  int lenn=i-pos+1;
	  args[argid]=new char[lenn+1];
	  memset(args[argid],0,lenn+1);//+1 to end the str with '\0'
	  for(int j=pos;j<=i;++j){
	    args[argid][j-pos]=str[j];
	  }
	  pos=i+1;
	  ++argid;
	}
      }

      for(int i=0;i<argid;++i){
	move(8,5+i);
	wprintw(win,"%d:\"%s\"",i,args[i]);
      }
      int input[2],output[2];
      pid=start(cmd.c_str(),args,input,output);
      string msg;
      char buf[100];
      while(true){
	if(string(msg)=="exit"){
	  break;
	}
	ost<<curpos(30,3)<<">>";
	ost.Clrtoeol();
	wborder(win,'|','|','-','-','+','+','+','+');
	ist.setecho(true);
	msg="";
	ist>>msg;
	ist.setecho(false);
	write(output[1],msg.c_str(),msg.size());
	memset(buf,0,sizeof buf);
	read(input[0],buf,100);
	ost<<curpos(30,5);ost.Clrtoeol();
	ost<<curpos(30,5)<<">>"<<buf;
      }
      ost<<curpos(30,2)<<"receive "<<(long long)stop(pid);
      

      for(int i=0;i<100;++i){
	if(args[i]){
	  delete[] args[i];
	}
      }
      
    }else{
      ost<<curpos(5,5)<<"can't match regex";
    }
    
  }


  destroy_win(win);
}
