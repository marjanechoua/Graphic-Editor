#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QWidget>
#include <QPoint>

#include "solidobj.h"

class Circle : public SolidObj {
private:
    int radius; // Radius des Kreises
    QPoint refPnt; // Referenzpunkt des Kreises

public:
    Circle(const QPoint& refPnt, int radius, const QColor& color, bool filled);

    double calcArea() const override; // Überschriebene Methode zur Berechnung der Fläche des Kreises (Implementierung erforderlich)

    void display(QPainter* painter) const override; // Überschriebene Methode zur Anzeige des Kreises
    bool isInside(const QPoint& point) const override;
    void move(const QPoint& delta) override {
        refPnt += delta;
    }
    void setColor(const QColor& color) override {
        SolidObj::setColor(color);
    }
    void setFilled(bool filled) override {
        SolidObj::setFilled(filled);
    }


    // Verbieten von Copy Constructor und Copy Assignment Operator
    Circle(const Circle&) = delete;
    Circle& operator=(const Circle&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    Circle(Circle&&) = default;
    Circle& operator=(Circle&&) = default;
};

#endif // CIRCLE_H
