//
// Created by Kalev Martinson on 9/5/23.
//

#include <iostream>
#include <list>
#include "Memory.h"
#include "utils.cpp"
#include "Loader.h"
#include "PCB.h"

int main() {
    Memory disk(40);
    std::cout << "Disk before:" << std::endl;
    disk.dump();

    std::list<PCB> pcbList;

    Loader::load("testJobs.txt", &disk, &pcbList);

    std::cout << "Disk after:" << std::endl;
    disk.dump();

    return 0;
}