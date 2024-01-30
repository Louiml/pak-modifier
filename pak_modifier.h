#ifndef PAK_MODIFIER_H
#define PAK_MODIFIER_H

#include "hex_converter.h"
#include <vector>

class PAKModifier {
public:
    PAKModifier();

    void run();

private:
    std::string filePath_;
    std::string partToReplace_;
    std::string replacement_;
    std::vector<unsigned char> fileContent_;

    bool modifyFile();
};

#endif
