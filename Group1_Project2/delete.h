#ifndef Delete_h
#define Delete_h

#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN_ROW 999
#define CHAR_PER_LINE 100

int Delete (char** text, int row, int lineCount);

#endif