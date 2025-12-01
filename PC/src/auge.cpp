#include <iostream>
#include <thread>

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


void LoopThread::threadFunction(long timeout)
{
    while(shouldRun())
    {
        lFunc(this);

        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
    }
}

/**
 * @param lFunc Funktion, die bei jedem Durchlauf ausgeführt werden soll
 * @param cFunc Bedingungsfunktion, die bestimmt, ob die Schleife weiterlaufen soll; true, wenn ja.
 * @param timeout Timeout nach jedem Schleifendurchlauf in Millisekunden
 */
LoopThread::LoopThread(LoopFunc lFunc, ConditionFunc cFunc, long timeout) :
    lFunc(std::move(lFunc)), cFunc(std::move(cFunc)), timeout(timeout) {}

/**
 * @brief Startet den Thread.
 */
void LoopThread::start(long timeout)
{
    running = true;
    thread = std::thread(&threadFunction, this, timeout);
}

/**
 * @brief Stoppt die Schleife und somit den Thread.
 */
void LoopThread::stop()
{
    running = false;
}

/**
 * @brief 
 * 
 * Diese Methode darf nicht vor Verwendung von LoopThread#start() verwendet werden.
 */
void LoopThread::join()
{
    thread.join();
}

/**
 * @brief Macht diesen Thread zu einem Daemon-Thread.
 * 
 * Das Programm muss bei Vollendung des main-Threads nicht auf diesen Thread warten (Daemon Thread wird beendet).
 * 
 * Diese Methode darf nicht vor Verwendung von LoopThread#start() verwendet werden.
 */
void LoopThread::setDaemon()
{
    thread.detach();
}

/**
 * @brief Bestimmt, ob die Schleife in dem Thread weiterlaufen soll.
 * 
 * @return true Soll weiter laufen
 * @return false Soll gestoppt werden
 */
bool LoopThread::shouldRun()
{
    return running && cFunc();
}