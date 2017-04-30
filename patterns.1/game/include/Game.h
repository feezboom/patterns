//
// Created by avk on 30.04.17.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <ncurses.h>
#include <unordered_set>
#include <IObject.h>

class Game {
public:
    Game();
    bool startGame();
    ~Game();
private:

    bool updateScreenSizes();

    /**
     * @param unsigned - number of pixels to move all objects
     * @return unsigned - number of objects disappeared
     */
    unsigned moveObjects(unsigned nPixels = 1, Direction direction = right);
private:
    class GameField {
    public:
        std::unordered_set<IObjectPtr> m_objects;
        unsigned xMax, yMax;
    };

    GameField m_field;
    unsigned m_fps;
};



#endif //GAME_GAME_H
