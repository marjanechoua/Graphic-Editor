#include <QApplication>
#include "paint.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	Paint w;
	w.show();
	return app.exec();
}


//ich kann eine linie zeichnen und die farbe ändern,
//bei freehand zeichnet sich iregndwie ein kreis ich weiß auch nicht warum,
//beim kreis wiederum wird eine linie gezeichnet anstatt ein kreis,
//beim rectangle funktioniert nichts wenn ich es auswähle.
//wenn ich triangle auswähle zeichnet sich ein rectangle
