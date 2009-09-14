#include "scanthread.h"
#include <QDebug>

ScanThread::ScanThread()
{
	setTerminationEnabled(true);
}

void ScanThread::run()
{
	for (i=files->begin(); i!=files->end(); ++i)
	{
		if ((*i)->duplicates != NULL)
		{
			QSet <TFile*> *dup=(*i)->duplicates;
			foreach (TFile* fil, *dup)
			{
				fil->duplicates=NULL;
			}
			delete dup;
		}
		fi.setFileName((*i)->fullName);
		emit processingFile((*i)->name);
		if (!fi.open(QIODevice::ReadOnly))	// message box?
			continue;
		for (j=files->begin(); i!=j; ++j)
		{
			// diff
			if ( compareNames && ((*i)->name == (*j)->name) )
			{
				if ((*j)->duplicates == NULL)
				{
					(*j)->duplicates=new QSet<TFile*>;
				}
				(*j)->duplicates->insert(*j);
				(*j)->duplicates->insert(*i);
				(*i)->duplicates=(*j)->duplicates;
				continue;
			}

			if ((*i)->size != (*j)->size)
			{
				fj.close();
				continue;
			}
			fj.setFileName((*j)->fullName);

			QFileInfo fii(fi), fij(fj);
			if (fii.canonicalFilePath() == fij.canonicalFilePath())
			{
				if ((*j)->duplicates == NULL)
				{
					(*j)->duplicates=new QSet<TFile*>;
				}
				(*j)->duplicates->insert(*j);
				(*j)->duplicates->insert(*i);
				(*i)->duplicates=(*j)->duplicates;
				continue;
			}

			if (!fj.open(QIODevice::ReadOnly))	// message box?
				continue;
			fi.seek(0);
			fj.seek(0);

			arri=fi.read(blockSize);
			arrj=fj.read(blockSize);
			do
			{
				datai=arri.data();
				dataj=arrj.data();
				N=qMax(arri.size(), arrj.size())/sizeof(int);
				for (k=0; k < N; k++)
					if ( ((int*)datai)[k] !=  ((int*)dataj)[k] )
						break;
				if (k-- != N)
					break;
				for (k*=4; k<arri.size(); k++)
					if (datai[k] != dataj[k])
						break;
				arri=fi.read(blockSize);
				arrj=fj.read(blockSize);
			}
			while(arri.size()>0 && arrj.size()>0);
			if ( (!(arri.size()>0 && arrj.size()>0)) )
			{
				if ((*j)->duplicates == NULL)
				{
					(*j)->duplicates=new QSet<TFile*>;
				}
				(*j)->duplicates->insert(*j);
				(*j)->duplicates->insert(*i);
				(*i)->duplicates=(*j)->duplicates;
			}
			fj.close();
		}
		fi.close();
	}
	emit finished();
	exec();
}

void ScanThread::closeFiles()
{
	if (fi.isOpen())
		fi.close();
	if (fj.isOpen())
		fi.close();
	arri.clear();
	arrj.clear();
}

void ScanThread::setFiles(QSet <TFile*> *f)
{
	files=f;
}

void ScanThread::setBlockSize(qint32 size)
{
	blockSize=size;
}

void ScanThread::setCompareNames(bool b)
{
	compareNames=b;
}
