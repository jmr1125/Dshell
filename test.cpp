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

void handle(int sig) {
  if (sig == SIGCHLD) {
    int pid, status;
    //printw("recv SIGCHLD");
    mvprintw(LINES-1,0,"bash died");
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
    // system("/usr/bin/bash --login");
    exit(0);
  }
  /*
    stdin <-input[1]
    stdout ->output[0]
  */
  close(input[0]);
  close(output[1]);
  std::mutex mtx;
  std::atomic<bool> exit;
  exit = false;
  signal(SIGCHLD, handle);
  char buf[256]{0};
  initscr();
  noecho();
  std::thread thr([&]() {
    while (!exit) {
      memset(buf, 0, sizeof buf);
      int r_num = read(output[0], buf, 256);
      if (r_num) {
        unique_lock<mutex> lck(mtx);
        move(0, COLS / 2);
        printw("buf>> %s", buf);
        refresh();
      }
      // move(LINES/2, COLS / 2);
      // printw("%d",(bool)exit);
      refresh();
    }
  });
  {
    int status;
    int len = 0;
    while (status != -1) {
      if (kill(pid, 0) == -1) {
        break;
      }
      char msg;
      msg = getch();
      // clrtoeol();
      clear();
      {
        unique_lock<mutex> lck(mtx);
        move(1, 1);
        printw("msg= %d", (int)msg);
        refresh();
      }
      if (msg == 'q')
        break;
      if (status == -1) {
        break;
      }
      write(input[1], &msg, 1);
    }
    printw("EXIT ...\n");
    refresh();
  }
  kill(pid, SIGKILL); // stop
  close(input[1]);
  close(output[0]);
  {
    int status = 0;
    waitpid(pid, &status, 0);
    move(LINES - 1, 1);
    printw("---return: %d---\n", status);
  }
  exit = true;
  thr.join();
  refresh();
  getch();
  endwin();
}
