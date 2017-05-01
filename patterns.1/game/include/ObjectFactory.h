//
// Created by avk on 30.04.17.
//

#ifndef GAME_OBJECTFACTORY_H
#define GAME_OBJECTFACTORY_H


#include <vector>
#include <string>
#include <fstream>

#include <IObject.h>
#include <context.h>


class ObjectFactory {
public:
    static IObjectPtr createObject(const std::istream&);
    static IObjectPtr createObject(const std::string&);
    static IObjectPtr createObject(const std::vector<std::string>&);

    /**
     * @brief
     *      Creates random object from given list of objects
     * @param names -
     *      Vector of existent objects
     * @param asciiRepresentations -
     *      Vector of ascii representations of objects (vector<vector<string>>)
     * @return IObjectPtr -
     *      Shared_ptr to just created object
     */
    static IObjectPtr createRandom(ObjectsStorage& asciiReprs);

};


#endif //GAME_OBJECTFACTORY_H
