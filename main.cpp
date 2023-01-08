#include"dshell.h"
int main(){
  initscr();
  raw();
  keypad(stdscr,TRUE);
  //cbreak();
  noecho();

  dshell();

  endwin();
}
