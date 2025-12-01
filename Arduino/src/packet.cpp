#include <stdlib.h>

#include "packet.h"
#include "common_print.h"

uint16_t genChecksum(const uint8_t *data, size_t from, size_t to)
{
    uint16_t checksum = 5381;
    for(size_t i = from; i < to; i++)
    {
        checksum = 33 * checksum + data[i];
    }

    return checksum;
}

uint16_t getChecksum(const uint8_t* data, size_t numOfBytes)
{
    uint8_t* temp = (uint8_t*) malloc(2);
    temp[0] = data[2];
    temp[1] = data[3];
    uint16_t checksum = *reinterpret_cast<uint16_t*>(temp);

    free(temp);

    return checksum;
}

bool checkHeaderSize(const uint8_t* data, size_t numOfBytes)
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
 * Davor sollte unbedingt checkHeader(const uint8_t* data, size_t numOfBytes) gecalled werden.
 * 
 * @param data 
 * @param numOfBytes 
 */
void printPacketInfo(const uint8_t* data, size_t numOfBytes)
{
    cpr::print("Packet-Type: ");
    cpr::print(data[0]);
    cpr::newLine();

    cpr::print("Packet-Größe (soll): ");
    cpr::print(data[1]);
    cpr::newLine();

    cpr::print("Checksum: ");
}

bool isValidPacketData(const uint8_t *rawData, size_t numOfBytes)
{
    if(!checkHeaderSize(rawData, numOfBytes)) return false;

    uint8_t expectedNumOfBytes = rawData[1];
    if(expectedNumOfBytes != numOfBytes) 
    {
        cpr::println("Fehler: Packet ist unvollständig!");
        printPacketInfo(rawData, numOfBytes);

        return false;
    }

    uint16_t expectedChecksum = getChecksum(rawData, numOfBytes);
    uint16_t checksum = genChecksum(rawData, 3, 5);
    if(checksum != expectedChecksum)
    {
        cpr::println("Fehler: Packet ist beschädigt!");
        printPacketInfo(rawData, numOfBytes);

        return false;
    }
    return true;
}

