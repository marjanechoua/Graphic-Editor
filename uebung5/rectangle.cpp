#include "rectangle.h"
#include <QPainter>
#include <QPoint>


Rectangle::Rectangle(const QPoint& refPnt, double w, double h, const QColor color, bool filled)
    : SolidObj(refPnt, color, filled), refPnt(refPnt), width(w), height(h)
{
}

void Rectangle::display(QPainter* painter) const
{
    painter->setPen(QPen(color, 2));
    if (filled) {
        painter->setBrush(QBrush(color));
    } else {
        painter->setBrush(Qt::NoBrush);
    }
    painter->drawRect(QRect(refPnt, QSize(width, height)));

    painter->save();


    painter->restore();
}

double Rectangle::calcArea() const {
    return width * height;
}

bool Rectangle::isInside(const QPoint& point) const {

    return  QRect(refPnt.x() - width / 2, refPnt.y() - height / 2, width, height).contains(point);
}
void Rectangle::setColor(const QColor& newColor) {
    this->color = newColor;
}


