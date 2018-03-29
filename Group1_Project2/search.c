// search.c 
// Programmed by Robert Sarvis

#include "search.h"
#include <ncurses.h>			
#include <string.h> 

void search(char **str)
{	
    mvprintw(LINES - 5, 0, "%s",mesg);              		
	echo();
    getstr(sub);
	noecho();
    mvprintw(LINES - 5, 0, "You Entered: %s", sub);
    refresh();
    for ( int n = 0; n < SIZE; ++n )
    {
        j=0;
      for(i=0; str[n][i]; i++)
      {
        if(str[n][i] == sub[j])
        {
          for(k=i, j=0; str[n][k] && sub[j]; j++, k++)
            if(str[n][k]!=sub[j])
                break;
           if(!sub[j])
            {
            flag = false;
            whichstring = n;
            linelocation = i;
            wmove(stdscr,n,i);
            break;
            }
        }
      }
    }
    if ( flag )
    {
        mvprintw(LINES - 4, 0, "Not a substring");
    }
    refresh();
    if ( !flag )
    {
        mvprintw(LINES - 3, 0, "Do you want to replace the string located here with another? y/n: ");
        answer = getch();
        
        if ( answer == 'y' || answer == 'Y' )
        {
		    echo();
            mvprintw(LINES - 2, 0, "Replacement: ");
            getstr(newstr);
		    noecho();
            char *p = &newstr;
            char *h = &str[whichstring][linelocation];
            strcpy(h, p); 
            mvprintw(LINES -1, 0, "Completed");           
        }
	    refresh();
    }
    refresh();
}


