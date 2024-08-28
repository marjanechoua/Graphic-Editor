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

void Scene::remove(GraphObj* obj) {
    auto it = std::find(objects.begin(), objects.end(), obj);
    if (it != objects.end()) {
        delete *it;
        objects.erase(it);
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
