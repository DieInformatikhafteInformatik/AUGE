#include <iostream>
#include <memory>
#include <functional>

#include "command.h"
#include "stringutils.h"
#include "auge.h"

bool execExitCommand(const AUGESystem& sys, Command::Args args)
{
    std::string reason = args.empty() ? "keiner" : args[0];

    std::cout << "Shutdown; Grund: " << reason << std::endl;
    sys.stop();

    return true;
}

int main()
{
    CommandManager cmdManager;
    AUGESystem sys{&cmdManager}; // Erstellen von AUGESystem und Übergabe von CommandManager-Pointer

    std::cout << "Willkommen" << std::endl;
    // std = standard namespace sind die wichtigsten Funktionen definiert
    // cout = console out
    // endl = end-line (äquivalent zu "\n")

    /*
    Command-Konstruktor:
        mit Extra-Informationen:    Command(std::string name, Aliases aliases, Executor executor, std::string description, std::string usage)
        ohne Extra-Informationen:   Command(std::string name, Aliases aliases, Executor executor)

        Objekte können meist über eine Listen-Initialisierung erstellt werden. Hier:
            Command(...) = {...}

        Aliases = std::vector<std::string>
        Args = std::vector<std::string>
        Executor = std::function<bool(const AUGESystem*, Args)
    */
    cmdManager.registerCommand({
        "exit",
        {"close", "bye"},
        execExitCommand,
        "Schließt das Programm.",
        "exit (reason)"
    });

    sys.start();
}