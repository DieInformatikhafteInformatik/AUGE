#pragma once

#include "common_type.h"

#ifndef Arduino_h
#include <iostream>
#endif

namespace cpr
{
    void print(const char* message);
    void print(ui8_t n);
    void print(ui16_t n);
    void print(ui32_t n);
    void print(ui64_t n);
    void print(i8_t n);
    void print(i16_t n);
    void print(i32_t n);
    void print(i64_t n);
    void print(bool b);
    void print(fl32_t f);
    void print(fl64_t f);

    void println(const char* message);
    void println(ui8_t n);
    void println(ui16_t n);
    void println(ui32_t n);
    void println(ui64_t n);
    void println(i8_t n);
    void println(i16_t n);
    void println(i32_t n);
    void println(i64_t n);
    void println(bool b);
    void println(fl32_t f);
    void println(fl64_t f);
    void newLine();
}