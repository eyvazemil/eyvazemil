#include "RGBA.h"

//! constructors
RGBA::RGBA(int r, int g, int b, int a) {
    m_r = r;
    m_g = g;
    m_b = b;
    m_a = a;
}

RGBA::RGBA(const RGBA & rhs) {
    this->m_r = rhs.m_r;
    this->m_g = rhs.m_g;
    this->m_b = rhs.m_b;
    this->m_a = rhs.m_a;
}

RGBA & RGBA::operator=(const RGBA & rhs) {
    this->m_r = rhs.m_r;
    this->m_g = rhs.m_g;
    this->m_b = rhs.m_b;
    this->m_a = rhs.m_a;
    return *this;
}