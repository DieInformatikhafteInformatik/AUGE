#pragma once

#include <functional>
#include <windows.h>
#include <thread>

const POINT INVALID_WINDOW_MOUSE_POS{-1, -1};

class LoopThread
{
    using LoopFunc = std::function<void(LoopThread*)>;
    using ConditionFunc = std::function<bool()>;

private:
    std::thread thread;
    LoopFunc lFunc;
    ConditionFunc cFunc;
    bool running;
    long timeout;

    void threadFunction(long timeout);

public:
    LoopThread(LoopFunc lFunc, ConditionFunc cFunc, long timeout);

    void start();
    void stop();
    void join();
    void setDaemon();
    bool shouldRun();
};

LoopThread createMousePositionThread(HWND hWindow, std::function<void(POINT)> command, long timeout);
