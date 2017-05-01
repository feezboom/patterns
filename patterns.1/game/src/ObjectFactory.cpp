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

IObjectPtr ObjectFactory::createRandom(ObjectsStorage &asciiRepresentations) {
    srand(static_cast<unsigned>(time(0)));
    unsigned chose = rand() % (unsigned) asciiRepresentations.size();

    const ObjectName& chosenName = asciiRepresentations[chose].first;
    const ObjectASCII& chosenObject = asciiRepresentations[chose].second;
    IObjectPtr retVal = std::shared_ptr<Object>(new Object(chosenName, &chosenObject));

    return retVal;
}
