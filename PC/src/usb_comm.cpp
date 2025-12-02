#include "usb_comm.h"

#include <string>
#include <iostream>
#include <variant>

std::optional<HANDLE> openCOMPort(uint8_t portNumber)
{
    std::string portName = "\\\\.\\COM" + std::to_string(portNumber);

    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if(hSerial != INVALID_HANDLE_VALUE) return hSerial;
    else return std::nullopt;
}

bool setupCOMPort(HANDLE hSerial)
{
    DCB dcbSerialParams{};
    dcbSerialParams.DCBlength = sizeof(DCB);

    if (!GetCommState(hSerial, &dcbSerialParams)) 
    {
        std::cerr << "Fehler beim getten des Data-Control-Block (DCB)!" << std::endl;
        return false;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) 
    {
        std::cerr << "Fehler beim setten des Data-Control-Block (DCB)!" << std::endl;
        return false;
    }

    COMMTIMEOUTS timeouts{};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if(!SetCommTimeouts(hSerial, &timeouts))
    {
        std::cerr << "Fehler beim Setzen von der COM-Timeouts!" << std::endl;
        return false;
    }

    return true;
}

void CommunicationsThread::run(LoopThread *loopThread)
{
    if(!packetQueue.empty())
    {
        sendPacket(*packetQueue.front());

        packetQueue.pop();
    } 
    else pushPacket(StatusGetPacket());

    awaitResponse();
}

void processResponse(uint8_t* rawData, DWORD bytesRead)
{
    if(!isValidPacketData(rawData, bytesRead)) return;
}

void CommunicationsThread::awaitResponse()
{
    uint8_t* buffer = new uint8_t[responseBufferSize];
    DWORD bytesRead;

    ReadFile(
        hSerial,
        buffer,
        responseBufferSize,
        &bytesRead,
        NULL
    );

    processResponse(buffer, bytesRead);

    delete[] buffer;
}

bool CommunicationsThread::sendPacket(RawPacket rawPacket)
{
    DWORD length = rawPacket.size;
    DWORD bytesWritten;
    
    WriteFile(
        hSerial,
        rawPacket.data,
        length,
        &bytesWritten,
        NULL
    );

    return bytesWritten == length;
}

