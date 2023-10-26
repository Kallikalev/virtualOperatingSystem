//
// Created by Kalev Martinson on 9/15/23.
//

#include "Processor.h"
#include "utils.cpp"
#include <iostream>

Processor::Processor(Memory *ramPtr) {
    ram = ramPtr;
}

bool Processor::computeCycle() {
    uint32_t instruction = ram->get(effectiveAddress(registers.getPC()));
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

uint32_t Processor::effectiveAddress(uint32_t addr) {
    return addr + registers.getIR();
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
            std::cout << "Executed instruction: RD" << std::endl;
            break;
        }
        case 0x01: {
            std::cout << "Executed instruction: WR" << std::endl;
            break;
        }
        case 0x02: {
            std::cout << "Executed instruction: ST" << std::endl;
            break;
        }
        case 0x03: {
            std::cout << "Executed instruction: LW" << std::endl;
            break;
        }
        case 0x04: {
            std::cout << "Executed instruction: MOV" << std::endl;
            break;
        }
        case 0x05: {
            std::cout << "Executed instruction: ADD" << std::endl;
            // source registers are held in first two arguments
            uint32_t val = registers.getGenReg(args[0]) + registers.getGenReg(args[1]);
            registers.setGenReg(args[2], val); // destination register is held in argument 2
            break;
        }
        case 0x06: {
            std::cout << "Executed instruction: SUB" << std::endl;
            // source registers are held in first two arguments
            uint32_t val = registers.getGenReg(args[0]) - registers.getGenReg(args[1]);
            registers.setGenReg(args[2], val); // destination register is held in argument 2
            break;
        }
        case 0x07: {
            std::cout << "Executed instruction: MUL" << std::endl;
            // source registers are held in first two arguments
            uint32_t val = registers.getGenReg(args[0]) * registers.getGenReg(args[1]);
            registers.setGenReg(args[2], val); // destination register is held in argument 2
            break;
        }
        case 0x08: {
            std::cout << "Executed instruction: DIV" << std::endl;
            // source registers are held in first two arguments
            uint32_t val = registers.getGenReg(args[0]) / registers.getGenReg(args[1]);
            registers.setGenReg(args[2], val); // destination register is held in argument 2
            break;
        }
        case 0x09: {
            std::cout << "Executed instruction: AND" << std::endl;
            // source registers are held in first two arguments
            uint32_t val = registers.getGenReg(args[0]) & registers.getGenReg(args[1]);
            registers.setGenReg(args[2], val); // destination register is held in argument 2
            break;
        }
        case 0x0A: {
            std::cout << "Executed instruction: OR" << std::endl;
            // source registers are held in first two arguments
            uint32_t val = registers.getGenReg(args[0]) | registers.getGenReg(args[1]);
            registers.setGenReg(args[2], val); // destination register is held in argument 2
            break;
        }
        case 0x0B: {
            std::cout << "Executed instruction: MOVI" << std::endl;
            // argument 0 is base register, argument 2 is data to be transferred, argument 1 is empty
            registers.setGenReg(args[0],args[2]);
            break;
        }
        case 0x0C: {
            std::cout << "Executed instruction: ADDI" << std::endl;
            // argument 0 is base register, argument 2 is data to be added, argument 1 is empty
            uint32_t val = registers.getGenReg(args[0]) + args[2];
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0D: {
            std::cout << "Executed instruction: MULI" << std::endl;
            // argument 0 is base register, argument 2 is data to be multiplied, argument 1 is empty
            uint32_t val = registers.getGenReg(args[0]) * args[2];
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0E: {
            std::cout << "Executed instruction: DIVI" << std::endl;
            // argument 0 is base register, argument 2 is data to be divided, argument 1 is empty
            uint32_t val = registers.getGenReg(args[0]) / args[2];
            registers.setGenReg(args[0], val);
            break;
        }
        case 0x0F: {
            std::cout << "Executed instruction: LDI" << std::endl;
            break;
        }
        case 0x10: {
            std::cout << "Executed instruction: SLT" << std::endl;
            uint32_t val = registers.getGenReg(args[0]) < registers.getGenReg(args[1]); // Boolean condition returns 0 or 1
            registers.setGenReg(args[2], val);
            break;
        }
        case 0x11: {
            std::cout << "Executed instruction: SLTI" << std::endl;
            uint32_t val = registers.getGenReg(args[0]) < args[2]; // Boolean condition returns 0 or 1
            registers.setGenReg(args[1], val);
            break;
        }
        case 0x12: {
            std::cout << "Executed instruction: HLT" << std::endl;
            return true;
        }
        case 0x13: {
            std::cout << "Executed instruction: NOP" << std::endl;
            break;
        }
        case 0x14: {
            std::cout << "Executed instruction: JMP" << std::endl;
            break;
        }
        case 0x15: {
            std::cout << "Executed instruction: BEQ" << std::endl;
            break;
        }
        case 0x16: {
            std::cout << "Executed instruction: BNE" << std::endl;
            break;
        }
        case 0x17: {
            std::cout << "Executed instruction: BEZ" << std::endl;
            break;
        }
        case 0x18: {
            std::cout << "Executed instruction: BNZ" << std::endl;
            break;
        }
        case 0x19: {
            std::cout << "Executed instruction: BGZ" << std::endl;
            break;
        }
        case 0x1A: {
            std::cout << "Executed instruction: BLZ" << std::endl;
            break;
        }
        default: {
            throw std::invalid_argument("Opcode: " + std::to_string(opcode) + " does not exist");
        }
    }
    return false;
}
