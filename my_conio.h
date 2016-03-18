// Copyright (C) 2015 Daniil Anichin <anichindaniil@gmail.com>
// All rights reserved.
//
// Name:        my_conio.h
// Date:        2015.11.20
// Author:      Daniil Anichin

#ifndef MY_CONIO_H
#define MY_CONIO_H

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

char getch();

char getche();

inline void kb_wait()
{
    puts("Press any key to continue");
    getch();
}

#endif // MY_CONIO_H
