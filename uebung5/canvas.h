#ifndef CANVAS_H
#define CANVAS_H

#include <QFrame>

#include "scene.h"

class Canvas : public QFrame
{
    Q_OBJECT

public:
    enum PrimitiveMode {
        NONE, FREE_HAND, CIRCLE, LINE, TRIANGLE, RECTANGLE, POLYGON
    };
    enum class InteractionMode { CREAT, DEL, COL, TRAFO };

    Canvas(QWidget *parent = 0);
    ~Canvas();

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void clearCanvas(void);
    void setPrimitiveMode(int mode);
    void setObjColor(const QColor &col);
    void setFillMode(bool filled);
    void setInteractionMode(InteractionMode mode);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void startCreatingObject(const QPoint& clickPoint);
    void finishCreatingObject(const QPoint& endPoint);
    void changeObjectColor(const QPoint& clickPoint);
    void deleteObject(const QPoint& clickPoint);
    void startMovingObject(const QPoint& clickPoint);

    bool dragging;
    PrimitiveMode type;
    QColor currentColor;
    bool fillMode;
    QPoint lineStartPoint;
    QPoint lineEndPoint;
    QVector<QPoint> freehandPoints;
    std::vector<QPoint> trianglePoints;
    std::vector<QPoint> polygonPoints;
    int clickCount;
    InteractionMode interactionMode;
    GraphObj* selectedObject;
    QPoint moveOffset;
    QPoint lastPos;

    Scene *scene;
};

#endif // CANVAS_H
