#include "polygon.h"
#include <QPainter>

Polygon::Polygon(const std::vector<QPoint>& vertices, const QColor& color, bool filled)
    : SolidObj(vertices[0], color, filled), vertices(vertices) {

}

double Polygon::calcArea() const {
    // Implementation of polygon area calculation (e.g., shoelace formula)
    // This is a placeholder and should be implemented properly
    return 0.0;
}

void Polygon::display(QPainter* painter) const {
    SolidObj::display(painter);
    QPolygon polygon;
    for (const auto& point : vertices) {
        polygon << point;
    }
    painter->drawPolygon(polygon);
}
