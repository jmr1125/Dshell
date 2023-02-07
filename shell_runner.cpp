#include "shell_runner.h" //https://www.thinbug.com/q/6171552
pid_t start_helper(const char *cmd, char *const argv[], int fdm, int fds) {
  pid_t pid = 0;
  int status;

  pid = fork();
  if (pid == 0) {
    close(fdm);
    // struct termios slave_orig_term_settings; // Saved terminal settings
    // struct termios new_term_settings;        // Current terminal settings
    // // Save the defaults parameters of the slave side of the PTY
    // tcgetattr(fds, &slave_orig_term_settings);
    // // Set RAW mode on slave side of PTY
    // new_term_settings = slave_orig_term_settings;
    // cfmakeraw(&new_term_settings);
    // tcsetattr(fds, TCSANOW, &new_term_settings);
    // fprintf(stderr, "start_helper start0\n");
    if (dup2(fds, STDIN_FILENO) == -1) {
      fprintf(stderr, "error dup stdin  -> fdm \n");
    };
    // fprintf(stderr, "processing res0");
    if (dup2(fds, STDOUT_FILENO) == -1) {
      fprintf(stderr, "error dup stdout -> fdm \n");
    };
    // fprintf(stderr, "processing res1");
    if (dup2(fds, STDERR_FILENO) == -1) {
      fprintf(stderr, "error dup stderr -> fdm \n");
    };
    close(fds);
    // setsid();
    ioctl(0, TIOCSCTTY, 1);
    // fprintf(stderr, "processing res2");
    // execvp(cmd, argv);
    // fprintf(stderr, "processing res");
    // string res = ([](const char *cmd, char *const *argv) -> string {
    //   string res = cmd;
    //   res += ' ';
    //   for (char *const *ptr = argv; ptr; ++ptr) {
    //     res += *ptr;
    //     res += ' ';
    //   }
    //   return res;
    // }(cmd, argv));
    // fprintf(stderr, "start_helper start");
    // fprintf(stderr, "cmd: \"%s\"\n", res.c_str());
    // sleep(5);
    // fprintf(stderr, "%s", cmd);
    execvp(cmd, argv);
    exit(1);
  }

  return pid;
}
int stop(pid_t pid) {
  int status;
  kill(pid, SIGKILL);
  waitpid(pid, &status, 0);
  return status;
}
int get_status(pid_t pid) {
  int status;
  waitpid(pid, &status, WNOHANG | WUNTRACED);
  return status;
}
pid_t start(const char *cmd, int *FDM) {
  static regex command(R"(^((?:".+")|(?:[^"][^ ]+[^"])|(?:[\w^ ]+))(.*)$)");
  static std::chrono::milliseconds span(100);
  cmatch cm;
  char *args[100];
  regex_match(cmd, cm, command);
  {
    int argid = 1;
    memset(args, 0, sizeof args);
    args[0] = new char[string(cm[1]).size() + 1];
    memcpy(args[0], string(cm[1]).c_str(), string(cm[1]).size());
    args[0][string(cm[1]).size()] = 0;
    int pos = 0;
    char str[100]{0};
    memcpy(str, string(cm[2]).c_str(), string(cm[2]).size());
    str[string(cm[2]).size()] = ' ';
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
      if (str[i] == ' ') {
        int lenn = i - pos + 1;
        args[argid] = new char[lenn + 1];
        memset(args[argid], 0, lenn + 1); //+1 to end the str with '\0'
        for (int j = pos; j <= i; ++j) {
          args[argid][j - pos] = str[j];
        }
        pos = i + 1;
        ++argid;
      }
    }
    --argid;
    delete args[argid];
    args[argid] = NULL;
  }
  int fdm, fds;
  if (openpty(&fdm, &fds, NULL, NULL, NULL) == -1) {
    return -1;
  }
  pid_t pid = start_helper(string(cm[1]).c_str(), args, fdm, fds);
  *FDM = fdm;
  close(fds);
  return pid;
}
