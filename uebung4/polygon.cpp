#include "polygon.h"
#include <QPainter>

Polygon::Polygon(const std::vector<QPoint>& vertices, const QColor& color, bool filled)
    : SolidObj(vertices[0], color, filled), vertices(vertices) {

}




void Polygon::display(QPainter* painter) const {
    painter->setPen(QPen(color, 2));

    if (filled) {
        painter->setBrush(color);
    } else {
        painter->setBrush(Qt::NoBrush);
    }

    QPolygon polygon;
    for (const auto& point : vertices) {
        polygon << point;
    }
    if (vertices.size() > 2) {
        polygon << vertices.front(); // Schließt das Polygon automatisch
    }
    painter->drawPolygon(polygon);
}

double Polygon::calcArea() const {
    double area = 0.0;
    int n = vertices.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += (vertices[i].x() * vertices[j].y() - vertices[j].x() * vertices[i].y());
    }
    return std::abs(area) / 2.0;
}

bool Polygon::isInside(const QPoint& point) const {
    int i, j, nvert = vertices.size();
    bool c = false;
    for (i = 0, j = nvert - 1; i < nvert; j = i++) {
        if (((vertices[i].y() > point.y()) != (vertices[j].y() > point.y())) &&
            (point.x() < (vertices[j].x() - vertices[i].x()) * (point.y() - vertices[i].y()) / (vertices[j].y() - vertices[i].y()) + vertices[i].x()))
            c = !c;
    }
    return c;
}
