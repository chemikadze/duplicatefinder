#ifndef PROGRESSWIDGET_H
#define PROGRESSWIDGET_H

#include <QtGui/QLabel>
#include <QtGui/QDialog>
#include <QtGui/QPushButton>
#include <QtGui/QProgressBar>
#include <QtGui/QGridLayout>
#include <QtGui/QCloseEvent>
#include <QtCore/QString>
#include <QtCore/QSize>
#include "global.h"

class ProgressWidget : public QDialog
{
	Q_OBJECT

protected:
	QLabel		 *label;
	QProgressBar *progBar;
	QPushButton  *stopBtn;
	QString format;

	void changeEvent(QEvent*);
	void closeEvent(QCloseEvent *event);
protected slots:
	void slotStop();
signals:
	void stop();
public slots:
	void setValue(int);
	void setCount(int);
	void step();
	void sudoClose();
	void setCurrentFileName(const QString&);
public:
	void setStopEnabled(bool);
    ProgressWidget();
};

#endif // PROGRESSWIDGET_H
