//
// Created by Kalev Martinson on 9/5/23.
//

#include <iostream>
#include "Memory.h"
#include "utils.cpp"

int main() {
    Memory ram(4);
    std::cout << std::to_string(ram.get(2)) << std::endl;
    ram.set(2,2);
    ram.dump();
    std::cout << std::to_string(ram.get(2)) << std::endl;

    std::string tester("f0f0f0f0");
    std::cout << "Decimal: " << utils::hexToInt(tester) << std::endl;
    std::cout << "Binary: " << std::bitset<32>(utils::hexToInt(tester)) << std::endl;

    std::cout << "Hex: " + utils::intToHex(utils::hexToInt(tester));

    return 0;
}