#include"incfile.cpp"
#include"ow.h"
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
void dshell(){
  int maxy,maxx;
  getmaxyx(stdscr,maxy,maxx);
  WINDOW *win=create_newwin(maxy,maxx,0,0);
  keypad(win,TRUE);
  wOut ost(win);
  evtlistener el(win);
  ost<<curpos(2,3)<<"hello\n";
  ost<<curpos(2,4)<<"press q to exit";
  while(true){
    el.listen();
    auto res=el.res;
    if(res.ch==KEY_MOUSE){
      if(getmouse(&res.evt)==OK){
	ost<<curpos(5,5)<<"x,y,z = "<<(long long)res.evt.x<<","<<(long long)res.evt.y<<","<<(long long)res.evt.z<<'\n';
	ost<<curpos(5,6)<<"status = "<<(long long)(res.evt.bstate)<<'\n';
      }
      ost<<curpos(5,7)<<"key_mouse";
    }
    ost<<curpos(5,8)<<"ch = "<<(long long)res.ch<<"          "<<(long long)KEY_MOUSE;
    if( (res.ch&0x7f)=='q'){
      break;
    }
  }
  destroy_win(win);
}
