#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <concepts>

#include "command.h"
#include "stringutils.h"
#include "auge.h"

int main()
{
    int i = 10;
    char* buffer = (char*) calloc(1, 3);
    itoa(25, buffer, 10);

    std::cout << buffer << std::endl;
}