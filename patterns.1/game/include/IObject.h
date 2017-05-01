//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <Direction.h>
#include <memory>

class IObject {
public:
    virtual bool drawFigure() = 0;
    virtual bool eraseFigure() = 0;
    virtual bool move(unsigned nSymbols, Direction direction) = 0;
    virtual bool setPos(unsigned y, unsigned x) = 0;
    inline virtual ~IObject() {};
};

typedef std::shared_ptr<IObject> IObjectPtr;

#endif //GAME_OBJECT_H
