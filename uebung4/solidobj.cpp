#include "solidobj.h"
#include <QPoint>
#include <Qpainter>




void SolidObj:: display(QPainter* painter) const{
    painter->setPen(color);
    painter->setBrush(filled ? color : Qt::NoBrush);
}


