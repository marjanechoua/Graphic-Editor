

#include "line.h"
#include <QPainter>
#include <cmath>

Line::Line(const QPoint& start, const QPoint& end, const QColor color)
    : NonSolidObj(start), start(start), end(end) {
    this->color = color;
}

double Line::calcLineLength() const {
    QPoint diff = end - start;
    return std::sqrt(diff.x() * diff.x() + diff.y() * diff.y());
}

void Line::display(QPainter* painter) const {
    NonSolidObj::display(painter);
    painter->drawLine(start, end);
}
