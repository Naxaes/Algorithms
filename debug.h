#pragma once

#define Assert(statement, ...) if (!(statement)) LogImplementation(LogLevel::ASSERTION, #statement, __FILE__, __LINE__, __VA_ARGS__)

#define Info(...)    LogImplementation(LogLevel::INFO,    #__VA_ARGS__, __FILE__, __LINE__, __VA_ARGS__)
#define Error(...)   LogImplementation(LogLevel::ERROR,   #__VA_ARGS__, __FILE__, __LINE__, __VA_ARGS__)
#define Warning(...) LogImplementation(LogLevel::WARNING, #__VA_ARGS__, __FILE__, __LINE__, __VA_ARGS__)

#ifdef DEBUG
#define DEBUG_BLOCK(x) do { x } while(false)
#else
#define DEBUG_BLOCK(x)
#endif

#define TIME_SCOPE(name)  const auto name##__LINE__ = Timer(#name)

#include <unordered_map>
#include <chrono>


enum class LogLevel
{
    INFO, WARNING, ERROR, ASSERTION
};

void LogImplementation(LogLevel level, const char* statement, const char* file, unsigned line, const char* message = "", ...);


class Timer
{
public:
    using Clock = std::chrono::time_point<std::chrono::system_clock>;
    using ClockDiff = std::chrono::duration<double>;

    static std::unordered_map<const char*, ClockDiff> times;

    const char* name;
    const Clock start;

    explicit Timer(const char* name) : name(name), start(std::chrono::system_clock::now()) {}
    ~Timer();

    static void PrintTimes();
};

