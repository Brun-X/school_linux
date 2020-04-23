#include <ncurses.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

typedef struct
{
    int num_menu_entries;
    int curs_position = 0;
    std::vector<std::pair<std::string, int>> entries;
} Menu;

void make_vertical_line(WINDOW *win, int x, int yStart, int yStop, char ch)
{
    for(int i = yStart; i <= yStop; i++)
    {
        wmove(win, i, x);
        waddch(win, ch);
    }

}

void init_main_menu(WINDOW *win, std::shared_ptr<Menu> main_menu)
{
    main_menu->entries.push_back(std::make_pair("> That bitch Carol Baskin", 0));
    main_menu->entries.push_back(std::make_pair("> Get COVID-19", 0));
    main_menu->entries.push_back(std::make_pair("> Call bull shit", 0));
    main_menu->num_menu_entries = main_menu->entries.size();

    for(int i = 0; i < main_menu->num_menu_entries; i++)
    {
        wmove(win, (2 * i + 3), 12);
        main_menu->entries[i].second = 2 * i + 3;
        waddstr(win, main_menu->entries[i].first.c_str());
    }
    

}


int main()
{
    initscr();
    cbreak();
    noecho();
    refresh();      // Important to refresh screen before refresh window
    

    WINDOW* win = newwin(24, 80, 0, 0);

    std::shared_ptr<Menu> main_menu(new Menu);
    
    keypad(win, TRUE);
    curs_set(0);

    start_color();
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    wattron(win, COLOR_PAIR(2));

    wborder(win, '*','*','*','*','*','*','*','*');
    
    //attroff(COLOR_PAIR(0));

    init_main_menu(win, main_menu);

    //make_vertical_line(win, 10, 0, LINES - 1, '*');
    curs_set(1);
    wmove(win, main_menu->entries[0].second, 10);
    //refresh();
    wrefresh(win);
    

    while(1)
    {
        int key = wgetch(win);

        if(key == 'q') break;

        switch(key)
        {
            case KEY_UP :
                if(main_menu->curs_position - 1 >= 0) main_menu->curs_position = main_menu->curs_position - 1;
                    
                break;

            case KEY_DOWN :
                if(main_menu->curs_position + 1 < main_menu->num_menu_entries) main_menu->curs_position = main_menu->curs_position + 1;
                //wprintw(win, "%d\n", main_menu->curs_position);
                break;

            default :
                break;
        }

        wmove(win, main_menu->entries[main_menu->curs_position].second, 10);
        //refresh();
        //wrefresh(win);
    }

    delwin(win);
    endwin();

    return 0;
}