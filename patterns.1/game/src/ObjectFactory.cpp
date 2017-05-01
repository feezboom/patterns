//
// Created by avk on 30.04.17.
//
#include <ctime>
#include <cstdlib>

#include <ObjectFactory.h>
#include <context.h>

#include "ObjectImpl.h"

namespace game {

IObjectPtr ObjectFactory::createObject(std::istream &objectStream) {
    ObjectASCII objectASCII = loadObject(objectStream);
    return IObjectPtr();
}

IObjectPtr ObjectFactory::createObject(const std::string &) {
    // Todo : and here.
    return IObjectPtr();
}

IObjectPtr ObjectFactory::createObject(const ObjectName& name, const ObjectASCII& objectASCII) {
    IObjectPtr objectPtr = IObjectPtr(new Object(name, &objectASCII));
    return objectPtr;
}

IObjectPtr ObjectFactory::createRandom(ObjectsStorage &asciiObstacles) {

    unsigned chose = rand() % (unsigned) asciiObstacles.size();

    const ObjectName& chosenName = asciiObstacles[chose].first;
    const ObjectASCII& chosenObject = asciiObstacles[chose].second;
    IObjectPtr retVal = std::shared_ptr<Object>(new Object(chosenName, &chosenObject));

    return retVal;
}

    ObjectASCII ObjectFactory::loadObject(std::istream &objectStream) {
        ObjectASCII retVal;
        std::string line;
        while (!objectStream.eof()) {
            std::getline(objectStream, line);
            retVal.push_back(line);
        }
        return retVal;
    }

}
