//
// Created by Kalev Martinson on 9/5/23.
//
#include "Memory.h"
#include <stdexcept>
#include <string>
#include <iostream>

#include "utils.cpp"

Memory::Memory(uint32_t size) {
    data = std::vector<uint32_t>(size);
    pages = std::vector<bool>(size / PAGE_SIZE);
    numFreePages = pages.size();
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

uint32_t Memory::allocatePage() {
    for (int i = 0; i < pages.size(); i++) {
        if (!pages[i]) {
            pages[i] = true;
            numFreePages--;
            return i;
        }
    }
    return -1;
}

void Memory::freePage(uint32_t pageNum) {
    pages[pageNum] = false;
    for (int i = 0; i < Memory::PAGE_SIZE; i++) {
        data[pageNum * PAGE_SIZE + i] = 0;
    }
    numFreePages++;
}

uint32_t Memory::size() {
    return data.size();
}

void Memory::dump() {
    for (uint32_t t : data) {
        std::cout << utils::intToHex(t) << std::endl;
    }
}

uint32_t Memory::getNumFreePages() const {
    return numFreePages;
}

uint32_t Memory::depageAddress(std::vector<uint32_t>& pageTable, uint32_t virtualAddress) {
    uint32_t page = virtualAddress / Memory::PAGE_SIZE;
    uint32_t offset = virtualAddress % Memory::PAGE_SIZE;
    return pageTable[page] * Memory::PAGE_SIZE + offset;
}
