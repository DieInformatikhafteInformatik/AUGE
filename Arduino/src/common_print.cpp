#include "common_print.h"

// Komplett von ChatGPT erstellt, ungetestet
namespace cpr
{
    // ============================================================
    // print() Implementierungen
    // ============================================================

    void print(const char* message)
    {
    #ifdef ARDUINO_h
        Serial.print(message);
    #else
        std::cout << message;
    #endif
    }

    void print(uint8_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(static_cast<unsigned int>(n));
    #else
        std::cout << static_cast<unsigned int>(n);
    #endif
    }

    void print(uint16_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(uint32_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(uint64_t n)
    {
    #ifdef ARDUINO_h
        Serial.print((unsigned long long)n);
    #else
        std::cout << n;
    #endif
    }

    void print(int8_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(static_cast<int>(n));
    #else
        std::cout << static_cast<int>(n);
    #endif
    }

    void print(int16_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(int32_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(int64_t n)
    {
    #ifdef ARDUINO_h
        Serial.print((long long)n);
    #else
        std::cout << n;
    #endif
    }

    void print(bool b)
    {
    #ifdef ARDUINO_h
        Serial.print(b ? "true" : "false");
    #else
        std::cout << (b ? "true" : "false");
    #endif
    }

    void print(float f)
    {
    #ifdef ARDUINO_h
        Serial.print(f, 6);
    #else
        std::cout << f;
    #endif
    }

    void print(double d)
    {
    #ifdef ARDUINO_h
        Serial.print(d, 6);
    #else
        std::cout << d;
    #endif
    }

    // ============================================================
    // println() Implementierungen
    // ============================================================

    void println(const char* message)
    {
    #ifdef ARDUINO_h
        Serial.println(message);
    #else
        std::cout << message << std::endl;
    #endif
    }

    void println(uint8_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(static_cast<unsigned int>(n));
    #else
        std::cout << static_cast<unsigned int>(n) << std::endl;
    #endif
    }

    void println(uint16_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(uint32_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(uint64_t n)
    {
    #ifdef ARDUINO_h
        Serial.println((unsigned long long)n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(int8_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(static_cast<int>(n));
    #else
        std::cout << static_cast<int>(n) << std::endl;
    #endif
    }

    void println(int16_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(int32_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(int64_t n)
    {
    #ifdef ARDUINO_h
        Serial.println((long long)n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(bool b)
    {
    #ifdef ARDUINO_h
        Serial.println(b ? "true" : "false");
    #else
        std::cout << (b ? "true" : "false") << std::endl;
    #endif
    }

    void println(float f)
    {
    #ifdef ARDUINO_h
        Serial.println(f, 6);
    #else
        std::cout << f << std::endl;
    #endif
    }

    void println(double d)
    {
    #ifdef ARDUINO_h
        Serial.println(d, 6);
    #else
        std::cout << d << std::endl;
    #endif
    }

    void newLine()
    {
    #ifdef ARDUINO_h
        Serial.print("\n");
    #else
        std::cout << std::endl;
    #endif
    }
}