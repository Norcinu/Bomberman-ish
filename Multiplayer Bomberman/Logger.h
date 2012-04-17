#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cassert>

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
		if (message == nullptr) 
		{
			std::string error = __FUNCTION__;
			error.append(" NULLPTR message param.\n");
			Logger::WriteToStdio(error.c_str());
			return;
		}

        strings.push_back(std::string(message));
    }

    static void WriteToStdio(const char * message)
    {
		assert (message != nullptr);
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
        }
    }

    static void SetFilename(const char * filename)
    {
		assert (filename != nullptr);
        file_name = filename;
    }

    static void ClearBuffer() 
    {
		file_name = "";
		strings.clear();
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
