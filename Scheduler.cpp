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
    while (!newQueue.empty()) {
        PCB& job = *newQueue.front();
        unsigned int numPagesNeeded = job.size / Memory::PAGE_SIZE + (job.size % Memory::PAGE_SIZE != 0);
        std::cout << "Attempting to schedule job #" + std::to_string(job.processId) << std::endl;
        if (ram.getNumFreePages() < numPagesNeeded) {
            break;
        }
        std::cout << "Job scheduled successfully, allocated pages: " + std::to_string(numPagesNeeded) << std::endl;
        for (int i = 0; i < numPagesNeeded; i++) {
            job.pageTable.push_back(ram.allocatePage());
        }
        readyQueue.push(&job);
        newQueue.pop();
        job.registers.setIR(Memory::depageAddress(job.pageTable, 0));
        for (int i = 0; i < job.size; i++) {
            ram.set(Memory::depageAddress(job.pageTable, i), disk.get(job.diskAddress + i));
        }
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
    std::cout << "Running job #" + std::to_string(runningJob->processId) << std::endl;
}

void Scheduler::finishJob(Processor &cpu) {
    ContextSwitcher::switchOut(cpu, *runningJob);
    finishedQueue.push(runningJob);
    for (int i = 0; i < runningJob->size; i++) {
        uint32_t depagedAddress = Memory::depageAddress(runningJob->pageTable, i);
        disk.set(runningJob->diskAddress + i, ram.get(depagedAddress));
        ram.set(depagedAddress, 0);
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