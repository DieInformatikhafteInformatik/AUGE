#pragma once

#include <cstring>
#include <stdint.h>

using PacketTypeId = uint8_t;


class BasePacket
{
    virtual ~BasePacket() = default;
};

template<PacketTypeId TypeId = 0>
class Packet : public BasePacket
{
public:
    static constexpr uint8_t type = TypeId;

    uint8_t size;
    uint16_t checksum;

    virtual void run();
};

class ClearToSendPacket : public Packet<1> {};
class StatusGetPacket : public Packet<2> {};

class ServoMovePacket : public Packet<3>
{
public:
    float duration;
    float angle;
};

class LEDTogglePacket : public Packet<4>
{

};

/**
 * @brief Generiert eine einfache Checksum.
 * 
 * @param ptr 
 * @param from Start-Index (inklusiv)
 * @param to End-Index (exklusiv)
 * @return uint16_t 
 */
uint16_t genChecksum(const uint8_t* ptr, size_t from, size_t to);

/**
 * @brief Generiert eine Checksum aus den Daten eines Packets.
 * 
 * @param packet 
 * @return uint16_t
 */
template<PacketTypeId TypeId>
inline uint16_t genPacketChecksum(const Packet<TypeId>* packet)
{
    return genChecksum(
        reinterpret_cast<const uint8_t*>(packet),
        3,
        sizeof(packet)
    );
}

template<PacketTypeId TypeId>
inline void fillPacketHeader(Packet<TypeId>& packet)
{
    packet.size = sizeof(packet);
    packet.checksum = genPacketChecksum(&packet);
}


bool isValidPacketData(const uint8_t* rawData, size_t numOfBytes);

template<typename T>
inline T* rawDataToPacket(const uint8_t* rawData, size_t numOfBytes, bool copy = false)
{
    uint8_t* finalData;
    if(copy)
    {
        finalData = (uint8_t*) malloc(numOfBytes);
        memcpy(finalData, rawData, numOfBytes);
    }
    else
    {
        finalData = const_cast<uint8_t*>(rawData);
    }

    return reinterpret_cast<T*>(rawData);
}
