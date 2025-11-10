#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <concepts>
#include <string>

#include "command.h"
#include "stringutils.h"
#include "auge.h"

int main()
{
    std::string s = "\\\\.\\COM";
    
    std::cout << s << std::endl;
}