#pragma once

#include <stdint.h>
#include <windows.h>
#include <optional>
#include <queue>
#include <memory>

#include "auge.h"
#include "packet.h"

class CommunicationsThread : public LoopThread
{
private:
    HANDLE hSerial;
    std::queue<std::unique_ptr<BasePacket>> packetQueue;
    size_t responseBufferSize;

    void run(LoopThread* loopThread);
    void awaitResponse();

public:
    CommunicationsThread(HANDLE hSerial, ConditionFunc cFunc, long timeout, size_t responseBufferSize) :
        hSerial(hSerial), responseBufferSize(responseBufferSize), 
        LoopThread(std::bind(&run, this, std::placeholders::_1), cFunc, timeout) {}
    
    bool sendPacket(Packet& packet);
    void pushPacket(Packet p);
};

std::optional<HANDLE> openCOMPort(uint8_t portNumber);
bool setupCOMPort(HANDLE hSerial);
LoopThread createCommunicationsThread();