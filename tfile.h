#ifndef TFILE_H
#define TFILE_H

#include <QtGlobal>
#include <QString>
#include <QSet>
#include <QDateTime>
#include <QtGui/QTreeWidgetItem>
#include <QDebug>
#include "global.h"

class TFile
{
public:
	qint64 size;
	QString name;
	QString fullName;
	QSet <TFile*> *duplicates;
	QDateTime created;
	QTreeWidgetItem *item;
	TFile() {}
};


#endif // TFILE_H
