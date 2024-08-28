#ifndef LINE_H
#define LINE_H

#include "nonsolidobj.h"
#include <QLineF>
#include <QtMath>

class Line : public NonSolidObj {
public:
    Line(const QPoint& start, const QPoint& end, const QColor color); // Konstruktor

    double calcLineLength() const override; // Überschriebene Methode zur Berechnung der Linienlänge

    bool isInside(const QPoint& point) const override ;



    void display(QPainter* painter) const override; // Überschriebene Methode zur Anzeige

    QPoint getStart() const { return start; }
    QPoint getEnd() const { return end; }
    void move(const QPoint& delta) override {
        GraphObj::move(delta);
        start += delta;
        end += delta;
    }
    // Verbieten von Copy Constructor und Copy Assignment Operator
    Line(const Line&) = delete;
    Line& operator=(const Line&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    Line(Line&&) = default;
    Line& operator=(Line&&) = default;
private:
    QPoint start, end; // Start- und Endpunkt der Linie
};

#endif // LINE_H
