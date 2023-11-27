//
// Created by Kalev Martinson on 9/5/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_MEMORY_H
#define VIRTUALOPERATINGSYSTEM_MEMORY_H

#include <cstdint>
#include <vector>

class Memory {
private:
    std::vector<uint32_t> data;
    std::vector<bool> pages;
    uint32_t numFreePages = 0;

public:
    explicit Memory(uint32_t size);
    uint32_t get(uint32_t index);
    void set(uint32_t index, uint32_t val);
    uint32_t size();


    uint32_t allocatePage();
    void freePage(uint32_t pageNum);
    [[nodiscard]] uint32_t getNumFreePages() const;
    static uint32_t depageAddress(std::vector<uint32_t>& pageTable, uint32_t virtualAddress);

    void dump();

    static const uint32_t PAGE_SIZE = 8;
};

#endif //VIRTUALOPERATINGSYSTEM_MEMORY_H
