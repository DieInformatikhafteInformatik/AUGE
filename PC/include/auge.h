#pragma once

#include <functional>
#include <string>
#include <memory>

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