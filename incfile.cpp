#pragma once
#if (__has_include(<curses/curses.h>))
#include <curses/curses.h>
#endif
#if (__has_include(<curses.h>))
#include <curses.h>
#endif
#include <atomic>
#include <chrono>
#include <cstdio>
#include <future>
#include <mutex>
#include <pty.h>
#include <regex>
#include <stddef.h>
#include <string>
#include <sys/ioctl.h>
#include <thread>
#include <utility>
using std::atomic;
using std::cmatch;
using std::future;
using std::lock_guard;
using std::make_pair;
using std::mutex;
using std::pair;
using std::promise;
using std::regex;
using std::string;
using std::thread;
using std::unique_lock;
