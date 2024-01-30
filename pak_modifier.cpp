#include "pak_modifier.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

PAKModifier::PAKModifier() {}

void PAKModifier::run() {
    std::cout << "What path is your PAK that you want to modify?" << std::endl;
    std::getline(std::cin, filePath_);

    std::cout << "What part would you like to replace?" << std::endl;
    std::getline(std::cin, partToReplace_);

    std::cout << "What replacement would you like to have?" << std::endl;
    std::getline(std::cin, replacement_);

    if (modifyFile()) {
        std::cout << "DONE." << std::endl;
    }
}

bool PAKModifier::modifyFile() {
    std::ifstream inputFile(filePath_, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return false;
    }

    fileContent_ = std::vector<unsigned char>((std::istreambuf_iterator<char>(inputFile)),
                                              std::istreambuf_iterator<char>());

    std::vector<unsigned char> partBytes = HexStringToBytes(partToReplace_);
    std::vector<unsigned char> replacementBytes = HexStringToBytes(replacement_);

    auto partPosition = std::search(fileContent_.begin(), fileContent_.end(), partBytes.begin(), partBytes.end());

    if (partPosition == fileContent_.end()) {
        std::cerr << "Sorry, the part that you're looking for doesn't seem to exist in the PAK file." << std::endl;
        return false;
    }

    std::copy(replacementBytes.begin(), replacementBytes.end(), partPosition);

    inputFile.close();

    std::ofstream outputFile(filePath_, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return false;
    }

    outputFile.write(reinterpret_cast<const char*>(fileContent_.data()), fileContent_.size());

    outputFile.close();

    return true;
}
