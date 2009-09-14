#ifndef DELETELIST_H
#define DELETELIST_H

#include <QtGui>
#include <QtCore>
#include "tfile.h"
#include "common.h"
#include "deletetreewidget.h"
#include "global.h"

class DeleteList : public QDialog
{
	Q_OBJECT

	enum State {No=0, Leave=1, Delete=2};

	QIcon cancelIcon, okIcon;
	QLabel *lbl;
	DeleteTreeWidget *toDelete;
	QPushButton *okBtn;
	QPushButton *cancelBtn;
	QSet <TFile*> files;
private:
	void changeEvent(QEvent*);
private slots:
	void deleteFiles();
	void cancelDelete();
	void checkItem(QTreeWidgetItem*,bool);
	void checkItem( QTreeWidgetItem * item, int column );
public:
	void setFilesWithCopies(const QSet <QSet <TFile*> * >& new_files);
	QSet <TFile*> getFiles();
	DeleteList();
	~DeleteList();
};

#endif // DELETELIST_H
