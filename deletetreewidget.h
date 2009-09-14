#ifndef DELETETREEWIDGET_H
#define DELETETREEWIDGET_H
/*
#include <QtGui/QTreeWidget>
#include <QtGui/QMenu>
#include <QtGui/QAction>
*/
#include <QtGui>
#include "global.h"

class DeleteTreeWidget : public QTreeWidget
{
	Q_OBJECT

	QMenu *popupMenu;
	QAction *leaveAct;
	QAction *deleteAct;
	QAction *leaveAllCopiesAct;
	QAction *deleteAllCopiesAct;
	QAction *leaveAllAct;
	QAction *deleteAllAct;
	QAction *expandAll;
	QAction *collapseAll;
	QTreeWidgetItem *currItem;
private:
	void changeEvent(QEvent*);
private slots:
	void slotSingleCheck();
	void slotGroupCheck();
	void showContextMenu(const QPoint &pos);
signals:
	void sigCheckItem(QTreeWidgetItem *item, bool b);
public:
	QIcon leaveIcon, deleteIcon;
    DeleteTreeWidget();
};

#endif // DELETETREEWIDGET_H
