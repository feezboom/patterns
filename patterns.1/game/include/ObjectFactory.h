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
    typedef std::vector<ObjectRepresentation> ObjectsRepresentations;
public:
    static IObjectPtr createObject(const std::istream&);
    static IObjectPtr createObject(const std::string&);
    static IObjectPtr createObject(const std::vector<std::string>&);

    /**
     * @brief
     *      Creates random object from given list of objects
     * @param names
     * @param asciiRepresentations
     * @param max_yShift - max y shift for object to generate. (pixels number)
     * @return IObjectPtr - pointer to just created object
     */
    static IObjectPtr createRandom(const std::vector<ObjectName>& names,
                                   const ObjectsRepresentations& asciiReprs,
                                   unsigned max_yShift);

};


#endif //GAME_OBJECTFACTORY_H
