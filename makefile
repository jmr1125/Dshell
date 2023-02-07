check-syntax:
	make -s main
main:
	if [ ! -d check_syntax ];then mkdir check_syntax;fi
	make check_syntax/button
	make check_syntax/dshell
	make check_syntax/evtlistener
	make check_syntax/form
	make check_syntax/incfile
	make check_syntax/inputbox
	make check_syntax/iw
	make check_syntax/main
	make check_syntax/ow
	make check_syntax/pos
	make check_syntax/runnertest
	make check_syntax/shell_runner
	make check_syntax/simple
	make check_syntax/style
	make check_syntax/test
	make check_syntax/test2
check_syntax/button: button.cpp
	clang++ -fsyntax-only button.cpp
	cd check_syntax&&touch button
check_syntax/dshell: dshell.cpp
	clang++ -fsyntax-only dshell.cpp
	cd check_syntax&&touch dshell
check_syntax/evtlistener: evtlistener.cpp
	clang++ -fsyntax-only evtlistener.cpp
	cd check_syntax&&touch evtlistener
check_syntax/form: form.cpp
	clang++ -fsyntax-only form.cpp
	cd check_syntax&&touch form
check_syntax/incfile: incfile.cpp
	clang++ -fsyntax-only incfile.cpp
	cd check_syntax&&touch incfile
check_syntax/inputbox: inputbox.cpp
	clang++ -fsyntax-only inputbox.cpp
	cd check_syntax&&touch inputbox
check_syntax/iw: iw.cpp
	clang++ -fsyntax-only iw.cpp
	cd check_syntax&&touch iw
check_syntax/main: main.cpp
	clang++ -fsyntax-only main.cpp
	cd check_syntax&&touch main
check_syntax/ow: ow.cpp
	clang++ -fsyntax-only ow.cpp
	cd check_syntax&&touch ow
check_syntax/pos: pos.cpp
	clang++ -fsyntax-only pos.cpp
	cd check_syntax&&touch pos
check_syntax/runnertest: runnertest.cpp
	clang++ -fsyntax-only runnertest.cpp
	cd check_syntax&&touch runnertest
check_syntax/shell_runner: shell_runner.cpp
	clang++ -fsyntax-only shell_runner.cpp
	cd check_syntax&&touch shell_runner
check_syntax/simple: simple.cpp
	clang++ -fsyntax-only simple.cpp
	cd check_syntax&&touch simple
check_syntax/style: style.cpp
	clang++ -fsyntax-only style.cpp
	cd check_syntax&&touch style
check_syntax/test: test.cpp
	clang++ -fsyntax-only test.cpp
	cd check_syntax&&touch test
check_syntax/test2: test2.cpp
	clang++ -fsyntax-only test2.cpp
	cd check_syntax&&touch test2
