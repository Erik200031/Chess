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
    friend std::ostream& operator<<(std::ostream& out, const Figure& obj);
    virtual void set_collor(bool collor) = 0;
    bool get_collor() const;
    std::string get_figure() const;
protected:
    bool m_collor;
    std::string m_figure;
};

#endif //FIGURE_H