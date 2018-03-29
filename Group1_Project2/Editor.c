// Editor.c
// Implementation for editor functions
// Programmed by James Bellian 03/24/18

#include "Editor.h"

char filename[20];
bool hasCopied = false;

// Initializes ncurses and prepares the editor window

void init(Editor *e, char ** lines, int nl, char * fn)
{
	strncpy(filename, fn, 20);
	// start/setup nCurses
        initscr();
        raw();
        keypad(stdscr, TRUE);
        noecho();
	size_t n = 20;
	
	e->num_lines = nl;
	// set to 2 to give room for margins
	e->x = 1;
	e->y = 1;
	e->text = lines;
	e->scroll = 0;
	e->mode = 'e';
	
	getmaxyx(stdscr, e->h, e->w);

	mvprintw(e->h/2,e->w/3, " Welcome to Group 1 Text Editor! ");
        
	// 'Header' and 'Footer'
	wattron(stdscr,A_REVERSE);
	mvprintw(0,0,"Group 1\t\tFILE: %s\n", filename);

        mvprintw(e->h-1,1, (e->mode == 'e') ? "Line %d,%d) \t-EDIT MODE-":"Line %d,%d \t-COMMAND MODE-", e->y + e->scroll, e->x);
        wattroff(stdscr,A_REVERSE);
	
	refresh();

	start(e);
}

// Begins the main loop of the program 
void start(Editor *e)
{
	
	int ch;
	while (e->mode != 'x')
        {
               	 ch  = getch(); // gets the users key
		
		// read Keyboard cursor movement in both modes
                switch(ch)
                {
                case KEY_LEFT:
                        if (e->x > 1)
                                e->x --;
                        break;
                case KEY_RIGHT:
                        if (e->x < e->w-1)
                                e->x ++;
                        break;
                case KEY_UP:
                        if (e->y > 1)
                                e->y --;
                        else if (e->scroll > 0)
                                e->scroll --;
                        break;
                case KEY_DOWN:
                        if (e->y < e->h-2)
                                e->y ++;
                        else
                                e->scroll ++;
                        break;

                case 27: // ESC pressed toggle mode
                        if (e->mode == 'e')
				e->mode = 'c';
			else
				e->mode = 'e';
			mvprintw(e->h-1,1, (e->mode == 'e') ? "Line %d,%d \t-EDIT MODE-   ":"Line %d,%d \t-COMMAND MODE-",
				 e->y + e->scroll, e->x);		
                        refresh();
			break;
		}
		
		// command input when in Command Mode
		if (e->mode == 'c')
		{
			switch(ch)
			{
			// Quit 
			case 'q': case 'Q':
				e->mode = 'x';
				break;
			// add line
			case 'o': case 'O':
				e->num_lines = addNewLine(e->text, e->y + e->scroll , e->num_lines);
				break;
			// Delete Line 
			case 'd' : case 'D':
               Delete(e->text, e->y + e->scroll -1, e->num_lines);
				break;
			// Search and replace for a string 
			case 'f' : case 'F':
				{
				search(e->text);
				break;
				}
         // Save
			case 's' : case 'S':
				save(filename, e->num_lines, e->text, e->h, e->w);	
				break;
         // Yank / Copy
			case 'y' : case 'Y': 
				if (!hasCopied)
					{
					copyEnd();
					hasCopied = true;
					}
				else
					{
					copyStart();
					hasCopied = false;
					}
				break;
         // Paste
			case 'p' : case 'P':
            {
               if (hasCopied)
               {
                  char output[99];
                  paste(output);
                  mvprintw(0,e->w/2,"GOT \"%s\"       " ,output);
                  refresh();
                  type(e, output[0]);
                  type(e, output[1]);
                  
                  for(int i = 0 ; i < strLen(output); i ++)
                  {
                     char c = output[i];
                     type(e, c);
                  }
               }
				break;
            }
			}		
		}
		// Keyboard input when in Edit Mode
		if (e->mode == 'e')
		{
		switch(ch)
			{
			// IGNORE THE FOLLOWING KEY COMMANDS (Handled above)
			case KEY_UP:
			case KEY_DOWN:
			case KEY_LEFT:
			case KEY_RIGHT:
			case 27:
			break;
			
			case 10: // Press enter
				e->num_lines = addNewLine(e->text, e->y + e->scroll , e->num_lines);
               break;
               
			case KEY_RESIZE: // Recalculate window size
				getmaxyx(stdscr,e->h,e->w);			
				break;
			
			case KEY_DC: case KEY_DL: // line delete
				{
               Delete(e->text, e->y + e->scroll -1, e->num_lines);
					break;
				}
            case 127: case 8: // Backspace
        	        	{
                     // blank out line
                     char * newline = e->text[e->y + e->scroll -1];
                     int size = strLen(newline);

                     for(int i = e->x-1; i < size; i ++)
                     {
                           newline[i] = newline[i+1];
                     }

             			// adjust cursor
                		if (e->x >1)
                		{
                        		e->x -= 1;
                		}
                		else
                		{
                        		e->x = e->w - 1;
                        		if (e->y > 1)
                               		 	e->y --;
                		}

                		break;
				}
			// For everything else, handle in type function
			default:
				type(e,ch);
            break;
			};
		}

                clear_window(e);
                update_window(e);
                wattron(stdscr, A_REVERSE);
		mvprintw(e->h-1,1, (e->mode == 'e') ? "Line %d,%d \t-EDIT MODE-":"Line %d,%d \t-COMMAND MODE-", e->y + e->scroll, e->x);
                wattroff(stdscr,A_REVERSE);
                wmove(stdscr,e->y,e->x);

                refresh();
       }

        clear_window(e);
        mvprintw(e->h/2,e->w/3,"PROGRAM WILL NOW TERMINATE");
        mvprintw(e->h/2+1,e->w/3,"Goodbye!");
  	refresh();
        getch();
	endwin();
}


// Draws text from string buffer to window
void update_window(Editor *e)
{
	// recalculates window size (in case it has been resized since last update)
        getmaxyx(stdscr,e->h,e->w);

        // Displays the text between the scroll position and the bottom of the window
        for(int i = 0; (i < e->h); i ++)
        {
                mvprintw(i + 1, 1, "%s", e->text[i + e->scroll]);
        }
}

// Prints blank spaces to clear out the window
void clear_window( Editor *e)
{
        for(int i = 1; i < e->h; i++)
        for(int j = 0; j < e->w; j++)
        {
		if (j==0 && i >= e->num_lines - e->scroll)
                        mvprintw(i,j,"~");
                else
                        mvprintw(i,j," ");
        }
}

// Types the current character into the text field. 
// returns true if successful, false if unexpected letter given
bool type(Editor *e, char letter)
{
	char * newline; // pointer to hold the line to be modified
	int size; // size of the new line
	char hanging_char; //  letter to be pushed down
	char tmp_char;

	// Not a printable character
	if (letter < 32 && letter > 126)
		return false;
	
	// Not a valid line to type on 
   if (e->y + e->scroll > e->num_lines || letter == '\n')
		return false;

	// get the current line to manipulate
	newline = e->text[e->y + e->scroll -1];
   size = strLen(newline);
	
   // fix endlines
   if (newline[0] == '\n')
   {
      newline[0] = ' ';
      newline[1] = '\0';
   }
	// Expand lines that are empty (fill spaces in void)
	while (size < e->x - 1)
		{
		newline[size]= ' ';
		newline[size + 1] = '\0';
		size = strLen(newline);
		}
   
        // line is not full, so simply add char at cursor
        if (size < e->w - 1)
        {
                newline[size] = '\0';

                for(int i = size; i > e->x - 1; i --)
                {
                        newline[i] = newline[i-1];
                }

                newline[e->x - 1] = letter;
		e->text[e->y + e->scroll -1] = newline;
		if (e->x < e->w - 1)
			e->x += 1;
		else
		{
			e->x = 1;
			e->y +=1;
		}
        }
	else // When the line reaches the end, push down hanging character
	{
		hanging_char = newline[size-1];

		for(int i = size - 1; i > e->x - 1; i --)
                {
                        newline[i] = newline[i-1];
                }
	
                newline[e->x - 1] = letter;
		e->text[e->y + e->scroll - 1] = newline;
		
		
		for(int j = e->y + e->scroll ; j < e->num_lines; j ++)
		{
			newline = e->text[j];
			size = strLen(newline);
			
			// if the following line has space, insert hanging char
			if (size < e->w - 1) 
			{	
				for(int i = size; i > 0; i --)
	               		{
                	        	newline[i] = newline[i-1];
        	 	        }
				
				newline[0] = hanging_char;	
				e->text[j] = newline;

				// Exit loop
				j = e->num_lines;	
			}
			else // if the line does not, continue shifting 
			{
				tmp_char = newline[size-1];

                            for(int i = size; i > 0; i --)
                                {
                                        newline[i] = newline[i-1];
                                }
				newline[size] = '\0';			
				newline[0] = hanging_char;	
				e->text[j] = newline;
				
				hanging_char = tmp_char;

			}		
	
		}
      
	if (e->x < e->w - 1)
		e->x += 1;
	else
        {
              	e->x = 1;
               	e->y +=1;
        }

	}
	
	return true;
}

// returns the length of a c-string
int strLen(char * str)
{
	int i = 0;
	while (str[i] != '\0')
	{	
		i++;
	}

	return i;

}


