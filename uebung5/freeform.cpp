#include "freeform.h"
#include <QPainter>

Freeform::Freeform(const std::vector<QPoint>& points, const QColor& color)
    : NonSolidObj(points.front(), color, false), points(points) {}

double Freeform::calcLineLength() const {
    double length = 0;
    for (size_t i = 1; i < points.size(); ++i) {
        length += QLineF(points[i-1], points[i]).length();
    }
    return length;
}

void Freeform::display(QPainter* painter) const {
    painter->save();
    painter->setPen(QPen(color, 2));
    for (size_t i = 1; i < points.size(); ++i) {
        painter->drawLine(points[i-1], points[i]);
    }
    painter->restore();
}

bool Freeform::isInside(const QPoint& point) const {
    const int threshold = 5; // 5 pixels threshold
    for (const auto& freeformPoint : points) {
        if (QLineF(point, freeformPoint).length() <= threshold) {
            return true;
        }
    }
    return false;
}

void Freeform::move(const QPoint& delta) {
    for (auto& point : points) {
        point += delta;
    }
}

void Freeform::setColor(const QColor& newColor) {
    color = newColor;
}

void Freeform::setFilled(bool isFilled) {
    // Freeform objects are not filled, so this method does nothing
    (void)isFilled;
}
