//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <memory>

#include <Point.h>
#include <Direction.h>
#include "context.h"

namespace game {

    enum ObjectType {
        eObstacle,
        eBullet,
        eRocket,
        eUndefined,
    };

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
        virtual bool move(ShiftType nSymbols, Direction direction) = 0;

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
        virtual bool setPos(ShiftType y, ShiftType x) = 0;

        /**
         *
         * @return
         */
        virtual ObjectType getType() const = 0;

        /**
         *
         * @return
         */
        virtual bool setType(ObjectType) = 0;

        /**
         *
         */
        inline virtual ~IObject() {};
    };

    typedef std::shared_ptr<IObject> IObjectPtr;


};

#endif //GAME_OBJECT_H
