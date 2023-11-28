//
// Created by Kalev Martinson on 10/30/23.
//

#include "Scheduler.h"
#include "ContextSwitcher.h"
#include <iostream>

Scheduler::Scheduler(Memory &disk, Memory &ram) : disk(disk), ram(ram) {}


void Scheduler::newJob(PCB &job) {
    newQueue.push(&job);
}

void Scheduler::getReady() {
    uint32_t ramWriteLoc = 0;
    while (!newQueue.empty()) {
        PCB& job = *newQueue.front();
        unsigned int numPagesNeeded = job.size / Memory::PAGE_SIZE + (job.size % Memory::PAGE_SIZE != 0);
        std::cout << "Starting job of total size: " + std::to_string(job.size) << std::endl;
        std::cout << "Num pages needed: " + std::to_string(numPagesNeeded) << std::endl;
        if (ram.getNumFreePages() < numPagesNeeded) {
            break;
        }
        for (int i = 0; i < numPagesNeeded; i++) {
            job.pageTable.push_back(ram.allocatePage());
        }
        readyQueue.push(&job);
        newQueue.pop();
        job.ramAddress = ramWriteLoc;
        job.registers.setIR(ramWriteLoc);
        for (int i = 0; i < job.size; i++) {
            ram.set(Memory::depageAddress(job.pageTable, i), disk.get(job.diskAddress + i));
        }
        ramWriteLoc += numPagesNeeded * Memory::PAGE_SIZE;
    }
}

void Scheduler::dispatchJob(Processor& cpu) {
    if (readyQueue.empty()) {return;}
    if (runningJob != nullptr) {
        ContextSwitcher::switchOut(cpu, *runningJob);
    }
    runningJob = readyQueue.front();
    readyQueue.pop();
    ContextSwitcher::switchIn(cpu, *runningJob);
}

void Scheduler::finishJob(Processor &cpu) {
    ContextSwitcher::switchOut(cpu, *runningJob);
    finishedQueue.push(runningJob);
    for (int i = 0; i < runningJob->size; i++) {
        disk.set(runningJob->diskAddress + i, ram.get(Memory::depageAddress(runningJob->pageTable, i)));
        ram.set(runningJob->ramAddress + i, 0);
    }
    while (!runningJob->pageTable.empty()) {
        ram.freePage(runningJob->pageTable.back());
        runningJob->pageTable.pop_back();
    }
    runningJob = nullptr;
}

bool Scheduler::allFinished() {
    return newQueue.empty() and readyQueue.empty() and runningJob == nullptr;
}