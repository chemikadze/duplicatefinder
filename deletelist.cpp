#include "deletelist.h"

DeleteList::DeleteList()
{
	QGridLayout *la=new QGridLayout;
	setWindowTitle(tr("Choose files..."));
	lbl=new QLabel(tr("Choose which files to delete and which files to save by double-clicking them. Green files will be saved."));
	lbl->setWordWrap(true);
	okIcon=QIcon(":/icons/dialog-ok-apply.png");
	cancelIcon=QIcon(":/icons/dialog-cancel.png");
	toDelete=new DeleteTreeWidget;
	okBtn=new QPushButton(okIcon, tr("Ok"));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(deleteFiles()));
	cancelBtn=new QPushButton(cancelIcon, tr("Cancel"));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(cancelDelete()));

	la->addWidget(lbl, 0, 0, 1, 4);
	la->addWidget(toDelete, 1, 0, 1, 4);
	la->addWidget(okBtn, 2, 2);
	la->addWidget(cancelBtn, 2, 3);
	la->setColumnStretch(0, 1);
	la->setColumnStretch(1, 1);
	la->setColumnStretch(2, 0);
	la->setColumnStretch(3, 0);
	setLayout(la);

	connect(toDelete, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(checkItem(QTreeWidgetItem*,int)));
	connect(toDelete, SIGNAL(sigCheckItem(QTreeWidgetItem*,bool)), this, SLOT(checkItem(QTreeWidgetItem*,bool)));
}

DeleteList::~DeleteList()
{
	Common::clearTreeWidget(toDelete);
}

void DeleteList::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		setWindowTitle(tr("Choose files..."));
		lbl->setText(tr("Choose which files to delete and which files to save by double-clicking them. Green files will be saved."));
		okBtn->setText(tr("Ok"));
		cancelBtn->setText(tr("Cancel"));
	}
	else
	{
		QWidget::changeEvent(event);
	}
}

void DeleteList::deleteFiles()
{
	accept();
}

void DeleteList::cancelDelete()
{
	reject();
}

void DeleteList::setFilesWithCopies(const QSet <QSet <TFile*> * >& new_files)  /// QVector <QSet* <TFile*> >   !!!!!!!!!!!!!
 {
	QTreeWidgetItem *prnt, *item;
	foreach (QSet <TFile*> *set, new_files)
	{
		prnt=new QTreeWidgetItem;
		prnt->setData(0, Qt::DisplayRole, tr("%1 - %2 items").arg((*(set->begin()))->name, QString::number(set->size())));
		prnt->setData(1, Qt::DisplayRole,(*(set->begin()))->size);
		foreach (TFile* fil, *set)
		{
			item=new QTreeWidgetItem;
			item->setData(0, Qt::DecorationRole, toDelete->deleteIcon);
			item->setData(0, Qt::DisplayRole, fil->name);
			item->setData(1, Qt::DisplayRole, fil->size);
			item->setData(2, Qt::DisplayRole, fil->fullName);
			item->setData(0, Qt::UserRole, QVariant::fromValue((void*)fil));
			files.insert(fil);
			prnt->addChild(item);
		}
		files.remove(*(set->begin()));
		prnt->child(0)->setData(0, Qt::DecorationRole, QVariant(toDelete->leaveIcon));
		toDelete->addTopLevelItem(prnt);
	}
}

void DeleteList::checkItem(QTreeWidgetItem *item, int column)
{
	Q_UNUSED(column)
	TFile *f=(TFile*)(item->data(0, Qt::UserRole).value<void*>());
	if (f==NULL)
		return;
	if (files.contains(f))
	{
		files.remove(f);
		item->setData(0, Qt::DecorationRole, toDelete->leaveIcon);
	}
	else
	{
		files.insert(f);
		item->setData(0, Qt::DecorationRole, toDelete->deleteIcon);
	}
}

void DeleteList::checkItem(QTreeWidgetItem *item, bool b)
{
	TFile *f=(TFile*)(item->data(0, Qt::UserRole).value<void*>());
	if (f==NULL)
		return;
	if (b)
	{
		if (files.contains(f))
		{
			files.remove(f);
			item->setData(0, Qt::DecorationRole, toDelete->leaveIcon);
		}
	}
	else
	{
		if (!files.contains(f))
		{
			files.insert(f);
			item->setData(0, Qt::DecorationRole, toDelete->deleteIcon);
		}
	}
}

QSet <TFile*> DeleteList::getFiles()
{
	return files;
}
