#pragma once

#include <stdint.h>
#include <windows.h>
#include <optional>
#include <queue>
#include <memory>

#include "auge.h"
#include "packet.h"

struct RawPacket
{
    uint8_t* data;
    size_t size;
};

class CommunicationsThread : public LoopThread
{
private:
    HANDLE hSerial;
    std::queue<std::unique_ptr<RawPacket>> packetQueue;
    size_t responseBufferSize;

    void run(LoopThread* loopThread);
    void awaitResponse();

public:
    CommunicationsThread(HANDLE hSerial, ConditionFunc cFunc, size_t responseBufferSize) :
        hSerial(hSerial), responseBufferSize(responseBufferSize), 
        LoopThread(std::bind(&run, this, std::placeholders::_1), cFunc) {}
    
    bool sendPacket(RawPacket rawPacket);
    
    template<packet_typeid_t id>
    inline void pushPacket(Packet<id> packet)
    {
        fillPacketHeader(packet);

        uint8_t* rawData = reinterpret_cast<uint8_t*>(&packet);
        
        packetQueue.push(std::make_unique<RawPacket>(RawPacket{
            rawData,
            packet.size
        }));
    }
};

std::optional<HANDLE> openCOMPort(uint8_t portNumber);
bool setupCOMPort(HANDLE hSerial);