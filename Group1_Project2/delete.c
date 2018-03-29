#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "delete.h"

int Delete(char ** text, int row, int lineCount){
	
	//Creating the new line where it should be

	//Move lines up to replace blank line
	for (int i = row; i <= lineCount; i++){
		text[i] = text[i+1];
	}
	//Update lineCount
	return lineCount - 1;
}
