#include"incfile.cpp"
#include"ow.h"
WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);
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
  WINDOW *win=create_newwin(24,80,0,0);
  wOut ost(win);
  ost<<curpos(5,5);
  ost<<"helloworld!!";
  //ost<<curpos(5,5)<<"helloworld!!"<<123ll;
  getchar();
  destroy_win(win);
  // addstr("hello");
  // refresh();
  // getchar();
}
