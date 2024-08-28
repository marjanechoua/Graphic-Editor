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


    virtual double calcArea() const override; // Überschriebene Methode zur Berechnung der Fläche
    void display(QPainter* painter) const override ; // Überschriebene Methode zur Anzeige
     bool isInside(const QPoint& point) const override;

    void move(const QPoint& delta) override {
        GraphObj::move(delta);  // This moves the refPnt
        for (auto& vertex : vertices) {
            vertex += delta;
        }
    }
    // Verbieten von Copy Constructor und Copy Assignment Operator
    Polygon(const Polygon&) = delete;
    Polygon& operator=(const Polygon&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    Polygon(Polygon&&) = default;
    Polygon& operator=(Polygon&&) = default;

private:
    std::vector<QPoint> vertices; // Vektor mit den Eckpunkten des Polygons
};

#endif // POLYGON_H
