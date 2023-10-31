//
// Created by Kalev Martinson on 10/30/23.
//

#include "Scheduler.h"
#include "ContextSwitcher.h"

Scheduler::Scheduler(Memory &disk, Memory &ram) : disk(disk), ram(ram) {}


void Scheduler::newJob(PCB &job) {
    newQueue.push(&job);
}

void Scheduler::getReady() {
    uint32_t ramWriteLoc = 0;
    while (!newQueue.empty()) {
        PCB& job = *newQueue.front();
        if (ram.size() - ramWriteLoc >= job.size) {
            readyQueue.push(&job);
            newQueue.pop();
            job.ramAddress = ramWriteLoc;
            job.registers.setIR(ramWriteLoc);
            for (int i = 0; i < job.size; i++) {
                ram.set(ramWriteLoc + i, disk.get(job.diskAddress + i));
            }
            ramWriteLoc += job.size;
        } else {
            break;
        }
    }
}

bool Scheduler::dispatchJob(Processor& cpu) {
    if (readyQueue.empty()) {return false;}
    if (runningJob != nullptr) {
        ContextSwitcher::switchOut(cpu, *runningJob);
    }
    runningJob = readyQueue.front();
    readyQueue.pop();
    ContextSwitcher::switchIn(cpu, *runningJob);
    return true;
}

void Scheduler::finishJob(Processor &cpu) {
    ContextSwitcher::switchOut(cpu, *runningJob);
    finishedQueue.push(runningJob);
    for (int i = 0; i < runningJob->size; i++) {
        disk.set(runningJob->diskAddress + i, ram.get(runningJob->ramAddress + i));
        ram.set(runningJob->ramAddress + i, 0);
    }
    runningJob = nullptr;
}