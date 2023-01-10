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


  


  destroy_win(win);
}
