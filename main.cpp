//
// Created by Kalev Martinson on 9/5/23.
//

#include <iostream>
#include <list>
#include "Memory.h"
#include "utils.cpp"
#include "Loader.h"
#include "PCB.h"
#include "Processor.h"

int main() {
    Memory disk(50);

    std::list<PCB> pcbList;

    Loader::load("testJobs.txt", &disk, &pcbList);


//     Running CPU directly on disk, since scheduler and dispatcher don't exist yet
    Processor cpu(&disk);
    for (int i = 0; i < 5; i++) {
        cpu.computeCycle();
    }


    return 0;
}