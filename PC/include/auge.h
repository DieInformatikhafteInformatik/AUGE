#pragma once

#include <functional>
#include <string>
#include <memory>
#include <thread>

class CommandManager;
class InputReader;

class AUGESystem
{
private:
    CommandManager* cmdManager;
    InputReader* reader;

public:
    AUGESystem(CommandManager* cmdManager);

    void start() const;
    void stop() const;

private:
    void evalLine(std::string s);
};

class LoopThread
{
public:
    using LoopFunc = std::function<void(LoopThread*)>;
    using ConditionFunc = std::function<bool()>;

private:
    std::thread thread;
    LoopFunc lFunc;
    ConditionFunc cFunc;
    bool running;
    void threadFunction(long timeout);

public:
    LoopThread(LoopFunc lFunc, ConditionFunc cFunc);

    void start(long timeout);
    void stop();
    void join();
    void setDaemon();
    bool shouldRun();
};