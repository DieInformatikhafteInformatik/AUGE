#include <common_print.h>

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

    void print(ui8_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(static_cast<unsigned int>(n));
    #else
        std::cout << static_cast<unsigned int>(n);
    #endif
    }

    void print(ui16_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(ui32_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(ui64_t n)
    {
    #ifdef ARDUINO_h
        Serial.print((unsigned long long)n);
    #else
        std::cout << n;
    #endif
    }

    void print(i8_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(static_cast<int>(n));
    #else
        std::cout << static_cast<int>(n);
    #endif
    }

    void print(i16_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(i32_t n)
    {
    #ifdef ARDUINO_h
        Serial.print(n);
    #else
        std::cout << n;
    #endif
    }

    void print(i64_t n)
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

    void print(fl32_t f)
    {
    #ifdef ARDUINO_h
        Serial.print(f, 6);
    #else
        std::cout << f;
    #endif
    }

    void print(fl64_t f)
    {
    #ifdef ARDUINO_h
        Serial.print(f, 6);
    #else
        std::cout << f;
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

    void println(ui8_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(static_cast<unsigned int>(n));
    #else
        std::cout << static_cast<unsigned int>(n) << std::endl;
    #endif
    }

    void println(ui16_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(ui32_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(ui64_t n)
    {
    #ifdef ARDUINO_h
        Serial.println((unsigned long long)n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(i8_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(static_cast<int>(n));
    #else
        std::cout << static_cast<int>(n) << std::endl;
    #endif
    }

    void println(i16_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(i32_t n)
    {
    #ifdef ARDUINO_h
        Serial.println(n);
    #else
        std::cout << n << std::endl;
    #endif
    }

    void println(i64_t n)
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

    void println(fl32_t f)
    {
    #ifdef ARDUINO_h
        Serial.println(f, 6);
    #else
        std::cout << f << std::endl;
    #endif
    }

    void println(fl64_t f)
    {
    #ifdef ARDUINO_h
        Serial.println(f, 6);
    #else
        std::cout << f << std::endl;
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