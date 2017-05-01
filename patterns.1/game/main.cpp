#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <Game.h>

#define DELAY 30000

int main() {
    game::Game game;
    game.startGame();

}

//int keyPressed(void)
//{
//    int ch = getch();
//
//    if (ch != ERR) {
//        ungetch(ch);
//        return 1;
//    } else {
//        return 0;
//    }
//}
//
//int main(void)
//{
//    initscr();
//
//    cbreak();
//    noecho();
//    nodelay(stdscr, TRUE);
//
//    scrollok(stdscr, TRUE);
//    while (1) {
//        if (keyPressed()) {
//            printw("Key pressed! It was: %d\n", getch());
//            refresh();
//        } else {
//            printw("No key pressed yet...\n");
//            refresh();
//            sleep(1);
//        }
//    }
//}