#pragma once

#include <cstring>
#include "common_type.h"

struct Packet
{
    ui8_t type; // TODO: Diesen Member inaccessible und statisch (je Subklasse) machen
    ui8_t size;
    ui16_t checksum;

    
};

struct ServoMovePacket : public Packet
{
    float duration;
    float angle;
};

struct LEDTogglePacket : public Packet
{

};

/**
 * @brief Generiert eine einfache Checksum.
 * 
 * @param ptr 
 * @param from Start-Index (inklusiv)
 * @param to End-Index (exklusiv)
 * @return ui16_t 
 */
ui16_t genChecksum(const ui8_t* ptr, size_t from, size_t to);

/**
 * @brief Generiert eine Checksum aus den Daten eines Packets.
 * 
 * @param packet 
 * @return ui16_t
 */
ui16_t genPacketChecksum(const Packet* packet);

void fillPacketHeader(Packet& packet);
bool isValidPacketData(const ui8_t* rawData, size_t numOfBytes);

template<typename T>
inline T* rawDataToPacket(const ui8_t* rawData, size_t numOfBytes, bool copy = false)
{
    ui8_t* finalData;
    if(copy)
    {
        finalData = (ui8_t*) malloc(numOfBytes);
        memcpy(finalData, rawData, numOfBytes);
    }
    else
    {
        finalData = const_cast<ui8_t*>(rawData);
    }

    return reinterpret_cast<T*>(rawData);
}
