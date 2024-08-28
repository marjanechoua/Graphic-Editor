#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QColor>

class Canvas;
class QPushButton;
class QComboBox;
class QLabel;
class QCheckBox;
class QButtonGroup;

class Paint : public QWidget
{
    Q_OBJECT

public:
    Paint(QWidget *parent = nullptr);
    ~Paint();

private slots:
    void clearBtnPressed();
    void showOutlineOnly(bool outline);
    void primModeChanged(int index);
    void colorBtnPressed();
    void interactionModeChanged(int mode);

private:
    Canvas *viewport;
    QPushButton *btnClearCanvas;
    QPushButton *btnChangeCol;
    QComboBox *cobPrimModes;
    QLabel *lblPrimModes;
    QCheckBox *cbOutline;
    QColor currentColor;
    QButtonGroup *interactionModeButtonGroup;


};

#endif // PAINT_H
