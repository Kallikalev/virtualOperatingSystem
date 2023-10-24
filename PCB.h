//
// Created by Kalev Martinson on 10/24/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_PCB_H
#define VIRTUALOPERATINGSYSTEM_PCB_H


#include <cstdint>
#include "Registers.h"

struct PCB {
    uint32_t processId{};
    uint32_t programSize{};
    Registers registers;
    uint32_t priority{};
    uint32_t diskAddress{};
};


#endif //VIRTUALOPERATINGSYSTEM_PCB_H
