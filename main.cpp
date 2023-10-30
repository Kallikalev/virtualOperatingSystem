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
#include "ContextSwitcher.h"

int main() {
    Memory disk(36);

    std::vector<PCB> pcbList;

    Loader::load("testJobs.txt", disk, pcbList);

    pcbList[0].registers.setIR(pcbList[0].diskAddress); // temp, to be handled by scheduler
    pcbList[1].registers.setIR(pcbList[1].diskAddress); // temp, to be handled by scheduler

    Processor cpu(&disk);
//     Running CPU directly on disk, since scheduler and dispatcher don't exist yet



    ContextSwitcher::switchIn(cpu, pcbList.front());

    while (!cpu.computeCycle());

    std::cout << "Sum of int array: " << disk.get(17) << std::endl;

    ContextSwitcher::switchOut(cpu, pcbList[0]);



    ContextSwitcher::switchIn(cpu, pcbList[1]);

    while (!cpu.computeCycle());

    std::cout << "Sum of int array: " << disk.get(35) << std::endl;

    return 0;
}