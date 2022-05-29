#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#define BLACK 0
#define WHITE 1
#define EMPTY " "

class Figure;
typedef std::vector<std::vector<std::unique_ptr<Figure>>> FIGURES;

class Figure
{
public:
    Figure() = default;
    Figure(const Figure& rhs) = default;
    Figure(Figure&& rhs) = default;
    Figure& operator=(const Figure& rhs) = default;
    Figure& operator=(Figure&& rhs) = default;
    virtual ~Figure() = default;
public:
    inline friend std::ostream& operator<<(std::ostream& out, const Figure& obj);
    virtual void set_collor(bool collor) = 0;
    inline bool get_collor() const;
    inline std::string get_figure() const;
protected:
    bool m_collor;
    std::string m_figure;
};

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

#endif //FIGURE_H