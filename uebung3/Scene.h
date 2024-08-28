#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include <QWidget>

#include <vector>
#include "graphobj.h"


//#define WRITE_BIN

// Klasse für die Verwaltung einer Szene mit verschiedenen geometrischen Objekten
class Scene {
public:



    GraphObj* at(int index); // Gibt das GraphObj-Objekt an der angegebenen Indexposition zurück
    void insert(GraphObj* obj); // Fügt ein GraphObj-Objekt zur Szene hinzu
    void remove(GraphObj* obj); // Entfernt ein GraphObj-Objekt aus der Szene
    void clearObjects(); // Löscht alle Objekte aus der Szene
    void display(QPainter* painter);


private:
    std::vector<GraphObj*> objects; // Vektor zum Speichern aller GraphObj-Objekte
    int width;
    int height;
};

#endif // SCENE_H
