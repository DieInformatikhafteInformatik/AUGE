#pragma once

#include "stdint.h"

#ifndef Arduintno_h
#include <iostream>
#endif

namespace cpr
{
    void print(const char* message);
    void print(uint8_t n);
    void print(uint16_t n);
    void print(uint32_t n);
    void print(uint64_t n);
    void print(int8_t n);
    void print(int16_t n);
    void print(int32_t n);
    void print(int64_t n);
    void print(bool b);
    void print(float f);
    void print(double f);

    void println(const char* message);
    void println(uint8_t n);
    void println(uint16_t n);
    void println(uint32_t n);
    void println(uint64_t n);
    void println(int8_t n);
    void println(int16_t n);
    void println(int32_t n);
    void println(int64_t n);
    void println(bool b);
    void println(float f);
    void println(float f);
    void newLine();
}