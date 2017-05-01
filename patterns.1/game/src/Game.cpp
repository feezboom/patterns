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

namespace game {

using std::for_each;

Game::Game() {
    initscr();
    noecho();
    curs_set(FALSE);
    _updateScreenSizes_();
}

bool Game::startGame() {
    unsigned rocketUpdateDelay = static_cast<unsigned>(1. / m_rocketFPS);
    unsigned obstaclesUpdateDelay = static_cast<unsigned>(1. / m_obstaclesFPS);

    // Obviously ( rocketUpdateDelay << obstaclesUpdateDelay )

    while (usleep(rocketUpdateDelay) == 0 /* delay succeeded */ ) {
//      1) Capture user's pressed button and then update rocket position.
//      1') Capture if user pressed shoot button. If so, do a shot.
//      2) Create new obstacles.
//      3) Move all obstacles.
//      4) Update newly generated obstacles on the screen.

        // Update rocket

        // OnShotButtonPressed - bullets : create new & update old ones

        // Update obstacles
        _clearObjectsFromScreen_();
        _removeOutOfScreenObjects_();
        _generateNewObstacles_();
        _moveObstacles_();
        _drawObjectsOnScreen_();
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

unsigned Game::_moveObstacles_(unsigned int nSymbols, Direction direction) {
    for_each(m_field.objects.begin(),
             m_field.objects.end(), [=](IObjectPtr objectPtr) {
                if (objectPtr->getType() == ObjectType::eObstacle) {
                    objectPtr->move(nSymbols, direction);
                }
            });
    return 0;
}

unsigned Game::_generateNewObstacles_() {
    // initialize random seed:
    srand(static_cast<unsigned>(time(0)));

    // Generate number of obstacles to generate.
    unsigned obstaclesToGenerate = static_cast<unsigned>(rand()) % 3;

    for (unsigned i = 0; i < obstaclesToGenerate; ++i) {
        // Generate random object from storage
        IObjectPtr generated = ObjectFactory::createRandom(m_ASCIIObstacles);

        // Generate random position for it.
        srand(static_cast<unsigned>(time(0)));
        unsigned yPos = rand() % m_field.yMax, xPos{0};
        generated->setPos(yPos, xPos);
        generated->setType(ObjectType::eObstacle);

        // Add recently generated object on the field.
        m_field.addObject(generated);
    }

    return obstaclesToGenerate;
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

        m_ASCIIObstacles.push_back(std::make_pair(fileName, currentObject));
    }


    return true;
}

bool Game::_drawObjectsOnScreen_() {
    for_each(m_field.objects.begin(),
             m_field.objects.end(), [](IObjectPtr objectPtr) {
                objectPtr->eraseFigure();
            });
    return true;
}

unsigned int Game::_removeOutOfScreenObjects_() {
    unsigned removedCount{0};

    // Iterating over objects which exist in the m_field.
    for (auto i = m_field.objects.begin();
         i != m_field.objects.end(); ++i) {

        // If object is out of bounds then erase it.
        if ((*i)->getPos().x > m_field.xMax) {
            m_field.objects.erase(i++);
            removedCount++;
        }
    }
    return removedCount;
}

bool Game::GameField::addObject(IObjectPtr objectPtr) {
    objects.insert(objects.begin(), objectPtr);
    return true;
}

}
