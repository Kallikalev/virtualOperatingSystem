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

void Scheduler::dispatchJobs(std::vector<Processor>& cpus) {
    while (runningJobs.size() < cpus.size()) {
        runningJobs.push_back(nullptr);
    }
    if (readyQueue.empty()) {return;}
    while (!readyQueue.empty()) {
        int freeCpuIndex = -1;
        for (int i = 0; i < cpus.size(); i++) {
            if (cpus[i].free) {
                freeCpuIndex = i;
                break;
            }
        }
        if (freeCpuIndex == -1) {
            break;
        }
        runningJobs[freeCpuIndex] = readyQueue.front();
        readyQueue.pop();
        ContextSwitcher::switchIn(cpus[freeCpuIndex], *runningJobs[freeCpuIndex]);
        std::cout << "Running job #" + std::to_string(runningJobs[freeCpuIndex]->processId) + " on processor #" + std::to_string(freeCpuIndex) << std::endl;

    }
}

void Scheduler::finishJobs(std::vector<Processor>& cpus) {
    for (int i = 0; i < runningJobs.size(); i++) {
        if (cpus[i].free and runningJobs[i] != nullptr) {
            ContextSwitcher::switchOut(cpus[i], *runningJobs[i]);
            finishedQueue.push(runningJobs[i]);
            for (int j = 0; j < runningJobs[i]->size; j++) {
                uint32_t depagedAddress = Memory::depageAddress(runningJobs[i]->pageTable, j);
                disk.set(runningJobs[i]->diskAddress + j, ram.get(depagedAddress));
                ram.set(depagedAddress, 0);
            }
            while (!runningJobs[i]->pageTable.empty()) {
                ram.freePage(runningJobs[i]->pageTable.back());
                runningJobs[i]->pageTable.pop_back();
            }
            runningJobs[i] = nullptr;
        }
    }
}

bool Scheduler::allFinished() {
    for (auto & runningJob : runningJobs) {
        if (runningJob != nullptr) {
            return false;
        }
    }
    return newQueue.empty() and readyQueue.empty();
}