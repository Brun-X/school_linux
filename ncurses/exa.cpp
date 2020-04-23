#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>


void make_vertical_line(WINDOW *win, int x, int yStart, int yStop, char ch)
{
    for(int i = yStart; i <= yStop; i++)
    {
        wmove(win, i, x);
        waddch(win, ch);
    }

}


/*
void init_main_menu(WINDOW *win, std::shared_ptr<Menu> main_menu)
{
    main_menu->entries.push_back(std::make_pair("> That bitch Carol Baskin", 0));
    main_menu->entries.push_back(std::make_pair("> Get COVID-19", 0));
    main_menu->entries.push_back(std::make_pair("> Call bull shit", 0));
    main_menu->num_menu_entries = main_menu->entries.size();

    for(int i = 0; i < main_menu->num_menu_entries; i++)
    {
        
    }
}
*/

int main()
{
    initscr();
    cbreak();
    noecho();
    refresh();      // Important to refresh screen before refresh window
    

    WINDOW* win = newwin(24, 80, 0, 0);


    keypad(win, TRUE);	//Giver adgang til f. eks. pil op og ned på tastatur

    start_color();
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    wattron(win, COLOR_PAIR(2));



    wborder(win, '*','*','*','*','*','*','*','*');		//window border
 
    wmove(win, 3, 12);
    waddstr(win, "That bitch Carol Baskin");		//cursor position 0

    wmove(win, 5, 12);
    waddstr(win, "Get the corona virus");		//cursor position 1

    wmove(win, 7, 12);
    waddstr(win, "Watch hardcore midget porn");	//cursor position 2


    



    curs_set(1);
    wmove(win, 3, 10);  // window, y, x

    wrefresh(win);		// Refresh window
    

    int cursor_position = 0;
    int menu_entries = 3;

    while(1)
    {
        int key = wgetch(win);

        if(key == 'q') break;

        switch(key)
        {
            case KEY_UP :
                if(cursor_position - 1 >= 0) --cursor_position;   
                break;

            case KEY_DOWN :
                if(cursor_position + 1 < menu_entries) ++cursor_position;
                break;

            case KEY_ENTER :

            	wclear(win);

            	if(cursor_position == 0)
            	{
            		wmove(win, 5, 12);
    				waddstr(win, "She is indeed a bitch");		//cursor position 1
            	}
            
            	else if(cursor_position == 1)
            	{
            		wmove(win, 5, 12);
    				waddstr(win, "Lick public places");		//cursor position 1
            	}

            	else if(cursor_position == 2)
            	{
            		wmove(win, 5, 12);
    				waddstr(win, "Downloading: The internet");		//cursor position 1
            	}

            	wrefresh(win);		// Refresh window
            	break;

            default :
                break;
        }

        wmove(win, 3 + cursor_position * 2, 10);
        //refresh();
        //wrefresh(win);
    }

    delwin(win);
    endwin();

    return 0;
}