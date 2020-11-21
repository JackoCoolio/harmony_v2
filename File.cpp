#include "File.h"

#include <fstream>

void Harmony::File::readToString(std::string path, std::string& output)
{
    std::ifstream ifs(path);

    output.assign((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
}
