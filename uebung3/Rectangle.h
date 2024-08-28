#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QObject>
#include <QWidget>

#include "solidobj.h"

// Klasse für Rechtecke, abgeleitet von SolidObj
class Rectangle : public SolidObj {
private:
    QPoint refPnt; // Referenzpunkt des Rechtecks

    int width; // Breite des Rechtecks
    int height; // Höhe des Rechtecks

public:
    // Konstruktor für Rechtecke
    Rectangle(const QPoint& refPnt, double w, double h, const QColor color,bool filled);
    // Überschreibt die display()-Funktion der Basisklasse
    void display(QPainter* painter)  const  ;

    // Überschreibt die calcArea()-Funktion der Basisklasse (Implementierung erforderlich)
    double calcArea() const override;




};

#endif // RECTANGLE_H
