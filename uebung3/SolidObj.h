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

};

#endif // SOLIDOBJ_H
