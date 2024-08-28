#include "triangle.h"
#include <QPainter>
#include <cmath>

Triangle::Triangle(const std::vector<QPoint>& vertices, const QColor& color, bool filled)
    : SolidObj(vertices[0], color, filled), vertices(vertices)
{

}

void Triangle::display(QPainter* painter) const
{
    SolidObj::display(painter);
    QPolygon triangle;
    for (const auto& point : vertices) {
        triangle << point;
    }

    if (filled) {
        painter->setBrush(color);
        painter->drawPolygon(triangle);
    } else {
        painter->drawPolygon(triangle);
    }
}

double Triangle::calcArea() const
{
    // Using Heron's formula
    double a = QLineF(vertices[0], vertices[1]).length();
    double b = QLineF(vertices[1], vertices[2]).length();
    double c = QLineF(vertices[2], vertices[0]).length();
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
