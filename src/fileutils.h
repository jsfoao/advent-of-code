#pragma once
#include <errno.h>
#include <iostream>
#include <string>

class FileUtils
{
public:
    static std::string ReadFile(const char* filepath);
};