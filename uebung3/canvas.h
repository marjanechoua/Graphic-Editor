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

	Canvas(QWidget *parent = 0);
	~Canvas();

	QSize minimumSizeHint() const;
	QSize sizeHint() const;

	void clearCanvas(void);
    void setPrimitiveMode( int mode);
    void setObjColor(const QColor &col);
    void setFillMode(bool filled);

protected:
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	bool dragging;
	PrimitiveMode type;
    QColor currentColor;
    bool fillMode;
    QPoint lineStartPoint;
    QPoint lineEndPoint;
    QVector <QPoint> freehandPoints;
    std::vector<QPoint> trianglePoints;

    Scene *scene;
};

#endif // CANVAS_H
