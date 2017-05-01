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
         * @param objectsList
         *      Istream, which contains names of files with
         *      ASCII objects representations.
         *
         * @return
         *      True on success.
         */
        bool _loadObjects_(std::istream &objectsList);

        /**
         *
         * @return unsigned - Number of new generated objects
         */
        unsigned _generateNewObstacles_();

        /**
         *
         * @param nSymbols
         * @param direction
         * @return
         */
        unsigned _moveObstacles_(unsigned nSymbols = 1,
                                 Direction direction = right);

        /**
         *
         * @return
         */
        bool _clearObjectsFromScreen_() {
            std::for_each(m_field.objects.begin(), m_field.objects.end(),
                          [](IObjectPtr objectPtr) { objectPtr->eraseFigure(); });
            return true;
        }

        /**
         *
         * @return
         */
        bool _drawObjectsOnScreen_();

        /**
         *
         * @return
         */
        unsigned int _removeOutOfScreenObjects_();

    private:
        class GameField {
        public:
            bool addObject(IObjectPtr);

        public:
            std::list<IObjectPtr> objects;
            unsigned xMax, yMax;
        };

        GameField m_field;
        unsigned m_rocketFPS;
        unsigned m_obstaclesFPS;

        ObjectsStorage m_ASCIIObstacles;

    };

};

using namespace game;

#endif //GAME_GAME_H
