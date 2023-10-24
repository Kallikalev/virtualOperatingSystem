//
// Created by Kalev Martinson on 10/24/23.
//

#include "Loader.h"
#include <fstream>
#include <string>
#include <sstream>
#include "utils.cpp"

void Loader::load(const std::string& fileName, Memory *disk, std::list<PCB> *pcbList) {
    std::vector<std::vector<std::string>> tokens;

    // split up lines and load them into tokens
    int numJobs = 0;
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            tokens.push_back(utils::splitString(line, " "));
            if (tokens[tokens.size()-1][0] == "//") { // count the number of headers
                numJobs++;
            }
        }
        file.close();
    }
    numJobs /= 2; // account for the fact that each job has two headers

    uint32_t jobStartLoc = 0;
    uint32_t tokenReadLoc = 0;
    for (int i = 0; i < numJobs; i++) {
        std::vector<std::string> jobHeader = tokens[tokenReadLoc];
        uint32_t jobId = utils::hexToInt(jobHeader[2]);
        uint32_t programSize = utils::hexToInt(jobHeader[3]);
        uint32_t priority = utils::hexToInt(jobHeader[4]);
        tokenReadLoc++;
        for (int j = 0; j < programSize; j++) {
            disk->set(jobStartLoc + j,utils::hexToInt(tokens[tokenReadLoc][0]));
            tokenReadLoc++;
        }
        std::vector<std::string> dataHeader = tokens[tokenReadLoc];
        uint32_t inputSize = utils::hexToInt(dataHeader[2]);
        uint32_t outputSize = utils::hexToInt(dataHeader[3]);
        uint32_t temporarySize = utils::hexToInt(dataHeader[4]);
        tokenReadLoc++;
        for (int j = 0; j < inputSize + outputSize + temporarySize; j++) {
            disk->set(jobStartLoc + programSize + j,utils::hexToInt(tokens[tokenReadLoc][0]));
            tokenReadLoc++;
        }

        PCB newPCB;
        newPCB.processId = jobId;
        newPCB.programSize = programSize;
        newPCB.priority = priority;
        newPCB.diskAddress = jobStartLoc;
        pcbList->push_back(newPCB);

        jobStartLoc += programSize + inputSize + outputSize + temporarySize;
    }
}