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

    bool _loadObjects_(const std::istream& objectsList);

    /**
     *
     * @return unsigned - Number of new generated objects
     */
    unsigned _generateNewObjects_();

    /**
     * @param unsigned - number of pixels to move all objects
     * @return unsigned - number of objects disappeared
     */
    unsigned _moveObjects_(unsigned nPixels = 1, Direction direction = right);
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
