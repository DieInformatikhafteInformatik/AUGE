#include <algorithm>
#include <iostream>

#include "command.h"
#include "stringutils.h"

CommandManager::_CommandIterator CommandManager::get(std::string_view identifier)
{
    return std::find_if(reg.begin(), reg.end(),
        [&identifier](const Command& c)
        {
            return
                str::equals(identifier, c.name, true) ||
                std::any_of(c.aliases.begin(), c.aliases.end(),
                    [&identifier](std::string_view alias)
                    {
                        return str::equals(identifier, alias, true);
                    }
                );
        }
    );
}

bool CommandManager::commandExists(const Command& command)
{
    return
        this->exists(command.name) ||
        std::any_of(command.aliases.begin(), command.aliases.end(),
            [&](std::string_view alias)
            {
                return this->exists(alias);
            }
        );
}

bool CommandManager::registerCommand(Command command)
{
    if(this->commandExists(command)) return false;
    
    reg.push_back(command);
    return true;
}

bool CommandManager::unregisterCommand(std::string_view identifier)
{
    _CommandIterator found = this->get(identifier);
    if(found == reg.end()) return false;

    reg.erase(found);

    return true;
}

std::optional<std::reference_wrapper<Command>> CommandManager::getCommand(std::string_view identifier)
{
    _CommandIterator found = this->get(identifier);
    if(found == reg.end()) return std::nullopt;

    return std::ref(*found);
}

bool CommandManager::exists(std::string_view identifier)
{
    return this->get(identifier) != reg.end();
}


void InputReader::start()
{
    running = true;
    
    std::string line;
    while(running)
    {
        std::getline(std::cin, line, '\n');

        onReadFunc(line);
    }
}

void InputReader::stop()
{
    running = false;
}
