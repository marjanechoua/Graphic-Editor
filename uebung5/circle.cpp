#include "circle.h"
#include <QPainter>
#include <QPoint>


Circle::Circle(const QPoint& refPnt, int radius, const QColor& color, bool filled)
    : SolidObj(refPnt, color, filled), radius(radius), refPnt(refPnt) {}

double Circle::calcArea() const {
    return M_PI * radius * radius;
}

void Circle::display(QPainter* painter) const  {
    painter->setPen(QPen(color,2));
    if (filled){
        painter->setBrush(QBrush(color));
    } else {
        painter ->setBrush(Qt::NoBrush);
    }
    painter->save();
    painter->translate(refPnt);
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->restore();


    painter->drawEllipse(refPnt, radius, radius);
}

bool Circle::isInside(const QPoint& point) const {

    return QLineF(refPnt, point).length() <= radius;
}
