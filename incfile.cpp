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
using std::thread;
using std::atomic;
using std::string;
