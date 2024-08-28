#include "canvas.h"
#include "triangle.h"
#include "circle.h"
#include "rectangle.h"
#include "freeform.h"
#include "polygon.h"
#include "line.h"

#include <QMouseEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QFrame(parent), dragging(false), type(NONE), currentColor(Qt::black), fillMode(true), clickCount(0), interactionMode(InteractionMode::CREAT)
{
    setFrameStyle(QFrame::Box);
    dragging=true;
    scene = new Scene();
}

Canvas::~Canvas()
{
    delete scene;
}

void Canvas::resizeEvent(QResizeEvent* event) {
    QFrame::resizeEvent(event);

}
QSize Canvas::minimumSizeHint() const
{
    return QSize(200, 200);
}

QSize Canvas::sizeHint() const
{
    return QSize(640, 480);
}

void Canvas::clearCanvas(void)
{
    scene->clearObjects();
    update();
}

void Canvas::setPrimitiveMode(int mode)
{
    type = static_cast<PrimitiveMode>(mode);
}

void Canvas::setInteractionMode(InteractionMode mode) {
    interactionMode = mode;
}

void Canvas::setObjColor(const QColor &col)
{
    currentColor = col;
}

void Canvas::setFillMode(bool filled)
{
    fillMode = filled;
    update();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), Qt::white);
    scene->display(&painter);

    if (dragging) {
        painter.setPen(QPen(currentColor, 2, Qt::SolidLine));
        switch (type) {
        case LINE:
            painter.drawLine(lineStartPoint, lineEndPoint);
            break;
        case CIRCLE:
        {
            int radius = QLineF(lineStartPoint, lineEndPoint).length();
            painter.drawEllipse(lineStartPoint, radius, radius);
            break;
        }
        case RECTANGLE:
            painter.drawRect(QRect(lineStartPoint, lineEndPoint));
            break;
        case FREE_HAND:
            painter.setPen(QPen(currentColor, 1, Qt::SolidLine));
            painter.drawPolyline(freehandPoints.data(), freehandPoints.size());
            break;
        case TRIANGLE:
            if (clickCount > 0) {
                for (size_t i = 0; i < trianglePoints.size(); ++i) {
                    painter.drawLine(trianglePoints[i],
                                     i + 1 < trianglePoints.size() ? trianglePoints[i + 1] : lineEndPoint);
                }
                if (clickCount == 2) {
                    painter.drawLine(trianglePoints[0], lineEndPoint);
                }
            }
            break;
        case POLYGON:
            if (clickCount > 0) {
                for (size_t i = 0; i < polygonPoints.size(); ++i) {
                    painter.drawLine(polygonPoints[i],
                                     i + 1 < polygonPoints.size() ? polygonPoints[i + 1] : lineEndPoint);
                }
                if (clickCount >= 3) {
                    painter.drawLine(polygonPoints.back(), polygonPoints[0]);
                }
            }
            break;
        default:
            break;
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        QPoint clickPoint = event->pos();
        lastPos=clickPoint;

        switch(interactionMode) {
        case InteractionMode::CREAT:
            startCreatingObject(clickPoint);
            break;
        case InteractionMode::COL:
            changeObjectColor(clickPoint);
            break;
        case InteractionMode::DEL:
            deleteObject(clickPoint);
            break;
        case InteractionMode::TRAFO:
            startMovingObject(clickPoint);
            break;
        }

        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && dragging) {
        QPoint currPos = event->pos();
        QPoint delta = currPos - lastPos;

        if (interactionMode == InteractionMode::TRAFO && selectedObject) {
            selectedObject->move(delta);
            lastPos = currPos;
        } else if (interactionMode == InteractionMode::CREAT) {
            switch (type) {
            case RECTANGLE:
                lineEndPoint = currPos;
                break;
            case FREE_HAND:
                freehandPoints.append(currPos);
                break;
            case POLYGON:
                if (clickCount > 0) {
                    polygonPoints.back() = currPos;
                }
                break;
            default:
                lineEndPoint = currPos;
                break;
            }
        }
        update();
    }


}
void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton ) {
        dragging = false;
        if (interactionMode == InteractionMode::TRAFO) {
            selectedObject = nullptr;
        } else if (interactionMode == InteractionMode::CREAT) {
            finishCreatingObject(event->pos());
        }
        update();
    }
}
void Canvas::startCreatingObject(const QPoint& clickPoint)
{
    dragging = true;
    lineStartPoint = clickPoint;
    lineEndPoint = lineStartPoint;

    switch(type) {
    case FREE_HAND:
        freehandPoints.clear();
        freehandPoints.append(lineStartPoint);
        break;
    case TRIANGLE:
        if (clickCount < 3) {
            trianglePoints.push_back(clickPoint);
            clickCount++;
        }
        break;
    case POLYGON:
        if (clickCount == 0) {
            polygonPoints.clear();
        }
        polygonPoints.push_back(clickPoint);
        clickCount++;
        break;
    case RECTANGLE:

        lineStartPoint = clickPoint;
        lineEndPoint = clickPoint;

        break;
    default:
        break;
    }
}



void Canvas::finishCreatingObject(const QPoint& endPoint)
{
    lineEndPoint = endPoint;

    switch (type) {
    case LINE:
        scene->insert(new Line(lineStartPoint, lineEndPoint, currentColor));
        break;
    case CIRCLE:
    {
        int radius = QLineF(lineStartPoint, lineEndPoint).length();
        if (radius > 2) {
            scene->insert(new Circle(lineStartPoint, radius, currentColor, fillMode));
        }
        break;
    }
    case RECTANGLE:
    {

        QRect rect= QRect(lineEndPoint,lineStartPoint);
                scene->insert(new Rectangle(rect.topLeft(), rect.width(), rect.height(), currentColor, fillMode));



        break;
    }
    case FREE_HAND:
        if (freehandPoints.size() > 1) {
            std::vector<QPoint> points(freehandPoints.begin(), freehandPoints.end());
            scene->insert(new Freeform(points, currentColor));
        }
        break;
    case TRIANGLE:
        if (clickCount == 3) {
            scene->insert(new Triangle(trianglePoints, currentColor, fillMode));
            trianglePoints.clear();
            clickCount = 0;
        }
        break;
    case POLYGON:
        if (clickCount >= 3 && (lineEndPoint - polygonPoints[0]).manhattanLength() < 10) {
            polygonPoints.push_back(polygonPoints[0]); // Schließt das Polygon
            scene->insert(new Polygon(polygonPoints, currentColor, fillMode));
            polygonPoints.clear();
            clickCount = 0;
        }

        break;
    default:
        break;
    }
}






void Canvas::changeObjectColor(const QPoint& clickPoint)
{
    int objectCount = scene->getObjectCount();
    for (int i = objectCount - 1; i >= 0; --i) {
        GraphObj* object = scene->at(i);
        if (object && object->isInside(clickPoint)) {
            object->setColor(currentColor);
            if (auto* solidObj = dynamic_cast<SolidObj*>(object)) {
                solidObj->setFilled(fillMode);
            }
            update();
            break;
        }
    }
}

void Canvas::deleteObject(const QPoint& clickPoint)
{
    int objectCount = scene->getObjectCount();
    for (int i = objectCount - 1; i >= 0; --i) {
        GraphObj* object = scene->at(i);
        if (object && object->isInside(clickPoint)) {
            scene->remove(i); // Changed to remove by index
            update();
            break;
        }
    }
}

void Canvas::startMovingObject(const QPoint& clickPoint)
{
    int objectCount = scene->getObjectCount();
    for (int i = 0; i < objectCount; ++i) {
        GraphObj* object = scene->at(i);
        if (object && object->isInside(clickPoint)) {
            selectedObject = object;
            dragging = true;
            break;
        }
    }
}
