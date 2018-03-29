// Editor.h
// The header for the Text Editor
// Programmed by James Bellian 03/24/18

#ifndef Editor_h
#define Editor_h

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


struct TextEditor;

#define MAXLENGTH 9999

// Editor is the main structure of the program, creates the ncurses window,
// switches between edit and command mode, 
typedef struct TextEditor
{
	char ** text; // the body text of the editor
	int x, y; // x and y coordinates of cursor
	int w, h; // width and height of the terminal window
	int scroll; // the number of lines scrolled down
	char mode; // 'e' for edit mode, 'c' for command, 'x' for exit 
	int input; // user input from keyboard
	int num_lines; // number of lines in the text field
} Editor;

// Initializes ncurses and sets variables within the struct 'e'
void init( Editor *e, char ** lines, int nl, char * fn);

// begins the main loop of the Editor (DOES NOT NEED CALLED, CALLED AFTER INIT)
void start(Editor *e);

// Draws text from the string buffer to the screen
void update_window(Editor *e);

// Prints blank spaces to clear out the screen
void clear_window( Editor *e);

bool type(Editor *e, char letter);

int strLen(char * str);

#endif
