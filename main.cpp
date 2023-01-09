#include"dshell.h"
int main(){
  initscr();
  raw();
  //cbreak();
  noecho();
  keypad(stdscr,TRUE);

  dshell();

  endwin();
}
