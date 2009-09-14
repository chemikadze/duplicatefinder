#ifndef TFILE_H
#define TFILE_H

#include <QtGlobal>
#include <QString>
#include <QSet>
#include <QDateTime>
#include <QtGui/QTreeWidgetItem>
#include "global.h"

typedef struct SFile
{
	qint64 size;
	QString name;
	QString fullName;
	QSet <struct SFile*> *duplicates;
	QDateTime created;
	QTreeWidgetItem *item;
} TFile;

#endif // TFILE_H
