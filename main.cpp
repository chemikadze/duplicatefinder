#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	a.setOrganizationName("Chemikadze");
	a.setApplicationName("DuplicateFinder");

	MainWindow *w=new MainWindow();
	w->resize(800, 600);
	w->show();
	return a.exec();
}
