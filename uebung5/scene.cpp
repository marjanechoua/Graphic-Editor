#include "scene.h"

GraphObj* Scene::at(int index) {
    if (index >= 0 && index < objects.size()) {
        return objects[index];
    }
    return nullptr;
}

void Scene::insert(GraphObj* obj) {
    objects.push_back(obj);
}

void Scene::remove(int index) {
    if (index >= 0 && index < objects.size()) {
        delete objects[index];
        objects.erase(objects.begin() + index);
    }
}

void Scene::clearObjects() {
    for (auto obj : objects) {
        delete obj;
    }
    objects.clear();
}

void Scene::display(QPainter* painter) {
    for (auto obj : objects) {
        obj->display(painter);
    }
}
