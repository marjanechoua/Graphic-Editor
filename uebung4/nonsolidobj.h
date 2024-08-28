#ifndef NONSOLIDOBJ_H
#define NONSOLIDOBJ_H

#include "graphobj.h"

class NonSolidObj : public GraphObj {
public:
    NonSolidObj(const QPoint& start, const QColor& color, bool filled);


    virtual double calcLineLength() const = 0;
    void display(QPainter* painter) const override = 0;
    virtual bool isInside(const QPoint& point) const override = 0;
    virtual void setColor(const QColor& color) override {
        this->color = color;
    }
    virtual void setFilled(bool filled) override {
        // Non-solid objects are not filled, so this method does nothing
        (void)filled;
    }


    virtual ~NonSolidObj() = default;
// Verbieten von Copy Constructor und Copy Assignment Operator
    NonSolidObj(const NonSolidObj&) = delete;
    NonSolidObj& operator=(const NonSolidObj&) = delete;

     // Erlauben von Move Constructor und Move Assignment Operator
    NonSolidObj(NonSolidObj&&) = default;
    NonSolidObj& operator=(NonSolidObj&&) = default;


protected:
    NonSolidObj(const QPoint& p);
private:
    QPoint start, end;
};

#endif // NONSOLIDOBJ_H
