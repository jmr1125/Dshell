#include "incfile.cpp"
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
using std::mutex;
using std::unique_lock;

std::atomic<bool> isexit;
void handle(int sig) {
  if (sig == SIGCHLD) {
    int pid, status;
    mvprintw(LINES - 1, 0, "bash died");
    isexit = true;
    while ((pid = waitpid(-1, &status, WNOHANG) > 0)) {
    };
  }
}
int main(int argc, char **argv) {
  int input[2], output[2];
  pipe(input);
  pipe(output);
  pid_t pid = fork();
  if (pid == 0) {
    if (dup2(input[0], 0) == -1) {
      printf("error ");
      exit(1);
    };
    if (dup2(output[1], STDOUT_FILENO) == -1) {
      printf("error1");
      exit(1);
    };
    if (dup2(output[1], STDERR_FILENO) == -1) {
      printf("error2");
      exit(1);
    };
    close(input[1]);
    close(output[0]);
    execl("/usr/bin/bash", "bash", "--login", (char *)NULL);
    exit(0);
  }
  /*
    stdin <-input[1]
    stdout ->output[0]
  */
  close(input[0]);
  close(output[1]);
  std::mutex mtx;
  isexit = false;
  signal(SIGCHLD, handle);
  // auto ffunc = [&](int sig) {
  //   if (sig == SIGCHLD) {
  //     int pid, status;
  //     mvprintw(LINES - 1, 0, "bash died");
  //     // exit = true;
  //     while ((pid = waitpid(-1, &status, WNOHANG) > 0)) {
  //     };
  //   }
  //   return;
  // };
  // void (*func)(int) = ffunc;
  // auto add = [](int a, int b) { return a + b; };
  // int (*addd)(int, int) = add;
  // signal(SIGCHLD, func);
  initscr();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  std::thread Output([&]() {
    char buf[256]{0};
    while (!isexit) {
      memset(buf, 0, sizeof buf);
      int r_num = read(output[0], buf, 256);
      if (r_num) {
        unique_lock<mutex> lck(mtx);
        // move(0, COLS / 2);
        // printw("buf>> %s", buf);
        mvprintw(0, COLS / 2, "buf>> %s", buf);
        refresh();
      }
    }
  });
  while (true) {
    attron(A_NORMAL);
    if (isexit) {
      mvprintw(LINES - 1, 1, "exit");
      refresh();
      break;
    }
    auto msg = getch();
    if (msg == ERR) {
      mvprintw(1, 1, "no input");
      clrtoeol();
      refresh();
      continue;
    } else {
      // clear();
      mvprintw(1, 1, "msg = %d %c", msg, msg), clrtoeol();
      // if (msg == 'q') {
      // if (msg == KEY_F(1)) {
      if (msg == KEY_F(2)) {
        mvprintw(LINES - 1, 1, "--- %s ---", "EXIT");
        break;
      } else if (msg == 'l') {
        clear();
      }
      if (isexit) {
        mvprintw(LINES - 1, 1, "exit");
        refresh();
        break;
      }
      write(input[1], &msg, 1);
      refresh();
    }
  }
  kill(pid, SIGKILL); // stop
  close(input[1]);
  close(output[0]);
  {
    int status = 0;
    waitpid(pid, &status, 0);
    mvprintw(LINES - 1, 0, "---return: %d---\n", status);
  }
  isexit = true;

  Output.join();
  mvprintw(6, 1, "output stop");
  refresh();
  // getch();
  endwin();
}
