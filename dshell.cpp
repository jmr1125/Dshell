#include"incfile.cpp"
int main(){
  initscr();
  raw();
  keypad(stdscr,TRUE);
  noecho();
  endwin();
}
