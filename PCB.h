//
// Created by Kalev Martinson on 10/24/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_PCB_H
#define VIRTUALOPERATINGSYSTEM_PCB_H


#include <cstdint>
#include "Registers.h"

struct PCB {
    PCB(uint32_t newProcessId, uint32_t newSize, Registers newRegisters, uint32_t newPriority, uint32_t newDiskAddress) {
        processId = newProcessId;
        size = newSize;
        registers = newRegisters;
        priority = newPriority;
        diskAddress = newDiskAddress;
    }

    uint32_t processId{};
    uint32_t size{};
    Registers registers;
    uint32_t priority{};
    uint32_t diskAddress{};
};


#endif //VIRTUALOPERATINGSYSTEM_PCB_H
