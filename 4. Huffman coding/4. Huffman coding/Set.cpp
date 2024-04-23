#include "Set.h"

Set::Set() {
    for (int i = 0; i < m_setSize; i++) {
        m_setArray[i] = (char) 0;
    }
}

Set::Set(unsigned char symbol) {
    for (int i = 0; i < m_setSize; i++) {
        m_setArray[i] = (unsigned char) 0;
    }

    int index = (int)symbol / 8;
    int bit = (int)symbol % 8;

    m_setArray[index] |= 1 << (7 - bit);
}

Set::Set(const Set& other) {
    for (int i = 0; i < m_setSize; i++) {
        m_setArray[i] = other.m_setArray[i];
    }
}

Set& Set::operator=(const Set& other) {
    if (this == &other) {
        return *this;
    }

    for (int i = 0; i < m_setSize; i++) {
        m_setArray[i] = other.m_setArray[i];
    }

    return *this;
}

Set Set::operator|(const Set& other) {
    Set tmp(*this);
    tmp |= other;

    return tmp;
}

Set Set::operator|=(const Set& other) {
    for (int i = 0; i < m_setSize; i++) {
        m_setArray[i] |= other.m_setArray[i];
    }

    return *this;
}

bool Set::ContainsSymbol(unsigned char symbol) {
    int index = (int)symbol / 8;
    int bit = (int)symbol % 8;

    return (m_setArray[index] & (1 << (7 - bit))) != 0;
}

void Set::InsertSymbol(unsigned char symbol) {
    if (!ContainsSymbol(symbol)) {
        int index = (int)symbol / 8;
        int bit = (int)symbol % 8;

        m_setArray[index] |= 1 << (7 - bit);
    }
}