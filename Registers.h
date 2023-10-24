#pragma once
#ifndef REGISTERS_H
#define REGISTERS_H

#include <cstdint>

class Registers {
public:
	explicit Registers();
	uint32_t getGenReg(int index);
	uint32_t getAcc();
	uint32_t get0Reg();
	uint32_t getPC();
	uint32_t getIR();
	void setPC(uint32_t x);
	void setIR(uint32_t x);
	void setAcc(uint32_t x);
	void setGenReg(uint32_t x, int index);
private:
	uint32_t registers[16]{};
};

#endif