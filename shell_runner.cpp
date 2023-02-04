#include "shell_runner.h" //https://www.thinbug.com/q/6171552
pid_t start_helper(const char *cmd, char *const argv[], int *input, int *output,
                   int *sigexit, promise<int> &started) {
  pid_t pid = 0;
  int status;

  pipe(input);
  pipe(output);
  pipe(sigexit);
  fcntl(sigexit[0], F_SETFL, fcntl(sigexit[0], F_GETFL));
  pid = fork();
  if (pid == 0) {
    fprintf(stderr,"start_helper start0\n");
    if (dup2(input[0], STDIN_FILENO) == -1) {
      fprintf(stderr, "error dup stdin  -> pipe \n");
    };
    fprintf(stderr,"processing res0");
    if (dup2(output[1], STDOUT_FILENO) == -1) {
      fprintf(stderr, "error dup stdout -> pipe \n");
    };
    fprintf(stderr,"processing res1");
    if (dup2(output[1], STDERR_FILENO) == -1) {
      fprintf(stderr, "error dup stderr -> pipe \n");
    };
    fprintf(stderr,"processing res2");
    close(input[1]);
    close(output[0]);
    close(sigexit[0]);
    // execvp(cmd, argv);
    fprintf(stderr,"processing res");
    string res = ([](const char *cmd, char *const *argv) -> string {
      string res = cmd;
      res += ' ';
      for (char *const *ptr = argv; ptr; ++ptr) {
        res += *ptr;
        res += ' ';
      }
      return res;
    }(cmd, argv));
    started.set_value(0);
    fprintf(stderr,"start_helper start");
    fprintf(stderr, "cmd: \"%s\"\n", res.c_str());
    sleep(5);
    write(sigexit[1], "exit", 4);
    close(sigexit[1]);
    close(output[1]);
    close(input[0]);
    exit(0);
  }
  close(output[1]);
  close(sigexit[1]);
  close(input[0]);

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
int start(const char *cmd, int *in, int *out, promise<pid_t> pidv) {
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
  }
  int input[2], output[2], sig[2];
  promise<int> started;
  pid_t pid = start_helper(string(cm[1]).c_str(), args, input, output, sig,
                           ref(started));
  pidv.set_value(pid);
  fprintf(stderr,"set pid\n");
  char exitbuf[10];
  auto startedd = started.get_future();
  //startedd.get();
  startedd.wait();
  fprintf(stderr,"starting\n");
  do {
    errno = 0;
    memset(exitbuf, 0, sizeof exitbuf);
    int len = read(sig[0], exitbuf, 4);
    if (len > 0) {
      fprintf(stderr, "\"%s\"\n", exitbuf);
      break;
    }
  } while (errno == EAGAIN);
  return stop(pid);
}
