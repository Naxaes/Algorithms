#include "debug.h"

#include <algorithm>    // std::sort
#include <vector>
#include <tuple>

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <cstdlib>


void LogImplementation(LogLevel level, const char* statement, const char* file, unsigned line, const char* message, ...)
{
    constexpr int BUFFER_SIZE = 256;

    char* buffer = (char *) malloc(BUFFER_SIZE);
    memset(buffer, 0, BUFFER_SIZE);

    va_list argptr;
    va_start(argptr, message);
    vsnprintf(buffer, BUFFER_SIZE, message, argptr);
    va_end(argptr);

    if (level == LogLevel::INFO)
    {
        fprintf(
                stdout,
                "[Logging] (Info):\n"
                "\tMessage: %s\n",
                buffer
        );
    }
    else if (level == LogLevel::WARNING)
    {
        fprintf(
                stderr,
                "[Logging] (Warning):\n"
                "\tStatement: %s\n"
                "\tFile:      %s\n"
                "\tLine:      %i\n"
                "\tMessage:   %s\n",
                statement, file, line, buffer
        );
    }
    else if (level == LogLevel::ERROR)
    {
        fprintf(
                stderr,
                "[Logging] (Error):\n"
                "\tStatement: %s\n"
                "\tFile:      %s\n"
                "\tLine:      %i\n"
                "\tMessage:   %s\n",
                statement, file, line, buffer
        );

        printf("Press enter to continue...\n");
        getchar();  // To keep Windows OS window open.

        exit(-1);
    }
    else if (level == LogLevel::ASSERTION)
    {
        fprintf(
                stderr,
                "[Assertion]:\n"
                "\tStatement: %s\n"
                "\tFile:      %s\n"
                "\tLine:      %i\n"
                "\tMessage:   %s\n",
                statement, file, line, buffer
        );

        printf("Press enter to continue...\n");
        getchar();  // To keep Windows OS window open.

        exit(-1);
    }
    else
    {
        printf("Invalid log level option.\n");
    }
}


Timer::~Timer()
{
    auto stop = std::chrono::system_clock::now();
    auto time = stop - this->start;

    if (Timer::times.find(this->name) == Timer::times.end())
        Timer::times[this->name] = time * 1000.0;
    else
        Timer::times[this->name] += time * 1000.0;
}

void Timer::PrintTimes()
{
    std::vector<std::pair<const char*, ClockDiff>> elements(Timer::times.begin(), Timer::times.end());
    std::sort(elements.begin(), elements.end(), [](const auto& a, const auto& b){ return a.second > b.second; });

    printf("---- TIMER START ----\n");
    for (const auto& it : elements)
        printf("%-24s : %fms\n", it.first, it.second.count());
    printf("---- TIMER END ----\n\n");

    Timer::times.clear();
}
