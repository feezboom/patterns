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
#include <iostream>

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

unsigned Game::_moveObjects_(unsigned int nSymbols, Direction direction) {
    for_each(m_field.m_objects.begin(),
             m_field.m_objects.end(), [=](IObjectPtr object) {
        object->move(nSymbols, direction);
    });
    return 0;
}

unsigned Game::_generateNewObjects_() {
    /* initialize random seed: */
    srand(static_cast<unsigned>(time(0)));

    // Generate number of objects to generate.
    unsigned objectsToGenerate = static_cast<unsigned>(rand()) % 3;

    for (unsigned i = 0; i < objectsToGenerate; ++i) {
        IObjectPtr generated = ObjectFactory::createRandom(m_existentObjects);

    }

    return objectsToGenerate;
}

bool Game::_loadObjects_(std::istream &objectsList) {

    while (!objectsList.eof()) {
        std::string fileName;
        ObjectASCII currentObject;

        // Read object representation from current file
        objectsList >> fileName;
        std::ifstream currentFileStream(fileName, std::ios_base::in);

        if (!currentFileStream) {
            std::cerr << "Error while reading \"" << fileName
                      << "\". Check if it exists." << std::endl;
            continue;
        }

        // Filling ObjectASCII
        while (!currentFileStream.eof()) {
            char line[OBJECT_MAX_LINE_LENGHT];
            currentFileStream.getline(line, OBJECT_MAX_LINE_LENGHT);
            currentObject.push_back(std::string(line));
        }

        m_existentObjects.push_back(std::make_pair(fileName, currentObject));
    }


    return true;
}

