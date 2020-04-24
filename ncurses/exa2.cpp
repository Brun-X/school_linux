
#include <SenseHat.h>
#include <string>
#include <vector>
#include <iostream>
#include <ncurses.h>

enum{TEMPERATURE=0, HUMIDITY=1, PRESSURE=2};


void make_vertical_line(WINDOW *win, int x, int yStart, int yStop, char ch)
{
    for(int i = yStart; i <= yStop; i++)
    {
        wmove(win, i, x);
        waddch(win, ch);
    }

}



void init_main_menu(WINDOW *win)
{
    wborder(win, '*','*','*','*','*','*','*','*');		//window border
 
 	wmove(win, 3, 10);
 	waddstr(win, "[");		//cursor position 0
    wmove(win, 3, 12);
    waddstr(win, "> Get temperature");		//cursor position 0

    wmove(win, 5, 10);
 	waddstr(win, "[");
    wmove(win, 5, 12);
    waddstr(win, "> Get humidity");		//cursor position 1

    wmove(win, 7, 10);
 	waddstr(win, "[");
    wmove(win, 7, 12);
    waddstr(win, "> Get pressure");	//cursor position 2
}

void get_env_sensor_data(SenseHat* s, float* env)
{
	env[TEMPERATURE] = s->ObtenirTemperature();
	env[HUMIDITY] = s->ObtenirHumidite();
	env[PRESSURE] = s->ObtenirPression();
}

int main()
{
	float env_sensors[3];

	SenseHat carte;
	carte.Effacer();

    initscr();
    cbreak();
    noecho();
    refresh();      // Important to refresh screen before refresh window
    

    WINDOW* win = newwin(24, 80, 0, 0);


    keypad(win, TRUE);	//Giver adgang til f. eks. pil op og ned på tastatur

    start_color();
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_RED, COLOR_GREEN);
    wattron(win, COLOR_PAIR(2));

    init_main_menu(win);
    int cursor_position = 0;
    int main_menu_entries = 3;
    int whatMenuAmIIn = 0;

    curs_set(1);
    wmove(win, 3, 11);  // window, y, x

    wrefresh(win);		// Refresh window
    
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
                if(cursor_position + 1 < main_menu_entries) ++cursor_position;
                break;

            case KEY_ENTER :
            	get_env_sensor_data(&carte, env_sensors);
            	whatMenuAmIIn = cursor_position;
            	cursor_position = 0;
            	wclear(win);
            	//wrefresh(win);		// Refresh window

            	if(whatMenuAmIIn == TEMPERATURE)
            	{
            		wborder(win, '*','*','*','*','*','*','*','*');		//window border
            		wmove(win, 3, 12);
    				wprintw(win, "Temperature is: %.2f Degrees C", env_sensors[TEMPERATURE]);		//cursor position 1
            	}
            
            	else if(whatMenuAmIIn == HUMIDITY)
            	{
            		wborder(win, '*','*','*','*','*','*','*','*');		//window border
            		wmove(win, 3, 12);
    				wprintw(win, "Humidity is: %.0f %", env_sensors[HUMIDITY]);
            	}

            	else if(whatMenuAmIIn == PRESSURE)
            	{
            		wborder(win, '*','*','*','*','*','*','*','*');		//window border
            		wmove(win, 3, 12);
    				wprintw(win, "Atmospheric pressure is: %.2f hPa", env_sensors[PRESSURE]);
            	}
            	
            	wmove(win, 10, 12);
            	wattron(win, COLOR_PAIR(3));
            	wprintw(win, "Back");
            	wattroff(win, COLOR_PAIR(3));
            	
            	wrefresh(win);		// Refresh window            	
            	
            	break;

            default : 
            	break;

        }

        wmove(win, 3 + cursor_position * 2, 11);
        //wrefresh(win);		// Refresh window
        //refresh();
        //wrefresh(win);
    }

    delwin(win);
    endwin();

    return 0;
}