#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <Game.h>

#define DELAY 30000

//int main() {
////    int x = 0, y = 0;
////    int max_y = 0, max_x = 0;
////    int next_x = 0;
////    int direction = 1;
////
////    initscr();
////    noecho();
////    curs_set(FALSE);
////
////    // Global var `stdscr` is created by the call to `initscr()`
////    getmaxyx(stdscr, max_y, max_x);
////
////    while(1) {
////        clear();
////        mvprintw(y, x, "o");
////        refresh();
////
////        usleep(DELAY);
////
////        next_x = x + direction;
////
////        if (next_x >= max_x || next_x < 0) {
////            direction*= -1;
////        } else {
////            x+= direction;
////        }
////    }
////
////    endwin();
//
//    game::Game game;
//    game.startGame();
//
//
//
//}
//
int keyPressed(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main(void)
{
    initscr();

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    scrollok(stdscr, TRUE);
    while (1) {
        if (keyPressed()) {
            printw("Key pressed! It was: %d\n", getch());
            refresh();
        } else {
            printw("No key pressed yet...\n");
            refresh();
            sleep(1);
        }
    }
}