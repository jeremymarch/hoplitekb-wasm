#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include <locale.h>
#include "accent.h"
#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;
char buffer[1024];

char *choices[] = { 
            "φέρω 1",
            "Choice 2",
            "Choice 3",
            "Choice 4",
            "Exit",
          };
char abc[] = "οἴσω";
int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{   
    setlocale(LC_ALL, "");
    WINDOW *menu_win;
    int highlight = 1;
    int choice = 0;
    int c;

    WINDOW *w = initscr();
    int scrheight = 0;
    int scrwidth = 0;
    getmaxyx(w, scrheight, scrwidth);

    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
        
    menu_win = newwin(scrheight - 2, scrwidth - 2, 1, 1);
    keypad(menu_win, TRUE);
    mvprintw(0, 2, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    print_menu(menu_win, highlight);
    while(1)
    {   c = wgetch(menu_win);
        UCS2 l = 0;
                l = transliterate(c);
        switch(c)
        {   case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else 
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                break;
            default:
                ucs2_to_utf8_string(&l, 1, buffer);
                mvprintw(scrheight - 1, 2, "Charcter pressed is = %3d Hopefully it can be printed as '%04X', %s", c, transliterate(c), buffer);
                refresh();
                break;
        }
        print_menu(menu_win, highlight);
        if(choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }   
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
    endwin();
    return 0;
}


void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;    

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win, A_REVERSE); 
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
