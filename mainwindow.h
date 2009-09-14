#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtCore/QSettings>
#include <QtGui>
#include "tfile.h"
#include "scanthread.h"
#include "progresswidget.h"
#include "deletelist.h"
#include "common.h"
#include "optionsdialog.h"
#include "global.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

	bool followSymLinks;
	QStringList dirs;
    QSet <QString> W;
	QString defaultDir;
	QSet <TFile*> files;
	QDir *dir;
	qint32 blockSize;
	ScanThread *sThread;

	QMenu *fileMenu;
	QAction *openDirAct;
	QAction *addDirAct;
	QAction *exitAct;

	QMenu *optionsMenu;
	QAction *recursive;
	QAction *hiddenFilesAct;
	QAction *compareNamesAct;
	QAction *settingsAct;

	QMenu *actionsMenu;
	QAction *scanAct;
	QAction *removeSelectedAct;
	QAction *removeAllAct;

	QMenu *viewMenu;
	QAction *showOnlyDupAct;
	QMenu *toolBarMenu;
	QAction *showToolIconsAct;
	QAction *toolTextBesideAct;
	QAction *toolTextUnderAct;
	QMenu *transMenu;
	QAction *transEnAct;
	QAction *transRuAct;

	QMenu *helpMenu;
	QAction *aboutThisAct;
	QAction *aboutQtAct;

	QToolBar *toolBar;

	QIcon directoryIcon;
	QLineEdit *dirEdit;
	QPushButton *openDirButton;
	QTreeWidget *filList;
	QTreeWidget *dupList;
	QSplitter *splitter;

	QTranslator *trans;

	QWidget *central;
	ProgressWidget *progress;
	DeleteList *listToDelete;

	void dfsDir(QTreeWidgetItem *parent=NULL);
	void removeCopiesDialog(const QSet <QSet <TFile*> * > & filesWithCopies);
private:
	void createWidgets();
        void createActions();
	void saveSettings();
	void changeEvent(QEvent *event);
	void closeEvent(QCloseEvent *event);
private slots:
        void loadSettings();
	void selectionChanged();
	void readDirEntry();
	void refreshFiles();
	void aboutThis();
	void setEnglish();
	void setRussian();
	void setToolSettings();
	void settings();
public slots:
	void openDir();
	void addDir();
	void scan();
	void scanFinished();
	void showOnlyDup();
	void removeSelectedCopies();
	void removeAllCopies();
	void terminateThread();
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
