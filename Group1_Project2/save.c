// save.c 
// Programmed by Derek Sittenauer

 #include <stdio.h>
 #include <stdlib.h>
 #include <ncurses.h>
 #include "save.h"

void save(char * filename, int num_lines, char ** text, int h, int w) {
   FILE *file = fopen(filename, "w");
   
   for (int i = 0; i < num_lines; i++) {
	
	   for (int j = 0; j < strlen(text[i]); j++) {
			fputc(text[i][j], file);
		}
	fprintf(file, "\r\n");
   }
   mvprintw(h/2+1, w/3,"File saved");
   fclose(file);
 }

