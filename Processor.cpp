//
// Created by Kalev Martinson on 9/15/23.
//

#include "Processor.h"
#include "utils.cpp"
#include <iostream>

Processor::Processor(Memory *ramPtr) {
    ram = ramPtr;
    pageTable = std::vector<uint32_t>();
}

void Processor::setRegisters(Registers &regs) {
    registers.copy(regs);
}

void Processor::setPageTable(std::vector<uint32_t> &pageTableRef) {
    pageTable = pageTableRef;
}

Registers &Processor::getRegisters() {
    return registers;
}

bool Processor::computeCycle() {
    uint32_t instruction = ram->get(Memory::depageAddress(pageTable, registers.getPC()));
    uint32_t type = utils::getBits(instruction, 30, 31);
    uint32_t opcode = utils::getBits(instruction, 24, 29);
    std::vector<uint32_t> args;
    switch (type) {
        case 0x00: {
            getArithmeticArgs(instruction, args);
            break;
        }
        case 0x01: {
            getConditionalArgs(instruction, args);
            break;
        }
        case 0x02: {
            getUnconditionalArgs(instruction, args);
            break;
        }
        case 0x03: {
            getIOArgs(instruction, args);
            break;
        }
        default: {
            throw std::invalid_argument("Instruction type: " + std::to_string(type) + " does not exist");
        }
    }
    registers.setPC(registers.getPC() + 1);
    return execute(opcode, args);
}

void Processor::getArithmeticArgs(uint32_t instruction, std::vector<uint32_t> &args) {
    args.push_back(utils::getBits(instruction, 20, 23)); // source-register
    args.push_back(utils::getBits(instruction, 16, 19)); // source-register
    args.push_back(utils::getBits(instruction, 12, 15)); // destination-register
}

void Processor::getConditionalArgs(uint32_t instruction, std::vector<uint32_t> &args) {
    args.push_back(utils::getBits(instruction, 20, 23)); // base-register
    args.push_back(utils::getBits(instruction, 16, 19)); // destination-register
    args.push_back(utils::getBits(instruction, 0, 15)); // address/data
}

void Processor::getUnconditionalArgs(uint32_t instruction, std::vector<uint32_t> &args) {
    args.push_back(utils::getBits(instruction, 0, 23)); // address
}

void Processor::getIOArgs(uint32_t instruction, std::vector<uint32_t> &args) {
    args.push_back(utils::getBits(instruction, 20, 23)); // register 1
    args.push_back(utils::getBits(instruction, 16, 19)); // register 2
    args.push_back(utils::getBits(instruction, 0, 15)); // address
}

bool Processor::execute(uint32_t opcode, std::vector<uint32_t> &args) {
    switch (opcode) {
        case 0x00: {
//            std::cout << "Executed instruction: RD" << std::endl;
            break;
        }
        case 0x01: {
//            std::cout << "Executed instruction: WR" << std::endl;
            break;
        }
        case 0x02: {
//            std::cout << "Executed instruction: ST" << std::endl;
            uint32_t addr = args[2];
            if (args[1] != 0) { // assume that we will never use register #0 aka accumulator as index
                addr = registers.getGenReg(args[1]);
            }

            ram->set(Memory::depageAddress(pageTable, addr), registers.getGenReg(args[0]));
            break;
        }
        case 0x03: {
//            std::cout << "Executed instruction: LW" << std::endl;
            uint32_t addr = args[2];
            if (args[1] != 0) { // assume that we will never use register #0 aka accumulator as index
                addr = registers.getGenReg(args[1]);
            }
            registers.setGenReg(args[0], ram->get(Memory::depageAddress(pageTable, addr)));
            break;
        }
        case 0x04: {
//            std::cout << "Executed instruction: MOV" << std::endl;
            registers.setGenReg(args[0],registers.getGenReg(args[1]));
            break;
        }
        case 0x05: {
//            std::cout << "Executed instruction: ADD" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) + registers.getGenReg(args[2]);
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x06: {
//            std::cout << "Executed instruction: SUB" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) - registers.getGenReg(args[2]);
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x07: {
//            std::cout << "Executed instruction: MUL" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) * registers.getGenReg(args[2]);
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x08: {
//            std::cout << "Executed instruction: DIV" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) / registers.getGenReg(args[2]);
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x09: {
//            std::cout << "Executed instruction: AND" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) & registers.getGenReg(args[2]);
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0A: {
//            std::cout << "Executed instruction: OR" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) | registers.getGenReg(args[2]);
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0B: {
//            std::cout << "Executed instruction: MOVI" << std::endl;
            registers.setGenReg(args[0],args[2]);
            break;
        }
        case 0x0C: {
//            std::cout << "Executed instruction: ADDI" << std::endl;
            uint32_t val = registers.getGenReg(args[0]) + args[2];
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0D: {
//            std::cout << "Executed instruction: MULI" << std::endl;
            uint32_t val = registers.getGenReg(args[0]) * args[2];
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0E: {
//            std::cout << "Executed instruction: DIVI" << std::endl;
            uint32_t val = registers.getGenReg(args[0]) / args[2];
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0F: {
//            std::cout << "Executed instruction: LDI" << std::endl;
            registers.setGenReg(args[0],args[2]);
            break;
        }
        case 0x10: {
//            std::cout << "Executed instruction: SLT" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) < registers.getGenReg(args[2]); // Boolean condition returns 0 or 1
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x11: {
//            std::cout << "Executed instruction: SLTI" << std::endl;
            uint32_t val = registers.getGenReg(args[1]) < args[2]; // Boolean condition returns 0 or 1
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x12: {
//            std::cout << "Executed instruction: HLT" << std::endl;
            free = true;
            return false;
        }
        case 0x13: {
//            std::cout << "Executed instruction: NOP" << std::endl;
            break;
        }
        case 0x14: {
//            std::cout << "Executed instruction: JMP" << std::endl;
            registers.setPC(args[0]);
            break;
        }
        case 0x15: {
//            std::cout << "Executed instruction: BEQ" << std::endl;
            if (registers.getGenReg(args[0]) == registers.getGenReg(args[1])) {
                registers.setPC(args[2]);
            }
            break;
        }
        case 0x16: {
//            std::cout << "Executed instruction: BNE" << std::endl;
            if (registers.getGenReg(args[0]) != registers.getGenReg(args[1])) {
                registers.setPC(args[2]);
            }
            break;
        }
        case 0x17: {
//            std::cout << "Executed instruction: BEZ" << std::endl;
            if (registers.getGenReg(args[0]) == 0) {
                registers.setPC(args[2]);
            }
            break;
        }
        case 0x18: {
//            std::cout << "Executed instruction: BNZ" << std::endl;
            if (registers.getGenReg(args[0]) != 0) {
                registers.setPC(args[2]);
            }
            break;
        }
        case 0x19: {
//            std::cout << "Executed instruction: BGZ" << std::endl;
            if (registers.getGenReg(args[0]) > 0) {
                registers.setPC(args[2]);
            }
            break;
        }
        case 0x1A: {
//            std::cout << "Executed instruction: BLZ" << std::endl;
            if (registers.getGenReg(args[0]) < 0) {
                registers.setPC(args[2]);
            }
            break;
        }
        default: {
            throw std::invalid_argument("Opcode: " + std::to_string(opcode) + " does not exist");
        }
    }
    return true;
}
