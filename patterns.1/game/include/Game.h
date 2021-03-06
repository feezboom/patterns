//
// Created by avk on 30.04.17.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <list>

#include <ncurses.h>
#include <algorithm>

#include <IObject.h>
#include <context.h>

namespace game {

    class Game {
    public:
        /**
         *
         */
        Game();

        /**
         * @brief
         *      Runs infinite loop.
         * @return
         */
        bool startGame();

        /**
         * @brief
         *      Calls endwin() from ncurses to release all captured sources.
         */
        ~Game();

    private:

        /**
         *
         * @return
         */
        bool _updateScreenSizes_();


        /**
         * @brief
         *      Loads list of objects from objectList
         *      inside itself.
         * @param file
         *      Istream, which contains names of files with
         *      ASCII objects representations.
         *
         * @return
         *      True on success.
         */
        bool _loadObjects_(const std::string &file);

        /**
         *
         * @return ShiftType - Number of new generated objects
         */
        ShiftType _generateNewObstacles_(ShiftType maxObjects);

        /**
         *
         * @param nSymbols
         * @param direction
         * @return
         */
        unsigned int _moveObstacles_(ShiftType nSymbols = 1,
                                     Direction direction = left);

        unsigned _moveBulletsAndCheckCollisions_(ShiftType nSymbols = 1,
                                                  Direction direction = right);

        bool _moveRocket_(Direction direction);

        bool _generateBullet_(const Point& position);

        /**
         *
         * @return
         */
        bool _clearAllObjectsFromScreen_() {
            for (auto& iObstaclePtr : m_field.obstacles) {
                iObstaclePtr->eraseFigure();
            }
            for (auto& iBulletPtr : m_field.bullets) {
                iBulletPtr->eraseFigure();
            }
            m_field.rocket->eraseFigure();
            return true;
        }

        /**
         *
         * @return
         */
        bool _drawObjectsByType_(ObjectType type);

        bool _drawAllObjects_() const;

        /**
         *
         * @return
         */
        unsigned long _removeOutOfScreenObjects_();

        unsigned _generateMoveObstacles_(bool generate, bool move, unsigned maxToGen);

        bool _isCollision_(IObjectPtr obj1, IObjectPtr obj2);

        friend class OutOfBoundsRemover;
        bool _isOutOfBounds_(IObjectPtr);

        /**
         *
         * @return
         */
        static bool _keyPressed_(void);

        void _printCurrentScore_();

        bool _checkLoose_() {
            if (loose) {
                mvprintw(m_field.yMax/2, m_field.xMax/2, "YOU LOSE");
                nodelay(stdscr, FALSE);
                while (getch() != 'q');
                return true;
            }
            return false;
        }

    private:
        class GameField {
        public:
            bool addObstacle(IObjectPtr);
            bool addBullet(IObjectPtr);
        public:
            std::list<IObjectPtr> obstacles;
            std::list<IObjectPtr> bullets;
            IObjectPtr rocket;
            ShiftType xMax, yMax;
        };

        GameField m_field;
        unsigned m_rocketFPS;
        unsigned m_obstaclesFPS;

        ObjectsStorage m_ASCIIObstacles;
        ObjectASCII m_ASCIIBullet;
        ObjectASCII m_ASCIIRocket;

        unsigned long m_currentScore;
        ShiftType m_scoreXPos, m_scoreYPos;

        bool loose;

    };

};

using namespace game;

#endif //GAME_GAME_H
