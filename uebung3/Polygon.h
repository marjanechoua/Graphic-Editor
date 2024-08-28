#ifndef POLYGON_H
#define POLYGON_H

#include <QObject>
#include <QWidget>

#include "solidobj.h"

#include <vector>

// Klasse für Polygone, abgeleitet von SolidObj
class Polygon : public SolidObj {
public:
    Polygon(const std::vector<QPoint>& vertices, const QColor& color, bool filled);


    virtual double calcArea() const override=0; // Überschriebene Methode zur Berechnung der Fläche
    void display(QPainter* painter) const ; // Überschriebene Methode zur Anzeige


private:
    std::vector<QPoint> vertices; // Vektor mit den Eckpunkten des Polygons
};

#endif // POLYGON_H
