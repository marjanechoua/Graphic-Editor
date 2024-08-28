#include "nonsolidobj.h"
#include <QPainter>
#include <QPoint>

NonSolidObj::NonSolidObj(const QPoint& start, const QColor& color, bool filled)
    : GraphObj(start, color, filled) {}

NonSolidObj::NonSolidObj(const QPoint& p)
    : GraphObj(p, Qt::black, false) {}



void NonSolidObj::display(QPainter* painter) const {
    painter->setPen(color);
}

