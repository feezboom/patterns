//
// Created by avk on 30.04.17.
//

#include <unistd.h>
#include <cassert>
#include <ctime>
#include <cstdlib>

#include <algorithm>
#include <Game.h>
#include <ObjectFactory.h>

using std::for_each;

Game::Game() {
    initscr();
    noecho();
    curs_set(FALSE);
    _updateScreenSizes_();
}

bool Game::startGame() {
    unsigned updateDelay = static_cast<unsigned>(1./m_fps);
    while (usleep(updateDelay) == 0/*succeeded*/) {
        _generateNewObjects_();
        _moveObjects_();
//        updateField();
//        drawField();
    }
    return true;
}

Game::~Game() {
    endwin();
}

bool Game::_updateScreenSizes_() {
    getmaxyx(stdscr, m_field.yMax, m_field.xMax);
    return true;
}

unsigned Game::_moveObjects_(unsigned int nPixels, Direction direction) {
    for_each(m_field.m_objects.begin(),
             m_field.m_objects.end(), [nPixels, direction](IObjectPtr object) {
        object->move(nPixels, direction);
    });
    return 0;
}

unsigned Game::_generateNewObjects_() {
    int iSecret, iGuess;

    /* initialize random seed: */
    srand(static_cast<unsigned>(time(0)));

    // Generate number of objects
    int objectsToGenerate = rand() % 3;

    for (unsigned i = 0; i < objectsToGenerate; ++i) {
        IObjectPtr generated = ObjectFactory::createRandom();
    }

    puts ("Congratulations!");
    return 0;
}

bool Game::_loadObjects_(const std::istream &objectsList) {

    objectsList.getline()
    return false;
}

