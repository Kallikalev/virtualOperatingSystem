//
// Created by Kalev Martinson on 10/30/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_CONTEXTSWITCHER_H
#define VIRTUALOPERATINGSYSTEM_CONTEXTSWITCHER_H


#include "Processor.h"
#include "PCB.h"
#include "Registers.h"

class ContextSwitcher {
public:
    static void switchOut(Processor& cpu, PCB& oldPCB);
    static void switchIn(Processor& cpu, PCB& newPCB);
};


#endif //VIRTUALOPERATINGSYSTEM_CONTEXTSWITCHER_H
