#ifndef GRAPHOBJ_H
#define GRAPHOBJ_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QColor>



// Basisklasse für geometrische Objekte
class GraphObj {
protected:
    QPoint refPnt; // Ein Point-Objekt, das den Referenzpunkt des GraphObj-Objekts speichert
    QColor color;
    bool filled;
public:
    GraphObj(const QPoint& refPnt, const QColor& color, bool filled);

    virtual ~GraphObj(); // Virtueller Destruktor der GraphObj-Klasse, löscht die Grafikobjekte

    void setRefPnt(const QPoint& p); // Funktion, um den Referenzpunkt des GraphObj-Objekts zu setzen

    const QPoint& getRefPnt() const; // Funktion, um den Referenzpunkt des GraphObj-Objekts abzurufen
    // (gibt eine konstante Referenz auf das Point-Objekt zurück)

    virtual void move(const QPoint& delta){
        refPnt += delta;
    }
    virtual float distance(GraphObj* g); // Virtuelle Funktion, um den Abstand zwischen zwei GraphObj-Objekten zu berechnen
    // (muss in abgeleiteten Klassen überschrieben werden)

    virtual void display(QPainter* painter) const =0; // Rein virtuelle Methode zum Anzeigen des Objekts
    // (muss in abgeleiteten Klassen überschrieben werden)


 virtual bool isInside(const QPoint& point) const = 0;
    virtual void setColor(const QColor& color) = 0;
 virtual void setFilled(bool filled) = 0;

    // Verbieten von Copy Constructor und Copy Assignment Operator
    GraphObj(const GraphObj&) = delete;
    GraphObj& operator=(const GraphObj&) = delete;

    // Erlauben von Move Constructor und Move Assignment Operator
    GraphObj(GraphObj&&) = default;
    GraphObj& operator=(GraphObj&&) = default;




};

#endif // GRAPHOBJ_H
