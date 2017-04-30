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

IObjectPtr ObjectFactory::createRandom(const std::vector<ObjectName> &names,
                                       const ObjectsRepresentations &asciiRepresentations,
                                       unsigned max_yShift) {
    srand(static_cast<unsigned>(time(0)));
    unsigned chose = rand() % (unsigned) asciiRepresentations.size();
    unsigned y_shift = rand() % max_yShift;

    const ObjectName& name = names[chose];
    const ObjectRepresentation& chosenObject = asciiRepresentations[chose];
    IObjectPtr retVal = std::shared_ptr<Object>(new Object(name, &chosenObject, y_shift, 0));

    return IObjectPtr();
}
