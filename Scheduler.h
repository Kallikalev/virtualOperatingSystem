//
// Created by Kalev Martinson on 10/30/23.
//

#ifndef VIRTUALOPERATINGSYSTEM_SCHEDULER_H
#define VIRTUALOPERATINGSYSTEM_SCHEDULER_H


#include <queue>
#include "PCB.h"
#include "Memory.h"
#include "Processor.h"

class Scheduler {
public:
    Scheduler(Memory& disk, Memory& ram);
    void newJob(PCB &job);
    void getReady();
    void dispatchJobs(std::vector<Processor>& cpu);
    void finishJobs(std::vector<Processor>& cpu);
    bool allFinished();
private:
    Memory& disk;
    Memory& ram;
    std::queue<PCB*> newQueue;
    std::queue<PCB*> readyQueue;
    std::queue<PCB*> finishedQueue;
    std::vector<PCB*> runningJobs;
};


#endif //VIRTUALOPERATINGSYSTEM_SCHEDULER_H
