#ifndef FREEFORM_H
#define FREEFORM_H

#include "nonsolidobj.h"
#include <vector>

class Freeform : public NonSolidObj {
private:
    std::vector<QPoint> points;

public:
    Freeform(const std::vector<QPoint>& points, const QColor& color);

    double calcLineLength() const override;
    void display(QPainter* painter) const override;
    bool isInside(const QPoint& point) const override;
    void move(const QPoint& delta) override;
    void setColor(const QColor& color) override;
    void setFilled(bool filled) override;

    // Verbieten von Copy Constructor und Copy Assignment Operator
    Freeform(const Freeform&) = delete;
    Freeform& operator=(const Freeform&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    Freeform(Freeform&&) = default;
    Freeform& operator=(Freeform&&) = default;
};

#endif // FREEFORM_H
