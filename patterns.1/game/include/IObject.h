//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <memory>

#include <Point.h>
#include <Direction.h>

namespace game {

    class IObject {
    public:

        /**
         *
         * @return
         */
        virtual bool drawFigure() = 0;

        /**
         *
         * @return
         */
        virtual bool eraseFigure() = 0;

        /**
         *
         * @param nSymbols
         * @param direction
         * @return
         */
        virtual bool move(unsigned nSymbols, Direction direction) = 0;

        /**
         *
         * @return
         */
        virtual Point getPos() = 0;

        /**
         *
         * @param y
         * @param x
         * @return
         */
        virtual bool setPos(unsigned y, unsigned x) = 0;

        /**
         *
         */
        inline virtual ~IObject() {};
    };

    typedef std::shared_ptr<IObject> IObjectPtr;

};

#endif //GAME_OBJECT_H
