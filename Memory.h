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

public:
    explicit Memory(uint32_t size);
    uint32_t get(uint32_t index);
    void set (uint32_t index, uint32_t val);

    void dump();
};

#endif //VIRTUALOPERATINGSYSTEM_MEMORY_H
