#ifndef SOLIDOBJ_H
#define SOLIDOBJ_H

#include <QObject>
#include <QWidget>

#include "graphobj.h"

// Abstrakte Basisklasse für Körperobjekte, abgeleitet von GraphObj
class SolidObj : public GraphObj {
public:
    virtual double calcArea() const = 0; // Rein virtuelle Methode zur Berechnung der Fläche
    void display(QPainter* painter) const override; // Überschriebene Methode zur Anzeige
    SolidObj(const QPoint& refPnt, const QColor& color, bool filled)
        : GraphObj(refPnt, color, filled) {}
    virtual bool isInside(const QPoint& point) const override = 0;
    virtual void setFilled(bool filled) override {
        this->filled = filled;
    }
    void setColor(const QColor& color) override {
        this->color = color;
    }

    virtual ~SolidObj() = default;

    // Verbieten von Copy Constructor und Copy Assignment Operator
    SolidObj(const SolidObj&) = delete;
    SolidObj& operator=(const SolidObj&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    SolidObj(SolidObj&&) = default;
    SolidObj& operator=(SolidObj&&) = default;
};

#endif // SOLIDOBJ_H
