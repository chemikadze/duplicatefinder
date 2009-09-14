#include "deletetreewidget.h"

DeleteTreeWidget::DeleteTreeWidget()
{
	QStringList headers;
	headers << tr("Filename")
			<< tr("Size")
			<< tr("Full path");
	setHeaderLabels(headers);
	setColumnWidth(0, 200);
	popupMenu=new QMenu(this);
	deleteIcon=QIcon(":/icons/edit-delete.png");
	leaveIcon=QIcon(":/icons/list-add.png");
	setSelectionMode(QAbstractItemView::ExtendedSelection);
	leaveAct=popupMenu->addAction(leaveIcon, tr("Leave"), this, SLOT(slotSingleCheck()));
	deleteAct=popupMenu->addAction(deleteIcon, tr("Delete"), this, SLOT(slotSingleCheck()));
	popupMenu->addSeparator();
	leaveAllCopiesAct=popupMenu->addAction(tr("Leave all copies"), this, SLOT(slotGroupCheck()));
	deleteAllCopiesAct=popupMenu->addAction(tr("Delete all copies"), this, SLOT(slotGroupCheck()));
	popupMenu->addSeparator();
	leaveAllAct=popupMenu->addAction(tr("Leave all"), this, SLOT(slotGroupCheck()));
	deleteAllAct=popupMenu->addAction(tr("Delete all"), this, SLOT(slotGroupCheck()));
	popupMenu->addSeparator();
	expandAll=popupMenu->addAction(tr("Expand all"), this, SLOT(expandAll()));
	collapseAll=popupMenu->addAction(tr("Collapse all"), this, SLOT(collapseAll()));
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
}

void DeleteTreeWidget::changeEvent(QEvent *event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		QStringList headers;
		headers << tr("Filename")
				<< tr("Size")
				<< tr("Full path");
		setHeaderLabels(headers);
		leaveAct->setText(tr("Leave"));
		deleteAct->setText(tr("Delete"));
		leaveAllCopiesAct->setText(tr("Leave all copies"));
		deleteAllCopiesAct->setText(tr("Delete all copies"));
		leaveAllAct->setText(tr("Leave all"));
		deleteAllAct->setText(tr("Delete all"));
		expandAll->setText(tr("Expand all"));
		collapseAll->setText(tr("Collapse all"));
	}
	else
		QWidget::changeEvent(event);
}

void DeleteTreeWidget::showContextMenu (const QPoint &pos)
{
	currItem=itemAt(pos);
	if (currItem == NULL) 
		return;
	leaveAct->setEnabled(currItem->parent() != NULL);
	deleteAct->setEnabled(currItem->parent() != NULL);
	popupMenu->popup(mapToGlobal(pos));
}

void DeleteTreeWidget::slotSingleCheck()
{
	if (currItem == NULL)
		return;
	foreach (QTreeWidgetItem *item, this->selectedItems())
	{
		if (item->parent()==NULL)
			continue;
		if (sender()==leaveAct)
			emit sigCheckItem(item, true);
		if (sender()==deleteAct)
			emit sigCheckItem(item, false);
	}

}

void DeleteTreeWidget::slotGroupCheck()
{
	if (currItem == NULL) 
		return;
	if (currItem->parent() != NULL)
		currItem=currItem->parent();
	if (sender()==leaveAllCopiesAct || sender()==deleteAllCopiesAct)
		for (int i=0; i<currItem->childCount(); i++)
		{
			if (sender()==leaveAllCopiesAct)
				emit sigCheckItem(currItem->child(i), true);
			if (sender()==deleteAllCopiesAct)
				emit sigCheckItem(currItem->child(i), false);
		}
	else if (sender()==leaveAllAct || sender()==deleteAllAct)
		for (int i=0; i<topLevelItemCount(); i++)
		{
			currItem=topLevelItem(i);
			for (int j=0; j<currItem->childCount(); j++)
			{
				if (sender()==leaveAllAct)
					emit sigCheckItem(currItem->child(j), true);
				if (sender()==deleteAllAct)
					emit sigCheckItem(currItem->child(j), false);
			}
		}
}
