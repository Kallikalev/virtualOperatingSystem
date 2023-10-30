//
// Created by Kalev Martinson on 10/30/23.
//

#include "ContextSwitcher.h"

void ContextSwitcher::switchOut(Processor &cpu, PCB &oldPCB) {
    oldPCB.registers.copy(cpu.getRegisters());
}

void ContextSwitcher::switchIn(Processor &cpu, PCB &newPCB) {
    cpu.setRegisters(newPCB.registers);
}
