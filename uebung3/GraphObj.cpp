


#include <cmath>


#include "graphobj.h"




// Konstruktor
GraphObj::GraphObj(const QPoint& refPnt, const QColor& color, bool filled)
    : refPnt(refPnt), color(color), filled(filled) {}

// Destruktor
GraphObj::~GraphObj() {
}


// Funktion zum Setzen des Referenzpunkts
void GraphObj::setRefPnt(const QPoint& p) {
    refPnt = p;
}

// Funktion zum Abrufen des Referenzpunkts
const QPoint& GraphObj::getRefPnt() const {
    return refPnt;
}

// Funktion zum Bewegen des Objekts an eine andere Position
void GraphObj::move(const QPoint& p) {
    refPnt = p;
}

 //Funktion zur Berechnung der Distanz zwischen zwei Objekten
float GraphObj::distance(GraphObj* g) {

        QPoint diff = refPnt - g->getRefPnt();
        return std::sqrt(diff.x() * diff.x() + diff.y() * diff.y());

}


