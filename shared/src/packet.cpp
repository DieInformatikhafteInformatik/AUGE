#include <stdlib.h>

#include "packet.h"
#include "common_print.h"

ui16_t genChecksum(const ui8_t *data, size_t from, size_t to)
{
    ui16_t checksum = 5381;
    for(size_t i = from; i < to; i++)
    {
        checksum = 33 * checksum + data[i];
    }

    return checksum;
}

ui16_t genPacketChecksum(const Packet *packet)
{
    return genChecksum(
        reinterpret_cast<const ui8_t*>(packet),
        3,
        5
    );
}

void fillPacketHeader(Packet &packet)
{
    packet.size = sizeof(packet);
    packet.checksum = genPacketChecksum(&packet);
}

ui16_t getChecksum(const ui8_t* data, size_t numOfBytes)
{
    ui8_t* temp = (ui8_t*) malloc(2);
    temp[0] = data[2];
    temp[1] = data[3];
    ui16_t checksum = *reinterpret_cast<ui16_t*>(temp);

    free(temp);

    return checksum;
}

bool checkHeaderSize(const ui8_t* data, size_t numOfBytes)
{
    if(numOfBytes < 4)
    {
        cpr::println("Packet-Header ist unvollständig!");
        for(size_t i = 0; i < numOfBytes; i++)
        {
            cpr::print("data[");
            cpr::print(i);
            cpr::print("]");
            cpr::newLine();
        }
        return false;
    }
    return true;
}

/**
 * @brief 
 * 
 * Methode setzt voraus, dass der Header vollständig ist. 
 * Davor sollte unbedingt checkHeader(const ui8_t* data, size_t numOfBytes) gecalled werden.
 * 
 * @param data 
 * @param numOfBytes 
 */
void printPacketInfo(const ui8_t* data, size_t numOfBytes)
{
    cpr::print("Packet-Type: ");
    cpr::print(data[0]);
    cpr::newLine();

    cpr::print("Packet-Größe (soll): ");
    cpr::print(data[1]);
    cpr::newLine();

    cpr::print("Checksum: ");
}

bool isValidPacketData(const ui8_t *rawData, size_t numOfBytes)
{
    if(!checkHeaderSize(rawData, numOfBytes)) return false;

    ui8_t expectedNumOfBytes = rawData[1];
    if(expectedNumOfBytes != numOfBytes) 
    {
        cpr::println("Fehler: Packet ist unvollständig!");
        printPacketInfo(rawData, numOfBytes);

        return false;
    }

    ui16_t expectedChecksum = getChecksum(rawData, numOfBytes);
    ui16_t checksum = genChecksum(rawData, 3, 5);
    if(checksum != expectedChecksum)
    {
        cpr::println("Fehler: Packet ist beschädigt!");
        printPacketInfo(rawData, numOfBytes);

        return false;
    }
    return true;
}

