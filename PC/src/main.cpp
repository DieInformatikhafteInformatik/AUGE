#include "command.h"
#include "stringutils.h"
#include "auge.h"
#include "usb_comm.h"
#include "packet.h"

#include <iostream>

int main()
{
    ServoMovePacket p;
    p.size = 1;
    p.duration = 1;
    p.checksum = 1;
    p.angle = 1;

    uint8_t* rawData = reinterpret_cast<uint8_t*>(&p);

    for(int i = 0; i < sizeof(ServoMovePacket); i++)
    {
        std::cout << std::to_string(i) << ": " << std::to_string(rawData[i]) << std::endl;
    }

    
}