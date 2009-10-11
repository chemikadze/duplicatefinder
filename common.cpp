#include "common.h"
#include <QDebug>

namespace Common
{
	void dfsRemoveItems(QTreeWidgetItem *parent)
	{
		foreach (QTreeWidgetItem* item, parent->takeChildren())
		{
			if (item->childCount())
				dfsRemoveItems(item);
			else
				delete item;
		}
		delete parent;
	}

	void clearTreeWidget(QTreeWidget *tree)
	{
		while (tree->topLevelItemCount())
			dfsRemoveItems(tree->takeTopLevelItem(0));
	}
}
