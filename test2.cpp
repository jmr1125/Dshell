#include "incfile.cpp"
#include "shell_runner.h"
int main() {
  int fdm;
  pid_t pid = start("python", &fdm);
  printf("pid= %d\nfdm= %d\n", pid, fdm);
  fflush(stdout);
  fd_set fd_in;
  int rc;
  char input[16];

  while (1)

  {

    // Wait for data from standard input and master side of PTY
    FD_ZERO(&fd_in);
    FD_SET(0, &fd_in);
    FD_SET(fdm, &fd_in);
    rc = select(fdm + 1, &fd_in, NULL, NULL, NULL);
    switch (rc) {
    case -1: {
      fprintf(stderr, "Error %d on select()\n", errno);
      exit(1);
    }
    default: {
      // If data on standard input
      if (FD_ISSET(0, &fd_in)) {
        rc = read(0, input, sizeof(input));
        if (rc > 0) {
          // Send data on the master side of PTY
          write(fdm, input, rc);
        } else {
          if (rc < 0) {
            fprintf(stderr, "Error %d on read standard input\n", errno);
            exit(1);
          }
        }
      }
      // If data on master side of PTY
      if (FD_ISSET(fdm, &fd_in)) {
        rc = read(fdm, input, sizeof(input));
        if (rc > 0) {
          // Send data on standard output
          write(1, input, rc);
        } else {
          if (rc < 0) {
            fprintf(stderr, "Error %d on read master PTY\n[%s]", errno,strerror(errno));
            fprintf(stderr, "Stop...\n", errno);
            exit(1);
          }
        }
      }
    }
    } // End switch
  }   // End while
  // write(fdm, "1+2\n", 3);
  // char res[10]{0};
  // int a = -1;
  // while (a != 0) {
  //   a=read(fdm, res, 10);
  //   printf("%d\n", a);
  //   printf("[%s]\n", res);
  //   sleep(1);
  // }
  // initscr();
  // nodelay(stdscr, TRUE);
  // keypad(stdscr, TRUE);
  // noecho();

  // char c = 0;
  // while (true) {
  //   {
  //     char c1 = getch();
  //     if (c1 == ERR)
  //       continue;
  //     if (c1 == c && c == '\n') {
  //       //break;
  //     }
  //     c = c1;
  //   }
  //   mvprintw(1, 1, "%d", c);
  //   clrtoeol();
  //   write(fdm, &c, 1);
  //   {
  //     char buf[100]{0};
  //     int len = read(fdm, buf, 100);
  //     if (len > 0) {
  //       mvprintw(5,1,"buf=[%s]\n", buf);
  //     }
  //   }
  // }
  // mvprintw(5,10,"status: %d",stop(pid));
  // endwin();
  close(fdm);
}
