

#include "line.h"
#include <QPainter>
#include <cmath>

Line::Line(const QPoint& start, const QPoint& end, const QColor color)
    : NonSolidObj(start), start(start), end(end) {
    this->color = color;
}

double Line::calcLineLength() const {
    QPoint diff = end - start;  // Q Point Operator -
    return std::sqrt(diff.x() * diff.x() + diff.y() * diff.y());
}

void Line::display(QPainter* painter) const {
    NonSolidObj::display(painter);
    painter->drawLine(start, end);
}
bool Line::isInside(const QPoint& point) const {
    const int threshold = 5; // 5 pixels threshold
    QLineF lineF(start, end);

    // Calculate the distance from point to line
    double numerator = qAbs((end.y() - start.y()) * point.x() -
                            (end.x() - start.x()) * point.y() +
                            end.x() * start.y() - end.y() * start.x());
    double denominator = qSqrt(qPow(end.y() - start.y(), 2) + qPow(end.x() - start.x(), 2));

    double distance = numerator / denominator;

    // Check if the point is within the bounding box of the line segment
    bool withinBoundingBox =
        point.x() >= qMin(start.x(), end.x()) - threshold &&
        point.x() <= qMax(start.x(), end.x()) + threshold &&
        point.y() >= qMin(start.y(), end.y()) - threshold &&
        point.y() <= qMax(start.y(), end.y()) + threshold;

    return distance <= threshold && withinBoundingBox;
}
