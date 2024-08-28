#include "canvas.h"
#include "line.h"
#include "circle.h"
#include "rectangle.h"
#include "freeform.h"

#include <QMouseEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QFrame(parent), dragging(false),type(NONE), currentColor(Qt::black), fillMode(false)
{
	setFrameStyle(QFrame::Box);
	setMouseTracking(true);
    dragging=false;



    scene = new Scene();


}

Canvas::~Canvas()

{
    delete scene;
    // TODO; clean-up
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
	// TODO
    scene->clearObjects();
    update();
}

void Canvas::setPrimitiveMode( int mode)
{
    type = static_cast<PrimitiveMode>(mode);
}

void Canvas::setObjColor(const QColor &col)
{
    currentColor=col;
}

void Canvas::setFillMode(bool filled)
{
    fillMode = filled;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);  // parent class draws border

    QPainter painter(this);

    // white background (inside parent's border)
    painter.fillRect(QRect(1, 1, width() - 2, height() - 2), Qt::white);

    // Zeichne alle Objekte aus der Scene
    scene->display(&painter);

    //Zeichne die Rubber-Band-Visualisierung
        if (dragging) {
        painter.setPen(QPen(currentColor, 2, Qt::DashLine));
        switch (type) {
        case LINE:
            painter.drawLine(lineStartPoint, lineEndPoint);
            break;
        case CIRCLE:{

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
        default:
            break;
        }
    }



}

void Canvas::resizeEvent(QResizeEvent *event) 
{
	QFrame::resizeEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragging = true;

        lineStartPoint=event->pos();
        lineEndPoint=lineStartPoint;
        if (type==FREE_HAND){

            freehandPoints.clear();
            freehandPoints.append(lineStartPoint);
        }

		update();
        }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && dragging) {
        lineEndPoint = event->pos();

        if (type == FREE_HAND) {
            freehandPoints.append(lineEndPoint);
        }

        update();
    }
}


void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && dragging) {
        dragging = false;
        lineEndPoint=event->pos();


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
        }
        break;
        case RECTANGLE:
        {
            QRect rect= QRect(lineStartPoint, lineEndPoint).normalized();
            if (!rect.isNull() && rect.width() > 2 && rect.height() > 2) {
                scene->insert(new Rectangle(rect.topLeft(), rect.width(), rect.height(), currentColor, fillMode));
                break;
        }
        }

        case FREE_HAND:
            if (freehandPoints.size() > 1) {
                std::vector<QPoint> points(freehandPoints.begin(), freehandPoints.end());
                scene->insert(new Freeform(points, currentColor));
            }
            break;
        default:
            break;

        }


		update();
	}

}

