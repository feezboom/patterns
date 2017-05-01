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
#include "ObjectImpl.h"

namespace game {

    using std::for_each;

    Game::Game() : m_rocketFPS(1500), m_obstaclesFPS(500) {
        initscr();
        noecho(); // Character is not printed if pressed
        nodelay(stdscr, TRUE);
        curs_set(0); // Makes cursor invisible

        srand(static_cast<unsigned>(time(0)));

        // Create obstacles from files.
        _loadObjects_("../resources/obstacles_list.txt");

        // Create rocket from file.
        std::ifstream rocketStream("../resources/rocket", std::ios_base::in);
        m_ASCIIRocket = ObjectFactory::loadObject(rocketStream);
        IObjectPtr rocketPtr = ObjectFactory::createObject("rocket", m_ASCIIRocket);
        m_field.rocket = rocketPtr;
        rocketStream.close();

        // Create bullet from file.
        std::ifstream bulletStream("../resources/bullet", std::ios_base::in);
        m_ASCIIBullet = ObjectFactory::loadObject(bulletStream);

        _updateScreenSizes_();
    }

    bool Game::startGame() {
        unsigned rocketUpdateDelay = static_cast<unsigned>((10e6 / m_rocketFPS));
        unsigned obstaclesUpdateDelay = static_cast<unsigned>((10e6 / m_obstaclesFPS));

        // Obviously ?? ( rocketUpdateDelay << obstaclesUpdateDelay )
        unsigned long counter{0};

//    std::cout << "\r" << rocketUpdateDelay << std::flush;

        while (usleep(rocketUpdateDelay) == 0 /* delay succeeded */ ) {
//      1) Capture user's pressed button and then update rocket position.
//      1') Capture if user pressed shoot button. If so, do a shot.
//      2) Create new obstacles.
//      3) Move all obstacles.
//      4) Update newly generated obstacles on the screen.

            _clearAllObjectsFromScreen_();
            _removeOutOfScreenObjects_();

            // OnUserPressedButton.
            if (_keyPressed_()) {
                int c = getch();
                switch (c) {
                    case KEYUP: {
                        _moveRocket_(Direction::up);
                        break;
                    }
                    case KEYDOWN: {
                        _moveRocket_(Direction::down);
                        break;
                    }
                    case KEYLEFT: {
                        _moveRocket_(Direction::left);
                        break;
                    }
                    case KEYRIGHT: {
                        _moveRocket_(Direction::right);
                        break;
                    }
                    case KEYFIRE: {
                        _generateBullet_(m_field.rocket->getPos());
                        break;
                    }
//                case KEYPAUSE: {
//                    nodelay(stdscr, FALSE);
//                    while (getch() != KEYCONTINUE);
//                    nodelay(stdscr, TRUE);
//                }
//                case KEYDEBUG: {
//                    nodelay(stdscr, FALSE);
//                    while ((c=getch()) != KEYDEBUG) {
//                        m_field.rocket->eraseFigure();
//
//                        if (c == KEYRIGHT) {
//                            m_field.rocket->move(1, right);
//                        } else if (c == KEYLEFT) {
//                            m_field.rocket->move(1, left);
//                        } else if (c == KEYUP) {
//                            m_field.rocket->move(1, up);
//                        } else if (c == KEYDOWN) {
//                            m_field.rocket->move(1, down);
//                        }
//
//                        if (c == 'q') {
//                            _drawAllObjects_();
//                            c = getch();
//                            if (c == 'w') {
//                                int x = m_field.xMax/2;
//                                int y = m_field.yMax/2;
//                                auto& p = m_field.objects.begin().operator*();
//                                std::shared_ptr<Object> pp = std::dynamic_pointer_cast<Object>(p);
//                                std::vector<std::string> q = *pp->m_signs;
//                                for (int i = 0; i < q.size(); ++i) {
//                                    mvprintw(y+i,x, q[i].c_str());
//                                }
//                            }
//                        }
//                        if (c == 'Q') {
//                            _clearObjectsFromScreen_();
//                        }
//
//
//                        if (c == 'o') {
//                            const IObjectPtr& o = m_field.objects.begin().operator*();
//                            while ((c=getch()) != 'o') {
//                                o->eraseFigure();
//                                if (c == KEYRIGHT) {
//                                    o->move(1, right);
//                                } else if (c == KEYLEFT) {
//                                    o->move(1, left);
//                                } else if (c == KEYUP) {
//                                    o->move(1, up);
//                                } else if (c == KEYDOWN) {
//                                    o->move(1, down);
//                                }
//                                o->drawFigure();
//                            }
//                        }
//                        m_field.rocket->drawFigure();
//
//                    }
//                    nodelay(stdscr, TRUE);
//                }
                    default: {
                        break;
                    }
                }
            }

            // Update bullets
            _moveBulletsAndCheckCollisions_(1, Direction::right);

            bool generateNew = (counter % (m_rocketFPS * 10 / m_obstaclesFPS) == 0);
            bool moveOldOnes = (counter % (m_rocketFPS / m_obstaclesFPS) == 0);
            _generateUpdateObstacles_(generateNew, moveOldOnes, 2);

            _drawAllObjects_();

            printstrnumxy(m_field.yMax - 1, 0, "Iteration: ", counter++)
            printstrnumxy(m_field.yMax - 1, 20, "Bullets count : ", m_field.bullets.size())
            printstrnumxy(m_field.yMax - 1, 120, "Obstacles count : ", m_field.obstacles.size())
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

    unsigned int Game::_moveObstacles_(ShiftType nSymbols, Direction direction) {
        unsigned counter{0};
        for (auto &iObstaclePtr : m_field.obstacles) {
            assert(iObstaclePtr->getType() == ObjectType::eObstacle);
            iObstaclePtr->move(nSymbols, direction);
            counter++;
        };
        return counter;
    }

    // TODO : remove after debug
    static int count{0};

    unsigned Game::_moveBulletsAndCheckCollisions_(ShiftType nSymbols, Direction direction) {
        unsigned counter{0};
        auto bulletIter = m_field.bullets.begin(),
                bulletEnd = m_field.bullets.end();
        auto obstacleIter = m_field.obstacles.begin(),
                obstacleEnd = m_field.obstacles.end();

        for (; bulletIter != bulletEnd; ++bulletIter) {
            IObjectPtr bullet = *bulletIter;
            bullet->move(nSymbols, direction);
//            while (_isOutOfBounds_(bullet)) {
//                bulletIter = m_field.bullets.erase(bulletIter);
//            }
            assert(bullet->getType() == ObjectType::eBullet);

            for (; obstacleIter != obstacleEnd; ++obstacleIter) {
                IObjectPtr obstacle = *obstacleIter;
                assert(obstacle->getType() == ObjectType::eObstacle);

                if (_isCollision_(bullet, obstacle)) {
                    obstacleIter = m_field.obstacles.erase(obstacleIter);
                    bulletIter = m_field.bullets.erase(bulletIter);
                    counter++; count++;
                }
            }
        }
//    printstrnumxy(m_field.yMax-1, 50, "moved bullets : ", count);

        return counter;
    }

    ShiftType Game::_generateNewObstacles_(ShiftType maxObjects) {
        // Generate number of obstacles to generate.
        ShiftType obstaclesToGenerate = static_cast<ShiftType>(rand()) % maxObjects;

        for (ShiftType i = 0; i < obstaclesToGenerate; ++i) {
            // Generate random object from storage
            IObjectPtr generated = ObjectFactory::createRandom(m_ASCIIObstacles);

            // Generate random position for it.
            ShiftType yPos = rand() % m_field.yMax, xPos{m_field.xMax - 8};
            generated->setPos(yPos, xPos);
            generated->setType(ObjectType::eObstacle);

            // Add recently generated object on the field.
            m_field.addObstacle(generated);
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
        for_each(m_field.obstacles.begin(),
                 m_field.obstacles.end(), [=](IObjectPtr objectPtr) {
                    if (objectPtr->getType() == type) {
                        objectPtr->drawFigure();
                    }
                });
        return true;
    }

    unsigned int Game::_removeOutOfScreenObjects_() {
        unsigned removedCount{0};

        auto outOfBoundsRemover = [this, &removedCount](auto iter, auto end) {
            for (; iter != end; ++iter) {
                ShiftType x_coord = (*iter)->getPos().x;
                if (x_coord > m_field.xMax || x_coord <= 0) {
                    iter = m_field.obstacles.erase(iter);
                    removedCount++;
                }
            }
        };

        // Iterating over objects which exist in the m_field.
        auto bulletIter = m_field.bullets.begin(),
                bulletEnd = m_field.bullets.end();
        auto obstacleIter = m_field.obstacles.begin(),
                obstacleEnd = m_field.obstacles.end();

        outOfBoundsRemover(bulletIter, bulletEnd);
        outOfBoundsRemover(obstacleIter, obstacleEnd);

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

    bool Game::_moveRocket_(Direction direction) {
        m_field.rocket->move(1, direction);
        return true;
    }

    // TODO :remove after debug
    static int anotherCounter{0};

    bool Game::_generateBullet_(const Point &position) {
        printstrnumxy(m_field.yMax - 1, 80, "I'm in generated bullet #", anotherCounter++);
        IObjectPtr bulletPtr = ObjectFactory::createObject("bullet", m_ASCIIBullet);

        Point pos = m_field.rocket->getPos();
        bulletPtr->setPos(pos.y + 2, pos.x + 1);
        bulletPtr->setType(ObjectType::eBullet);

        m_field.addBullet(bulletPtr);
        return true;
    }

    unsigned Game::_generateUpdateObstacles_(bool generate, bool move, unsigned maxToGen) {
        // Update obstacles
        if (generate) {
            _generateNewObstacles_(maxToGen);
        }
        if (move) {
            return _moveObstacles_(1, Direction::left);
        }
        return 0;
    }

    bool Game::_isCollision_(IObjectPtr obj1, IObjectPtr obj2) {
        const ObjectASCII *repr1 = obj1->getASCIIRepresentation(),
                *repr2 = obj2->getASCIIRepresentation();
        const Point pos1 = obj1->getPos(),
                pos2 = obj2->getPos();

        if (pos1.y + repr1->size() < pos2.y ||
            pos2.y + repr2->size() < pos1.y) {
            return false;
        }

        auto getObjectXLength = [](const ObjectASCII *o) {
            unsigned long max{0};
            for (const auto &line : *o) {
                if (line.size() > max) {
                    max = line.size();
                }
            }
            return max;
        };

        return !(pos1.x + getObjectXLength(repr1) < pos2.x ||
                 pos2.x + getObjectXLength(repr2) < pos1.x);

    }

    bool Game::_isOutOfBounds_(IObjectPtr obj) {
        ShiftType x_coord = obj->getPos().x;
        return x_coord > m_field.xMax || x_coord <= 0;
    }

    bool Game::GameField::addObstacle(IObjectPtr iObstaclePtr) {
        obstacles.push_back(iObstaclePtr);
        return true;
    }

    bool Game::GameField::addBullet(IObjectPtr iBulletPtr) {
        bullets.push_back(iBulletPtr);
        return true;
    }

}
