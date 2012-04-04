#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

class Logger
{
public:
    Logger(void)
    {
    }

    ~Logger(void)
    {
        Logger::ClearBuffer();
    }

    static void Append(const char * message) 
    {
        strings.push_back(std::string(message));
    }

    static void WriteToStdio(const char * message)
    {
        std::cerr << message << std::endl;
    }

    static void WriteToFile()
    {
        std::ofstream file(file_name);
        if (file.is_open())
        {
            std::for_each(strings.begin(), strings.end(), [&file](std::string& message) {
                file << message << std::endl;
            });
            file.close();
        }
        else
        {
            Logger::WriteToStdio("Error opening logfile");
            //LOG_WRITE_TO_STDIO("Error opening logfile.");
        }
    }

    static void SetFilename(const char * filename)
    {
        file_name = filename;
    }

    static void ClearBuffer() 
    {
    }

private:
    static std::string file_name;
    static std::vector<std::string> strings;
};

#define LOG_APPEND(x) Logger::Append(x)
#define LOG_SET_FILENAME(x) Logger::SetFilename(x)
#define LOG_WRITE_TO_STDIO(x) Logger::WriteToStdio(x)
#define LOG_WRITE_FILE Logger::WriteToFile()

#endif
