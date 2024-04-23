#pragma once
#include <iostream>

class Set {
public:
    Set();
    Set(unsigned char symbol);
    Set(const Set& other);

    ~Set() = default;

    Set& operator=(const Set& other);
    Set operator|(const Set& other);
    Set operator|=(const Set& other);

    bool ContainsSymbol(unsigned char symbol);

    void InsertSymbol(unsigned char symbol);

    friend std::ostream& operator<<(std::ostream& out, const Set& other) {
        for (int i = 0; i < 256; i++) {
            int index = i / 8;
            int bit = i % 8;

            if ((other.m_setArray[index] & (1 << (7 - bit))) != 0) {
                out << (unsigned char)i;
            }
        }

        return out;
    }

private:
    static const int m_setSize = 32;
    unsigned char m_setArray[m_setSize];
};