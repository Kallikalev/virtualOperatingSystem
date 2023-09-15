//
// Created by Kalev Martinson on 9/5/23.
//

#include <cstdint>
#include <string>

#include <iostream>

class utils {
private:
    inline static const std::string hexChars = "0123456789ABCDEF";

public:
    static uint32_t hexToInt(std::string input) {
        uint32_t result = 0;
        for (int i = 0; i < 8; i++) { // process characters left to right
            result <<= 4;
            result += (uint32_t)hexChars.find((char)toupper(input[i]));
        }
        return result;
    }

    static std::string intToHex(uint32_t input) {
        std::string result;
        for (int i = 0; i < 8; i++) { // adds characters left to right
            result += hexChars.at((input >> 4 * (7 - i)) % 16);
        }
        return result;
    }
};

