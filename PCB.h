//
// Created by Kalev Martinson on 10/24/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_PCB_H
#define VIRTUALOPERATINGSYSTEM_PCB_H


#include <cstdint>
#include "Registers.h"

struct PCB {
    PCB() = default;

    PCB(uint32_t processId, uint32_t size, Registers registers, uint32_t priority, uint32_t diskAddress) : processId(processId), size(size), registers(registers), priority(priority), diskAddress(diskAddress) {}

    uint32_t processId{};
    uint32_t size{};
    Registers registers;
    uint32_t priority{};
    uint32_t diskAddress{};
    uint32_t ramAddress{};
};

#endif //VIRTUALOPERATINGSYSTEM_PCB_H
