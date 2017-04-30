//
// Created by avk on 30.04.17.
//

// usleep
#include <unistd.h>
#include <algorithm>
#include <Game.h>

using std::for_each;

Game::Game() {
    initscr();
    noecho();
    curs_set(FALSE);
    updateScreenSizes();
}

bool Game::startGame() {
    unsigned updateDelay = static_cast<unsigned>(1./m_fps);
    while (usleep(updateDelay) == 0/*succeeded*/) {
//        generateNewObjects();
        moveObjects();
//        updateField();
//        drawField();
    }
    return true;
}

Game::~Game() {
    endwin();
}

bool Game::updateScreenSizes() {
    getmaxyx(stdscr, m_field.yMax, m_field.xMax);
    return true;
}

unsigned Game::moveObjects(unsigned int nPixels, Direction direction) {
    for_each(m_field.m_objects.begin(),
             m_field.m_objects.end(), [nPixels, direction](IObjectPtr object) {
        object->move(nPixels, direction);
    });
    return 0;
}

