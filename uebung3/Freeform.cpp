#include "freeform.h"
#include <QPainter>

Freeform::Freeform(const std::vector<QPoint>& points, const QColor& color)
    : NonSolidObj(points[0]), points(points) {
    this->color = color;
}



void Freeform::display(QPainter* painter) const {
    NonSolidObj::display(painter);
    for (size_t i = 1; i < points.size(); ++i) {
        painter->drawLine(points[i-1], points[i]);
    }
}

double Freeform::calcLineLength() const {
    double length = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        QPoint diff = points[i] - points[i-1];
        length += std::sqrt(diff.x() * diff.x() + diff.y() * diff.y());
    }
    return length;
}
