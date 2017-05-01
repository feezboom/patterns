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

Game::Game() : m_rocketFPS(100), m_obstaclesFPS(5) {
//    initscr();
//    noecho();
//    curs_set(FALSE);
    std::string file("../resources/obstacles_list.txt");
//    std::ifstream obstList(, std::ios_base::in);
//    assert(obstList);
    _loadObjects_(file);
    _updateScreenSizes_();
}


bool Game::startGame() {
    unsigned rocketUpdateDelay = static_cast<unsigned>((10e6 / m_rocketFPS));
    unsigned obstaclesUpdateDelay = static_cast<unsigned>((10e6 / m_obstaclesFPS));

    // Obviously ( rocketUpdateDelay << obstaclesUpdateDelay )
    unsigned counter{0};
//    printnum(m_field.xMax);
//    return false;

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
        _moveObstacles_(1, Direction::left);
        _drawObjectsByType_(eObstacle);
        std::cout << "\r" << counter++ << std::flush;
//        printnum(counter++);
        if (counter > 100) {
            break;
        }
    }
    return true;
}

Game::~Game() {
//    getch();
//    endwin();
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
        unsigned yPos = rand() % m_field.yMax, xPos{m_field.xMax};
        generated->setPos(yPos, xPos);
        generated->setType(ObjectType::eObstacle);

        // Add recently generated object on the field.
        m_field.addObject(generated);
    }

    return obstaclesToGenerate;
}

ObjectASCII Game::_loadObject_(std::istream &objectStream) const {
    ObjectASCII retVal;
    std::string line;
    while (!objectStream.eof()) {
        std::getline(objectStream, line);
        retVal.push_back(line);
    }
    return retVal;
}

bool Game::_loadObjects_(const std::string &file) {
    std::ifstream objList(file, std::ios_base::in);

    std::string fileName;
    std::ifstream currentFileStream;
    while (!objList.eof()) {

        // Read object representation from current file
        objList >> fileName;
        currentFileStream.open(fileName, std::ios_base::in);

        if (!currentFileStream) {
            std::cerr << "Error while reading \"" << fileName
                      << "\". Check if it exists." << std::endl;
            continue;
        }

        // Filling ObjectASCII
        ObjectASCII currentObject = _loadObject_(currentFileStream);
        m_ASCIIObstacles.push_back(std::make_pair(fileName, currentObject));
        currentFileStream.close();
    }


    return true;
}

bool Game::_drawObjectsByType_(ObjectType type) {
    for_each(m_field.objects.begin(),
             m_field.objects.end(), [=](IObjectPtr objectPtr) {
                if (objectPtr->getType() == type) {
                    objectPtr->drawFigure();
                }
            });
    return true;
}

unsigned int Game::_removeOutOfScreenObjects_() {
    unsigned removedCount{0};

    // Iterating over objects which exist in the m_field.
    for (auto i = m_field.objects.begin();
         i != m_field.objects.end(); ++i) {

        // If object is out of bounds then erase it.
        unsigned x_coord = (*i)->getPos().x;
        if (x_coord > m_field.xMax || x_coord < 0) {
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
