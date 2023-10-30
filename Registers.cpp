#include <cstdint>
#include "Registers.h"

void Registers::copy(Registers &other) {
    for (int i = 0; i < sizeof(registers) / sizeof(uint32_t); i++) {
        registers[i] = other.getGenReg(i);
    }
    programCounter = other.getPC();
    indexRegister = other.getIR();
}

uint32_t Registers::getAcc() {
    return registers[0];
}

uint32_t Registers::get0Reg() {
    return registers[1];
}

uint32_t Registers::getPC() const {
    return programCounter;
}

uint32_t Registers::getIR() const {
    return indexRegister;
}

uint32_t Registers::getGenReg(uint32_t index) {
    return registers[index];
}

void Registers::setPC(uint32_t val) {
    programCounter = val;
}

void Registers::setIR(uint32_t val) {
    indexRegister = val;
}

void Registers::setAcc(uint32_t val) {
    registers[0] = val;
}

void Registers::setGenReg(uint32_t index, uint32_t val) {
    registers[index] = val;
}
