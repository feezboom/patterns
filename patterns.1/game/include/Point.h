//
// Created by avk on 01.05.17.
//

#ifndef GAME_POIN_H
#define GAME_POIN_H

#include <context.h>

namespace game {

    class Point {
    public:
        Point(ShiftType, ShiftType);
        ShiftType x, y;
    };

}

#endif //GAME_POIN_H
