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

    #define MAX_OBJECT_NAME_LENGTH 128
    #define MAX_FILE_NAME 128
    #define OBJECT_MAX_LINE_LENGHT 10

    // Todo : replace all unsigned with such shit:
    typedef unsigned ShiftType;

    typedef std::vector<std::string> ObjectASCII;
    typedef std::string ObjectName;
    typedef std::vector<std::pair<ObjectName, ObjectASCII>> ObjectsStorage;
    typedef unsigned ObjectShift;

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

}

#endif //GAME_CONTEXT_H
