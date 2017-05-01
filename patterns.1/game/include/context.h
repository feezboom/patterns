//
// Created by avk on 30.04.17.
//

#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>

namespace game {

    #define KEYUP 65
    #define KEYDOWN 66
    #define KEYRIGHT 67
    #define KEYLEFT 68
    #define KEYFIRE ' '
    #define KEYPAUSE 'p'
    #define KEYCONTINUE 'c'
    #define KEYDEBUG 'd'

    // Todo : replace all unsigned with such shit:
    typedef int ShiftType;

    typedef std::vector<std::string> ObjectASCII;
    typedef std::string ObjectName;
    typedef std::vector<std::pair<ObjectName, ObjectASCII>> ObjectsStorage;
    typedef int ObjectShift;

#include <ncurses.h>
#define printstr(blo) \
    mvprintw(0,0,blo); \
    refresh(); \

#define printnum(blo) \
    mvprintw(0,0,std::to_string(blo).c_str()); \
    refresh(); \

#define printstry(y, blo) \
    mvprintw(y, 0, blo); \
    refresh(); \

#define printnumy(y, blo) \
    mvprintw(y,0,std::to_string(blo).c_str()); \
    refresh(); \

#define printstrnumxy(y, x, str, num) \
    mvprintw(y,x,(str + std::to_string(num)).c_str()); \
//    refresh(); \

}

#endif //GAME_CONTEXT_H
