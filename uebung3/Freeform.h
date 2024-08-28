#ifndef FREEFORM_H
#define FREEFORM_H

#include <QObject>
#include <QWidget>
#include <QPoint>

#include <vector>
#include "nonsolidobj.h"


// Klasse für Freiformen, abgeleitet von NonSolidObj
class Freeform : public NonSolidObj {
public:
     Freeform(const std::vector<QPoint>& points, const QColor& color); //Konstruktor

    virtual double calcLineLength() const override ; // Überschriebene Methode zur Berechnung der Linienlänge (Implementierung erforderlich)



    void display(QPainter* painter) const override  ; // Überschriebene Methode zur Anzeige
    void addPoint(const QPoint& point) {
        points.push_back(point);
    }


private:
    std::vector<QPoint> points; // Vektor mit den Punkten der Freiform
};

#endif // FREEFORM_H
