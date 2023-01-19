#pragma once
#if( __has_include (<curses/curses.h>))
#include<curses/curses.h>
#endif
#if( __has_include (<curses.h>))
#include<curses.h>
#endif
#include<cstdio>
#include<stddef.h>
#include<thread>
#include<atomic>
#include<string>
#include<regex>
#include<mutex>
#include<utility>
using std::thread;
using std::atomic;
using std::string;
using std::regex;
using std::cmatch;
using std::lock_guard;
using std::mutex;
using std::unique_lock;
using std::pair;
using std::make_pair;
