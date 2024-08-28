#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QWidget>
#include <QPoint>


#include "solidobj.h"

// Klasse für Kreise, abgeleitet von der SolidObj-Klasse
class Circle : public SolidObj {
private:
    int radius; // Radius des Kreises
    QPoint refPnt; // Referenzpunkt des Kreises

public:
    Circle(const QPoint& refPnt, int radius, const QColor& color, bool filled);

    double calcArea() const override; // Überschriebene Methode zur Berechnung der Fläche des Kreises (Implementierung erforderlich)

    void display(QPainter* painter) const  ; // Überschriebene Methode zur Anzeige des Kreises




};

#endif // CIRCLE_H
