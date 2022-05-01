#include "figure.h"

std::ostream& operator<<(std::ostream& out, const Figure& obj)
{
    out << obj.m_figure;
    return out;
}

bool Figure::get_collor() const 
{
    return m_collor;
}

std::string Figure::get_figure() const
{
    return m_figure;
}