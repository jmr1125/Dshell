#include"dshell.h"
int main(){
  initscr();
  start_color();
  //init_pair(1,COLOR_CYAN,COLOR_BLACK);
  raw();
  cbreak();
  noecho();
  keypad(stdscr,TRUE);

  dshell();

  endwin();
}
