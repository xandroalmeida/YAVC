echo off
set cpplint_options=--filter=-build/include,-readability/function
set cpplint=cpplint.py %cpplint_options%

rmdir report.dir /s /q
mkdir report.dir

set FILE_LIST=(aboutdialog.cpp, aboutdialog.h, main.cpp, mainwindow.cpp, mainwindow.h, movieconvertthread.cpp, movieconvertthread.h, movieinfo.cpp, movieinfo.h, optionsdialog.cpp, optionsdialog.h, settings.cpp, settings.h, videoprofile.cpp, videoprofile.h)

FOR %%f in %FILE_LIST% do %cpplint% %%f 
