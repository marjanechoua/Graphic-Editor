#include <QPushButton> 
#include <QComboBox>
#include <QLabel>
#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include "paint.h"
#include "canvas.h"

/** c'tor */
Paint::Paint(QWidget *parent)
	: QWidget(parent)
{
    // instantiate Canvas along with buttons and stuff
	viewport = new Canvas();

	btnClearCanvas = new QPushButton("&Clear Canvas");

    cobPrimModes = new QComboBox();
    cobPrimModes->addItem(tr("None"),      Canvas::NONE);
    cobPrimModes->addItem(tr("Line"),      Canvas::LINE);
    cobPrimModes->addItem(tr("Freehand"),  Canvas::FREE_HAND);
    cobPrimModes->addItem(tr("Circle"),    Canvas::CIRCLE);
    cobPrimModes->addItem(tr("Rectangle"), Canvas::RECTANGLE);
    cobPrimModes->addItem(tr("Triangle"),  Canvas::TRIANGLE);
    cobPrimModes->addItem(tr("Polygon"),   Canvas::POLYGON);

	lblPrimModes = new QLabel("Primitive Mode");
	lblPrimModes->setBuddy(cobPrimModes);

    btnDeleteObj = new QPushButton("&Delete Selected");

    btnChangeCol = new QPushButton("C&hange Color");
    cbOutline = new QCheckBox("Show Only &Outline");

	// create layout and add gui elements to it
	QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(viewport,       0, 0, 1, 4);
    mainLayout->addWidget(btnChangeCol,   1, 0);
    mainLayout->addWidget(cbOutline,      1, 1, Qt::AlignLeft);
    mainLayout->addWidget(lblPrimModes,   1, 2, Qt::AlignRight);
    mainLayout->addWidget(cobPrimModes,   1, 3);
    mainLayout->addWidget(btnDeleteObj,   2, 0);
    mainLayout->addWidget(btnClearCanvas, 2, 3);

	// add layout to this widget instance
	setLayout(mainLayout);
	
    // connect button click event to clear canvas handler
    connect(btnClearCanvas, SIGNAL(clicked()),
            this, SLOT(clearBtnPressed()));
    // connect button click event to delete selected object handler
    connect(btnDeleteObj, SIGNAL(clicked()),
            this, SLOT(deleteBtnPressed()));
    // connect button click event to color chooser handler
    connect(btnChangeCol, SIGNAL(clicked()),
            this, SLOT(colorBtnPressed()));
    // connect list-/combobox to primitive changed event handler
    connect(cobPrimModes, SIGNAL(activated(int)),
            this, SLOT(primModeChanged(int)));
    // connect checkbox to toggle outline event handler
    connect(cbOutline, SIGNAL(toggled(bool)),
            this, SLOT(showOutlineOnly(bool)));
}

/** d'tor */
Paint::~Paint()
{

}

/** method for handling button clicked event */
void Paint::clearBtnPressed()
{
	viewport->clearCanvas();

	// force redraw
	update();
    qDebug() << "Clear image called";
}

void Paint::deleteBtnPressed()
{
    // Implementation requires inside test for all objects for selection
    qDebug() << "Next action: delete selected item (NYI)";
}

void Paint::colorBtnPressed()
{
    QColor color = QColorDialog::getColor(Qt::blue, this);
    if (color.isValid()) {
        qDebug() << "Color choosen : " << color.name();
        viewport->setObjColor(color);
    }
}

void Paint::showOutlineOnly(bool outline)

{
    qDebug() << "Only show outline: " << outline;
    viewport->setFillMode(!outline);
}

void Paint::primModeChanged(int index)
{
    int mode = cobPrimModes->itemData(index).toInt();
    viewport->setPrimitiveMode(mode);
    qDebug() << "Primitive Mode changed to " << mode;
}
