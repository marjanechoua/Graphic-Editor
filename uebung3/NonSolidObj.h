#ifndef NONSOLIDOBJ_H
#define NONSOLIDOBJ_H

#include <QObject>
#include <QWidget>

#include "graphobj.h"

// Abstrakte Basisklasse für Nicht-Körperobjekte, abgeleitet von GraphObj
class NonSolidObj : public GraphObj {
public:
    NonSolidObj(const QPoint& start, const QPoint& end);
    virtual ~NonSolidObj(); // Virtueller Destruktor

    virtual double calcLineLength() const = 0; // Rein virtuelle Methode zur Berechnung der Linienlänge



    void display(QPainter* painter) const override ; // Überschriebene Methode zur Anzeige

protected:
    NonSolidObj(const QPoint& p); // Make the constructor protected
    // Other member functions...
private:
    QPoint start, end;
};

#endif // NONSOLIDOBJ_H
