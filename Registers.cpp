#include <cstdint>
#include "Registers.h"

	Registers::Registers() {
		for (int x = 0; x < sizeof(regsisters) / sizeof(uint32_t); x++) {
			regsisters[x] = 0;
		}
	}

	uint32_t Registers::getAcc() {
		return regsisters[14];
	}

	uint32_t Registers::get0Reg() {
		return regsisters[12];
	}

	uint32_t Registers::getPC() {
		return regsisters[15];
	}

	uint32_t Registers::getIR() {
		return regsisters[13];
	}

	uint32_t Registers::getGenReg(int index) {
		return regsisters[index];
	}

	void Registers::setPC(uint32_t x) {
		regsisters[15] = x;
	}

	void Registers::setIR(uint32_t x) {
		regsisters[13] = x;
	}

	void Registers::setAcc(uint32_t x) {
		regsisters[14] = x;
	}

	void Registers::setGenReg(uint32_t x, int index) {
		if ((index < 12) && (index >= 0)) {
			regsisters[index] = x;
		}
	}
