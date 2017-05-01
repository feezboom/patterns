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

Game::Game() : m_rocketFPS(2000), m_obstaclesFPS(5) {
    initscr();
    noecho(); // Character is not printed if pressed
    nodelay(stdscr, TRUE);
    curs_set(0); // Makes cursor invisible

    // Create obstacles from files.
    _loadObjects_("../resources/obstacles_list.txt");

    // Create rocket from file.
    std::ifstream rocketStream("../resources/rocket", std::ios_base::in);
    m_ASCIIRocket = ObjectFactory::loadObject(rocketStream);
    IObjectPtr rocketPtr = ObjectFactory::createObject("rocket", m_ASCIIRocket);
    m_field.rocket = rocketPtr;
    rocketPtr->drawFigure();
    rocketStream.close();

    // Create bullet from file.
    std::ifstream bulletStream("../resources/bullet", std::ios_base::in);
    m_ASCIIBullet = ObjectFactory::loadObject(bulletStream);

    _updateScreenSizes_();
}

bool Game::startGame() {
    unsigned rocketUpdateDelay = static_cast<unsigned>((10e6 / m_rocketFPS));
    unsigned obstaclesUpdateDelay = static_cast<unsigned>((10e6 / m_obstaclesFPS));

    // Obviously ( rocketUpdateDelay << obstaclesUpdateDelay )
    unsigned counter{0};

    std::cout << "\r" << rocketUpdateDelay << std::flush;

    while (usleep(rocketUpdateDelay) == 0 /* delay succeeded */ ) {
//      1) Capture user's pressed button and then update rocket position.
//      1') Capture if user pressed shoot button. If so, do a shot.
//      2) Create new obstacles.
//      3) Move all obstacles.
//      4) Update newly generated obstacles on the screen.

        _clearObjectsFromScreen_();
        _removeOutOfScreenObjects_();

        // OnUserPressedButton.
        if (_keyPressed_()) {
            int c = getch();
            switch (c) {
                case KEYUP: {
                    _moveDrawRocket_(Direction::up);
                    break;
                }
                case KEYDOWN: {
                    _moveDrawRocket_(Direction::down);
                    break;
                }
//                case KEYFIRE: {
//                    _generateBullet_(m_field.rocket->getPos());
//                    break;
//                }
                default: {
                    break;
                }
            }
        }

//        // Update bullets
//        _moveBullets_(1, Direction::right);
//
//        // Update obstacles
//        _generateNewObstacles_();
//        _moveObstacles_(1, Direction::left);
//
//        _drawAllObjects_();

        std::cout << "\r" << counter++ << std::flush;
        if (counter > 1000000) {
            break;
        }
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
    unsigned counter{0};
    for_each(m_field.objects.begin(),
             m_field.objects.end(), [&](IObjectPtr objectPtr) {
                if (objectPtr->getType() == ObjectType::eObstacle) {
                    objectPtr->move(nSymbols, direction);
                    counter++;
                }
            });
    return counter;
}

unsigned Game::_moveBullets_(unsigned int nSymbols, Direction direction) {
    unsigned counter{0};
    for_each(m_field.objects.begin(),
             m_field.objects.end(), [&](IObjectPtr objectPtr) {
                if (objectPtr->getType() == ObjectType::eBullet) {
                    objectPtr->move(nSymbols, direction);
                    counter++;
                }
            });
    return counter;
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
        ObjectASCII currentObject = ObjectFactory::loadObject(currentFileStream);
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

bool Game::_keyPressed_(void) {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return true;
    } else {
        return false;
    }
}

bool Game::_moveDrawRocket_(Direction direction) {
    m_field.rocket->eraseFigure();
    m_field.rocket->move(1, direction);
    m_field.rocket->drawFigure();
    return true;
}

bool Game::_generateBullet_(const Point& position) {
    IObjectPtr bulletPtr = ObjectFactory::createObject("bullet", m_ASCIIBullet);
    m_field.addObject(bulletPtr);
    return true;
}

bool Game::GameField::addObject(IObjectPtr objectPtr) {
    objects.insert(objects.begin(), objectPtr);
    return true;
}

}
