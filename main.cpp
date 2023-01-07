#include"dshell.h"
int main(){
  initscr();
  raw();
  keypad(stdscr,TRUE);
  noecho();

  dshell();

  endwin();
}
