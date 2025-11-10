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

uint16_t genPacketChecksum(const Packet *packet)
{
    
    return genChecksum(
        reinterpret_cast<const uint8_t*>(packet),
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

bool checkHeader(const ui8_t* data, size_t numOfBytes)
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
    cpr::print()
}

Packet* rawDataToPacket(const uint8_t* rawData, size_t numOfBytes)
{
    if(!checkHeader(rawData, numOfBytes)) return nullptr;

    uint8_t sz = rawData[1];
    if(sz != numOfBytes) 
    {
        cpr::println("Fehler: Packet ist unvollständig!");
        printPacketInfo(rawData, numOfBytes);

        return nullptr;
    }

    // TODO: Methode für Array-Zugriff erstellen
    ui16_t providedChecksum = getChecksum(rawData, numOfBytes);
    ui16_t checksum = genChecksum(rawData, 3, 5);

    if(checksum != providedChecksum)
    {
        cpr::println("Fehler: Packet ist beschädigt!");
        printPacketInfo(rawData, numOfBytes);
    }

}
