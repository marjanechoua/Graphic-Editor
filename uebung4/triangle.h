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
    bool isInside(const QPoint& point) const override;
    void move(const QPoint& delta) override {
        GraphObj::move(delta);
        for (auto& vertex : vertices) {
            vertex += delta;
        }
    }
    // Verbieten von Copy Constructor und Copy Assignment Operator
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    Triangle(Triangle&&) = default;
    Triangle& operator=(Triangle&&) = default;
};


#endif // TRIANGLE_H
