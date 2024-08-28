#ifndef LINE_H
#define LINE_H

#include <QObject>
#include <QWidget>


#include "nonsolidobj.h"



// Klasse für Linien, abgeleitet von NonSolidObj
class Line : public NonSolidObj {
public:
    Line(const QPoint& start, const QPoint& end, const QColor color); // Konstruktor

    double calcLineLength() const override ; // Überschriebene Methode zur Berechnung der Linienlänge




    void display(QPainter* painter) const  ; // Überschriebene Methode zur Anzeige

private:
    QPoint start, end; // Start- und Endpunkt der Linie
};

#endif // LINE_H
