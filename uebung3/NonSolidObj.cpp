#include "nonsolidobj.h"
#include <QPainter>
#include <QPoint>






NonSolidObj::NonSolidObj(const QPoint& start, const QPoint& end)
    : GraphObj(start, Qt::black, false), start(start), end(end) {}

NonSolidObj::NonSolidObj(const QPoint& p)
    : GraphObj(p, Qt::black, false), start(p), end(p) {}

NonSolidObj::~NonSolidObj() {}

void NonSolidObj::display(QPainter* painter) const {
    painter->setPen(color);
}
