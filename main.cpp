//
// Created by Kalev Martinson on 9/5/23.
//

#include <iostream>
#include "Memory.h"

int main() {
    Memory ram(4);
    ram.set(2,1);
    ram.dump();

    return 0;
}