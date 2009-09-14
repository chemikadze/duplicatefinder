#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#include <QtCore/QThread>
#include <QtCore/QVector>
#include <QtCore/QSet>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QByteArray>
#include <QtGui/QTreeWidgetItem>
#include "tfile.h"
#include "global.h"

class ScanThread : public QThread
{
	Q_OBJECT

protected:
	qint32 blockSize;

	bool compareNames;
	QSet <TFile*> *files;
	QTreeWidgetItem* item;
	QFile fi, fj;
	QByteArray arri, arrj;
	char* datai, *dataj;
	QSet<TFile*>::iterator i, j;
	int N, k;

	virtual void run();
signals:
	void processingFile(const QString&);
	void finished();
public:
	void setCompareNames(bool b);
	void closeFiles();
	void setFiles(QSet <TFile*> *f);
	void setBlockSize(qint32 size);
    ScanThread();
};

#endif // SCANTHREAD_H
