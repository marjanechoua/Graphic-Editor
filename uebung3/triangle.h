#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QPoint>
#include <QColor>
#include "solidobj.h"

class Triangle : public SolidObj
{
private:
   std::vector<QPoint> vertices;
public:
    Triangle(const std::vector<QPoint>& vertices, const QColor& color, bool filled);

    void  display(QPainter* painter) const override ;
    double calcArea() const override;
};


#endif // TRIANGLE_H
