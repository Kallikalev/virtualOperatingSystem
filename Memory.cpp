//
// Created by Kalev Martinson on 9/5/23.
//
#include "Memory.h"
#include <stdexcept>
#include <string>
#include <iostream>

Memory::Memory(uint32_t size) {
    data = std::vector<uint32_t>(4);
}

uint32_t Memory::get(uint32_t index) {
    if (index >= data.size()) {
        throw std::invalid_argument("Index: " + std::to_string(index) + " is greater than maximum index: " + std::to_string(data.size()-1));
    }
    return data[index];
}

void Memory::set(uint32_t index, uint32_t val) {
    if (index >= data.size()) {
        throw std::invalid_argument("Index: " + std::to_string(index) + " is greater than maximum index: " + std::to_string(data.size()-1));
    }
    data[index] = val;
}

void Memory::dump() {
    for (uint32_t t : data) {
        std::cout << t << std::endl;
    }
}
