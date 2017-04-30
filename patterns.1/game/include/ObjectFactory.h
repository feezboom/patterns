//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECTFACTORY_H
#define GAME_OBJECTFACTORY_H


#include <vector>
#include <string>
#include <fstream>

#include <IObject.h>

#define MAX_OBJECT_NAME_LENGTH 1024

class ObjectFactory {
public:
    static IObjectPtr createObject(const std::istream&);
    static IObjectPtr createObject(const std::string&);
    static IObjectPtr createObject(const std::vector<std::string>&);

    /**
     * @brief
     *      Creates random object from given list of objects
     * @param names
     * @param asciiRepresentations
     * @return IObjectPtr - pointer to just created object
     */
    static IObjectPtr createRandom(const std::vector<std::string>& names,
                                   const ObjectsRepresentations& asciiRepresentations);

};


#endif //GAME_OBJECTFACTORY_H
