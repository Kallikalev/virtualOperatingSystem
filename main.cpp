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

int NUM_CPUS = 8;


int main() {
    Memory disk(2048);
    Memory ram(1024);
    std::vector<Processor> cpuList;
    for (int i = 0; i < NUM_CPUS; i++) {
        cpuList.emplace_back(&ram);
    }

    Scheduler scheduler(disk, ram);
    std::vector<PCB> pcbList;

    Loader::load("manyJobs.txt", disk, pcbList);
    for (PCB& pcb : pcbList) {
        scheduler.newJob(pcb);
    }

    while (!scheduler.allFinished()) {
        scheduler.getReady();
        scheduler.dispatchJobs(cpuList);
        bool jobsDone = false;
        while (!jobsDone) {
            for (auto & cpu : cpuList) {
                if (!cpu.free) {
                    if (!cpu.computeCycle()) {
                        jobsDone = true;
                    }
                }
            }
        }
        scheduler.finishJobs(cpuList);
    }


    return 0;
}