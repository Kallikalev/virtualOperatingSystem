//
// Created by Kalev Martinson on 10/24/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_LOADER_H
#define VIRTUALOPERATINGSYSTEM_LOADER_H


#include "Memory.h"
#include <string>
#include "PCB.h"
#include <list>

class Loader {
public:
    static void load(const std::string& programFile, Memory* disk, std::list<PCB> *pcbList);
};


#endif //VIRTUALOPERATINGSYSTEM_LOADER_H
