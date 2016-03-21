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


inline void clear_screen()
{
    /*
    Clearing the screen of the terminal with dimensions as 80 * 61
   */
    int size_h = 80;
    int size_v = 24;

    printf("\033[1;1H");

    for(int i = 0; i < size_h * size_v; ++i)
        putchar(' ');

    printf("\033[1;1H");
}

#endif // MY_CONIO_H
