#pragma once
#include <fstream>
#include <sstream>
#include <utils/log.h>

inline std::string read_file(const std::string& file_path)
{
    std::ifstream file(file_path);

    if(!file.is_open())
    {
        log_error("failed to open file: %s", file_path.c_str());
    }
    std::stringstream ss;

    ss << file.rdbuf();

    return ss.str();
}