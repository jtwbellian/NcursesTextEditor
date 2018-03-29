// textBuffer.c 
// Programmed by John Barulich

#include "textBuffer.h"

int addNewLine(char ** textBufferPtr, int line, int lineCount){
	int i;
	//Move all indices down 1 to make room for the new line
	for (i = lineCount; i >= line; i--){
		textBufferPtr[i] = textBufferPtr[i - 1];
	}

	//Creating the new line where it should be
	textBufferPtr[line - 1] = malloc(MAX_LEN_ROW * sizeof *textBufferPtr); 
	
	return lineCount + 1;
	//Update lineCount
}

//Returns the number of lines of the initial text file
//Inserts each line into an array of char*
int fillBuffer(char* file, char* textBuffer[], int lineCount){
	FILE *in;
	in = fopen(file, "r");
	int i;
	//Allocate memory for each pointer of the buffer
	for (i = 0; i < MAX_LEN_ROW; i++){
		textBuffer[i] = malloc(MAX_LEN_ROW * sizeof *textBuffer);
	}
	
	char c;
	while (lineCount < MAX_LEN_ROW && (c = fgetc(in)) != EOF ){
		if (c == '\n'){
			lineCount++;
		}
		else if (c == '\t'){
		//	printf("------found a tab-------\n");
			char* s = "        ";
			textBuffer[lineCount] = strcat(textBuffer[lineCount], s);
		}
		else{
			char str[2];
			str[0] = c;
			str[1] = '\0';
			textBuffer[lineCount] = strcat(textBuffer[lineCount], str);	

		}
	}
	return lineCount;
}

