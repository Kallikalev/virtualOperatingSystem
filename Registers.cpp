#include <cstdint>
#include "Registers.h"

	Registers::Registers() {
		for (int x = 0; x < sizeof(registers) / sizeof(uint32_t); x++) {
            registers[x] = 0;
		}
	}

	uint32_t Registers::getAcc() {
		return registers[14];
	}

	uint32_t Registers::get0Reg() {
		return registers[12];
	}

	uint32_t Registers::getPC() {
		return registers[15];
	}

	uint32_t Registers::getIR() {
		return registers[13];
	}

	uint32_t Registers::getGenReg(int index) {
		return registers[index];
	}

	void Registers::setPC(uint32_t x) {
        registers[15] = x;
	}

	void Registers::setIR(uint32_t x) {
        registers[13] = x;
	}

	void Registers::setAcc(uint32_t x) {
        registers[14] = x;
	}

	void Registers::setGenReg(uint32_t x, int index) {
		if ((index < 12) && (index >= 0)) {
            registers[index] = x;
		}
	}
