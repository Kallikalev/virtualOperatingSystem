//
// Created by Kalev Martinson on 9/15/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_PROCESSOR_H
#define VIRTUALOPERATINGSYSTEM_PROCESSOR_H

#include "Memory.h"
#include "Registers.h"

class Processor {
private:
    Memory* ram;
    Registers registers;
    std::vector<uint32_t> pageTable;

    static void getArithmeticArgs(uint32_t instruction, std::vector<uint32_t> &args);
    static void getConditionalArgs(uint32_t instruction, std::vector<uint32_t> &args);
    static void getUnconditionalArgs(uint32_t instruction, std::vector<uint32_t> &args);
    static void getIOArgs(uint32_t instruction, std::vector<uint32_t> &args);

    bool execute(uint32_t opcode, std::vector<uint32_t> &args);

public:
    explicit Processor(Memory* ramPtr);
    bool computeCycle();
    Registers& getRegisters();
    void setRegisters(Registers& regs);
    void setPageTable(std::vector<uint32_t> &pageTableRef);
};


#endif //VIRTUALOPERATINGSYSTEM_PROCESSOR_H
