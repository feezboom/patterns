//
// Created by avk on 30.04.17.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <vector>
#include <unordered_set>

#include <ncurses.h>

#include <IObject.h>
#include <context.h>

class Game {
public:
    Game();
    bool startGame();
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
    unsigned _generateNewObjects_();

    /**
     *
     * @param nSymbols
     * @param direction
     * @return
     */
    unsigned _moveObjects_(unsigned nSymbols = 1, Direction direction = right);
private:
    class GameField {
    public:
        std::unordered_set<IObjectPtr> m_objects;
        unsigned xMax, yMax;
    };

    GameField m_field;
    unsigned m_fps;

    ObjectsStorage m_existentObjects;

};



#endif //GAME_GAME_H
