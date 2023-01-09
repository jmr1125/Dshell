#include "incfile.cpp"


//from https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void dshell();
bool exit_cond(int);
