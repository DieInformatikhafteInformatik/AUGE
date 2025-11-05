#include <iostream>

#include "auge.h"
#include "command.h"
#include "stringutils.h"

template<typename T>
std::vector<T> copyOfRange(std::vector<T> v, size_t firstIndex, size_t lastIndex)
{
    return std::vector<T>(
        v.begin() + firstIndex,
        v.begin() + lastIndex + 1,
        v.get_allocator()
    );
}

AUGESystem::AUGESystem(CommandManager *cmdManager) :
    cmdManager(cmdManager), reader(new InputReader([&](std::string line) { evalLine(line); })) {}

void AUGESystem::start() const
{
    reader->start();
}

void AUGESystem::stop() const
{
    reader->stop();
}

void AUGESystem::evalLine(std::string s)
{
    std::vector<std::string> split = str::split(s, ' ');
    if(split.empty()) return;
    
    if(auto cmdRef = cmdManager->getCommand(split[0]))
    {
        auto& cmd = cmdRef->get();
        size_t sz = split.size();
        Command::Args args = sz == 1 ?
            Command::Args{} :
            copyOfRange(split, 1, sz - 1);

        if(!cmd.executor(*this, args))
        {
            std::cout << "Invalid command usage! Usage: " << cmd.usage << std::endl;
        }
    }
    else
    {
        std::cout << "Unbekannter Command" << std::endl;
    }
}
