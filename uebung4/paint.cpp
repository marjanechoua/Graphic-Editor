#include "paint.h"
#include "canvas.h"

#include <QLabel>
#include <QColorDialog>
#include <QGridLayout>
#include <QCheckBox>
#include <QDebug>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>

Paint::Paint(QWidget *parent)
    : QWidget(parent), currentColor(Qt::black)
{
    viewport = new Canvas(this);
    btnClearCanvas = new QPushButton("Clear Canvas", this);



    cobPrimModes = new QComboBox(this);
    cobPrimModes->addItem(tr("None"), static_cast<int>(Canvas::PrimitiveMode::NONE));
    cobPrimModes->addItem(tr("Line"), static_cast<int>(Canvas::PrimitiveMode::LINE));
    cobPrimModes->addItem(tr("Freehand"), static_cast<int>(Canvas::PrimitiveMode::FREE_HAND));
    cobPrimModes->addItem(tr("Circle"), static_cast<int>(Canvas::PrimitiveMode::CIRCLE));
    cobPrimModes->addItem(tr("Rectangle"), static_cast<int>(Canvas::PrimitiveMode::RECTANGLE));
    cobPrimModes->addItem(tr("Triangle"), static_cast<int>(Canvas::PrimitiveMode::TRIANGLE));
    cobPrimModes->addItem(tr("Polygon"), static_cast<int>(Canvas::PrimitiveMode::POLYGON));

    lblPrimModes = new QLabel("Primitive Mode", this);
    lblPrimModes->setBuddy(cobPrimModes);

    cbOutline = new QCheckBox("Show Only Outline", this);

    btnChangeCol = new QPushButton("Set Color");

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(btnChangeCol,   1, 1);
    mainLayout->addWidget(viewport, 0, 0, 1, 4);
    mainLayout->addWidget(cbOutline, 1, 0, Qt::AlignLeft);
    mainLayout->addWidget(lblPrimModes, 1, 2, Qt::AlignRight);
    mainLayout->addWidget(cobPrimModes, 1, 3);
    mainLayout->addWidget(btnClearCanvas, 2, 3);

    QGroupBox* interactionModeGroup = new QGroupBox("Selection Tools", this);
    QVBoxLayout* interactionModeLayout = new QVBoxLayout(interactionModeGroup);

    QRadioButton* createRadio = new QRadioButton("Create objects", interactionModeGroup);
    QRadioButton* deleteRadio = new QRadioButton("Delete selected", interactionModeGroup);
    QRadioButton* colorRadio = new QRadioButton("Change Color", interactionModeGroup);
    QRadioButton* transformRadio = new QRadioButton("Move object", interactionModeGroup);

    interactionModeLayout->addWidget(createRadio);
    interactionModeLayout->addWidget(deleteRadio);
    interactionModeLayout->addWidget(colorRadio);
    interactionModeLayout->addWidget(transformRadio);

    QButtonGroup* interactionModeButtonGroup = new QButtonGroup(this);
    interactionModeButtonGroup->addButton(createRadio, static_cast<int>(Canvas::InteractionMode::CREAT));
    interactionModeButtonGroup->addButton(deleteRadio, static_cast<int>(Canvas::InteractionMode::DEL));
    interactionModeButtonGroup->addButton(colorRadio, static_cast<int>(Canvas::InteractionMode::COL));
    interactionModeButtonGroup->addButton(transformRadio, static_cast<int>(Canvas::InteractionMode::TRAFO));

    mainLayout->addWidget(interactionModeGroup, 3, 0, 1, 4);

    connect(btnClearCanvas, &QPushButton::clicked, this, &Paint::clearBtnPressed);
    connect(btnChangeCol, SIGNAL(clicked()),
            this, SLOT(colorBtnPressed()));

    connect(cobPrimModes, QOverload<int>::of(&QComboBox::activated), this, &Paint::primModeChanged);
    connect(cbOutline, &QCheckBox::toggled, this, &Paint::showOutlineOnly);
    connect(interactionModeButtonGroup, QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked),
            this, [this, interactionModeButtonGroup](QAbstractButton *button) {
                int id = interactionModeButtonGroup->id(button);
                this->interactionModeChanged(id);
            });
    createRadio->setChecked(true);  // Set default mode to CREAT
}

Paint::~Paint()
{
}

void Paint::clearBtnPressed()
{
    viewport->clearCanvas();
    update();
    qDebug() << "Clear image called";
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

void Paint::interactionModeChanged(int mode)
{
    qDebug() << "Interaction mode changed to:" << mode;
    viewport->setInteractionMode(static_cast<Canvas::InteractionMode>(mode));



}

void Paint::colorBtnPressed()
{
    QColor color = QColorDialog::getColor(Qt::blue, this);
    if (color.isValid()) {
        qDebug() << "Color choosen : " << color.name();
        viewport->setObjColor(color);
    }
}
