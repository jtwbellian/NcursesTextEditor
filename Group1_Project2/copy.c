//copy.c
//written by Derek
#include "copy.h"

int startx, starty;
int endx, endy;
int tempx,tempy;
int w,h;

void copyStart() {
   getmaxyx(stdscr,h,w);
	//get cursor starting position
	getyx(stdscr, tempy, tempx);
	mvprintw(0,w-20, "%s", "Starting index chosen.     ");
	move(tempy, tempx);
	getyx(stdscr, starty, startx);
   refresh();
}


void copyEnd() {
	
	//get cursor ending position
	getyx(stdscr, endy, endx);
	getyx(stdscr, tempy, tempx);
	
	mvprintw(0, w-20, "%s", "End index chosen.        ");
	move(tempy, tempx);
}

void paste(char * str) {
	
	int pastex, pastey;
	//char copyString[99]; //string to store copied text
   int indx = 0;
   
	//load copied text into string
	for (int s = startx; s < endx; s++) {
		str[indx] = mvinch(starty, s);
      indx ++;
	}
   mvprintw(0,w/2,"COPIED \"%s\"        " ,str);
}
