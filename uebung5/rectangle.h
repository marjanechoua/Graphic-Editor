#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QWidget>

#include "solidobj.h"

class Rectangle : public SolidObj {
private:
    QPoint refPnt; // Referenzpunkt des Rechtecks
    int width; // Breite des Rechtecks
    int height; // Höhe des Rechtecks

public:
    Rectangle(const QPoint& refPnt, double w, double h, const QColor color, bool filled);
    void display(QPainter* painter) const override;
    double calcArea() const override;
    bool isInside(const QPoint& point) const override;
    void move(const QPoint& delta) override {
        refPnt += delta;
    }
    void setColor(const QColor& color) override ;
    void setFilled(bool filled) override {
        SolidObj::setFilled(filled);
    }



    // Verbieten von Copy Constructor und Copy Assignment Operator
    Rectangle(const Rectangle&) = delete;
    Rectangle& operator=(const Rectangle&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(Rectangle&&) = default;
};

#endif // RECTANGLE_H
