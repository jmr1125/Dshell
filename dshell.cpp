#include"incfile.cpp"
#include"iow.h"
#include"evtlistener.h"
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
void dshell(){
  int maxy,maxx;
  getmaxyx(stdscr,maxy,maxx);
  WINDOW *win=create_newwin(maxy,maxx,0,0);
  keypad(win,TRUE);
  wOut ost(win);
  wIn ist(win);
  evtlistener el(win);
  ost<<curpos(2,3)<<"hello\n";
  ost<<curpos(2,4)<<"press q to exit";
  int i=0;
  string s;
  ist.setecho(true);
  ist<<s;
  ost<<s.c_str();
  while(true){
    el.sig=sig_next;
    //el.listen();
    ost<<curpos(5,1)<<(long long)i;
    while(el.sig==sig_next);
    ost<<curpos(5,2)<<(long long)i;
    ++i;
    auto res=el.res;
    int mousex,mousey;
    int mousestatus;
    if(res.ch==KEY_MOUSE){
      mousex=res.evt.x,mousey=res.evt.y;
      mousestatus=res.evt.bstate;
    }
    if(exit_cond(res.ch)){
      break;
    }
    ost<<curpos(5,5)<<(long long)res.ch<<' '<<(long long)res.evt.x<<' '<<(long long)res.evt.y;
  }
  destroy_win(win);
}
