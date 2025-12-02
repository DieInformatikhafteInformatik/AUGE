#include "command.h"
#include "stringutils.h"
#include "auge.h"
#include "usb_comm.h"
#include "packet.h"

#include <iostream>

class TestPacket : public Packet<10>
{
    uint8_t val = 10;
};

bool conditionFunc()
{
    return true;
}

int main()
{
    TestPacket packet;

    std::optional<HANDLE> hSerial = openCOMPort(3);
    if(hSerial && setupCOMPort(*hSerial))
    {
        std::cout << "Connection opened\n";

        CommunicationsThread commThread = CommunicationsThread{
            *hSerial,
            conditionFunc,
            255
        };

        commThread.pushPacket(packet);


        commThread.start(1);

        commThread.join();
    } else std::cerr << "Fehler\n";

    CloseHandle(*hSerial);
}