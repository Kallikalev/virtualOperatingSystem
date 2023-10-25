#pragma once
#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>

class Registers {
public:
	explicit Registers();
    Registers(Registers &other);
	uint32_t getGenReg(int index);
	uint32_t getAcc();
	uint32_t get0Reg();
	[[nodiscard]] uint32_t getPC() const;
	[[nodiscard]] uint32_t getIR() const;
	void setPC(uint32_t x);
	void setIR(uint32_t x);
	void setAcc(uint32_t x);
	void setGenReg(uint32_t x, int index);
private:
	uint32_t registers[16]{};
    uint32_t programCounter;
    uint32_t indexRegister;
};

#endif