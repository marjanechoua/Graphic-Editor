#include "triangle.h"
#include <QPainter>
#include <cmath>

Triangle::Triangle(const std::vector<QPoint>& vertices, const QColor& color, bool filled)
    : SolidObj(vertices[0], color, filled), vertices(vertices)
{

}


void Triangle::display(QPainter* painter) const {
    painter->setPen(QPen(color, 2)); // Setzt die Umrissfarbe

    if (filled) {
        painter->setBrush(color); // Setzt die Füllfarbe, wenn gefüllt
    } else {
        painter->setBrush(Qt::NoBrush); // Setzt keine Füllung, wenn nicht gefüllt
    }

    QPolygon triangle;
    for (const auto& point : vertices) {
        triangle << point;
    }
    painter->drawPolygon(triangle);
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


bool Triangle::isInside(const QPoint& point) const {
    // Ensure we have exactly 3 vertices
    if (vertices.size() != 3) return false;

    const QPoint& v1 = vertices[0];
    const QPoint& v2 = vertices[1];
    const QPoint& v3 = vertices[2];

    // Calculate barycentric coordinates
    int denominator = ((v2.y() - v3.y()) * (v1.x() - v3.x()) +
                       (v3.x() - v2.x()) * (v1.y() - v3.y()));

    float a = ((v2.y() - v3.y()) * (point.x() - v3.x()) +
               (v3.x() - v2.x()) * (point.y() - v3.y())) / (float)denominator;
    float b = ((v3.y() - v1.y()) * (point.x() - v3.x()) +
               (v1.x() - v3.x()) * (point.y() - v3.y())) / (float)denominator;
    float c = 1 - a - b;

    // Check if the point is inside the triangle
    return a >= 0 && a <= 1 && b >= 0 && b <= 1 && c >= 0 && c <= 1;
}
