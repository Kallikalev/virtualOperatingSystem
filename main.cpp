//
// Created by Kalev Martinson on 9/5/23.
//

#include <list>
#include "Memory.h"
#include "utils.cpp"
#include "Loader.h"
#include "PCB.h"
#include "Processor.h"
#include "Scheduler.h"

int main() {
    Memory disk(2048);
    Memory ram(64);
    Processor cpu(&ram);

    Scheduler scheduler(disk, ram);
    std::vector<PCB> pcbList;

    Loader::load("testJobs.txt", disk, pcbList);
    for (PCB& pcb : pcbList) {
        scheduler.newJob(pcb);
    }


    while (!scheduler.allFinished()) {
        scheduler.getReady();
        scheduler.dispatchJob(cpu);
        while (cpu.computeCycle());
        scheduler.finishJob(cpu);
    }


    return 0;
}