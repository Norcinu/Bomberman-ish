#pragma once

#ifndef COMMON_H
#define COMMON_H

#include <string>

#ifdef _WIN32
    #include <direct.h>
    #define GET_CWD _getcwd
#else
    #include<unistd.h>
    #define GET_CWD getwd
#endif

namespace common {
    static const std::string GRAPHIC_DIR = "data\\bitmaps\\";
    static const std::string SOUND_DIR   = "data\\sounds\\";
    static const std::string LEVEL_DIR   = "data\\levels\\";
    static const std::string FONT_DIR    = "data\\fonts\\";

    static std::string FStripPathAndExtension(const std::string& file) {
        auto end = file.find_last_of(".");
        auto start = file.find_last_of("\\");
        std::string name = file.substr(start+1, (end-start)-1);
        return std::move(name);
    }
}

#endif
