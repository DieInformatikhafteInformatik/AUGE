#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include <optional>

#include "auge.h"

class AUGESystem;

struct Command
{
    using Args = std::vector<std::string>;
    using Aliases = std::vector<std::string>;
    using Executor = std::function<bool(const AUGESystem&, Args)>;

    std::string name;
    Aliases aliases;
    Executor executor;
    std::string description, usage;

    Command(std::string name, Aliases aliases, Executor executor, std::string description, std::string usage) :
        name(std::move(name)), 
        aliases(std::move(aliases)), 
        executor(std::move(executor)), 
        description(std::move(description)),
        usage(std::move(usage)) {}

    Command(std::string name, Aliases aliases, Executor executor) :
        Command(name, aliases, executor, "No Description", "No Usage") {}
    
};

class CommandManager
{
private:
    using _CommandIterator = std::vector<Command>::iterator;

private:
    std::vector<Command> reg;

    _CommandIterator get(std::string_view identifier);
    bool commandExists(const Command& command);


public:
    bool registerCommand(Command command);
    bool unregisterCommand(std::string_view identifier);
    std::optional<std::reference_wrapper<Command>> getCommand(std::string_view identifier);
    
    bool exists(std::string_view identifier);
    void parseCommandLine(std::string line);
};

class InputReader
{
public:
    using StringConsumer = std::function<void(std::string)>;

private:
    StringConsumer onReadFunc;
    bool running;

public:
    InputReader(StringConsumer onReadFunc) :
        onReadFunc(std::move(onReadFunc)) {}

    void start();
    void stop();
};
