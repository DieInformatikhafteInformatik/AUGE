#pragma once

#include <stdint.h>

struct Packet
{
    uint8_t type;
    uint8_t size;
    uint16_t checksum;
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
 * @return uint16_t 
 */
uint16_t genChecksum(const uint8_t* ptr, size_t from, size_t to);
uint16_t genPacketChecksum(const Packet* packet);
void fillPacketHeader(Packet& packet);
Packet* rawDataToPacket(const uint8_t* rawData, size_t numOfBytes);
