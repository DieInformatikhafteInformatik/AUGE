#include "usb_comm.h"

#include <string>

HANDLE openComPort(BYTE portNumber)
{
    std::string portName = "\\\\.\\COM" + portNumber;

    // https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea#communications-resources
    HANDLE hSerial = CreateFileA(
        portName.c_str(),
        FILE_READ_ACCESS | FILE_WRITE_ACCESS,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    return hSerial;
}
