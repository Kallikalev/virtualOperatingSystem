#include <cstdint>
#include "Registers.h"

Registers::Registers() {
    programCounter = 0;
    indexRegister = 0;
}

Registers::Registers(Registers &other) {
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

uint32_t Registers::getGenReg(int index) {
    return registers[index];
}

void Registers::setPC(uint32_t x) {
    programCounter = x;
}

void Registers::setIR(uint32_t x) {
    indexRegister = x;
}

void Registers::setAcc(uint32_t x) {
    registers[0] = x;
}

void Registers::setGenReg(uint32_t x, int index) {
    registers[index] = x;
}