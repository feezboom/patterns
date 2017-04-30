//
// Created by avk on 30.04.17.
//

#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <string>
#include <vector>

#define MAX_OBJECT_NAME_LENGTH 128
#define MAX_FILE_NAME 128
#define MAX_OBJECT_LINE_LENGHT 10

typedef std::vector<std::string> ObjectRepresentation;
typedef std::vector<ObjectRepresentation> ObjectsRepresentations;
typedef std::string ObjectName;
typedef unsigned ObjectShift;

#endif //GAME_CONTEXT_H
