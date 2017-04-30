//
// Created by avk on 30.04.17.
//
#include <ctime>
#include <cstdlib>

#include <ObjectFactory.h>

#include "ObjectImpl.h"

IObjectPtr ObjectFactory::createObject(const std::istream &) {
    // Todo : implement some shit here.
    return IObjectPtr();
}

IObjectPtr ObjectFactory::createObject(const std::string &) {
    // Todo : and here.
    return IObjectPtr();
}

IObjectPtr ObjectFactory::createObject(const std::vector<std::string> &) {
    // Todo : and do not forget about this one here.
    return IObjectPtr();
}

IObjectPtr ObjectFactory::createRandom(const std::vector<std::string> &names,
                                       const ObjectsRepresentations &asciiRepresentations) {
    srand(static_cast<unsigned>(time(0)));
    unsigned chose = rand() % asciiRepresentations.size();

    ObjectRepresentation& chosenObject = asciiRepresentations[chose];


    return IObjectPtr();
}
