#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose, true);

	blockSize=1024*64;
	trans=NULL;

	qApp->setWindowIcon(QIcon(":/icons/icon.png"));
	qApp->setApplicationName("DuplicateFinder");
	directoryIcon=QIcon(":/icons/inode-directory.png");

	createWidgets();
	createActions();

	dir=new QDir(QDir::home());
	sThread=new ScanThread;
	sThread->setBlockSize(blockSize);
	sThread->setFiles(&files);
	progress=new ProgressWidget;
	progress->resize(365, 0);
	progress->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);
	connect(sThread, SIGNAL(processingFile(const QString&)), progress, SLOT(setCurrentFileName(const QString&)));
	connect(sThread, SIGNAL(finished()), this, SLOT(scanFinished()));
	connect(sThread, SIGNAL(terminated()), this, SLOT(scanFinished()));
	connect(progress, SIGNAL(stop()), this, SLOT(terminateThread()));

	QGridLayout *la=new QGridLayout(central);
	QHBoxLayout *hla=new QHBoxLayout();
	hla->addWidget(dirEdit);
	hla->addWidget(openDirButton);
	splitter->setOrientation(Qt::Vertical);
	splitter->addWidget(filList);
	splitter->addWidget(dupList);
	splitter->setStretchFactor(0, 3);
	splitter->setStretchFactor(1, 1);
	la->addLayout(hla, 0, 0, 1, 4);
	la->addWidget(splitter, 1, 0, 1, 4);
	central->setLayout(la);
	setCentralWidget(central);

	loadSettings();
	dirEdit->setText(dir->absolutePath());
}

void MainWindow::createWidgets()
{
	QStringList headers;
	central=new QWidget(this);
	headers << tr("Filename")
			<< tr("Duplicates")
			<< tr("Size")
			<< tr("Creation date")
			<< tr("Full path");

	splitter=new QSplitter();

	filList=new QTreeWidget();
	filList->setHeaderLabels(headers);
	filList->setColumnWidth(0, 200);
	filList->setSortingEnabled(true);
	filList->sortItems(0, Qt::AscendingOrder);
	filList->setSelectionMode(QAbstractItemView::ExtendedSelection);
	connect(filList, SIGNAL(itemSelectionChanged()), this, SLOT(selectionChanged()));
	headers.clear();
	headers << tr("Filename")
			<< tr("Full path");

	dupList=new QTreeWidget();
	dupList->setHeaderLabels(headers);
	dupList->setColumnWidth(0, 170);
	dupList->setSortingEnabled(true);

	dirEdit=new QLineEdit();
	dirEdit->setReadOnly(true);

	sBar=this->statusBar();

	openDirButton=new QPushButton(QIcon(":/icons/document-open-folder.png"), tr("Open..."));
	connect(openDirButton, SIGNAL(clicked()), this, SLOT(openDir()));
}

void MainWindow::createActions()
{
	fileMenu=menuBar()->addMenu(tr("File"));
	openDirAct=fileMenu->addAction(openDirButton->icon(), tr("Open dir..."), this, SLOT(openDir()));
	addDirAct=fileMenu->addAction(QIcon(":/icons/list-add.png"), tr("Add dir..."), this, SLOT(addDir()));
	fileMenu->addSeparator();
	exitAct=fileMenu->addAction(QIcon(":/icons/application-exit.png"), tr("Exit"), this, SLOT(close()));

	optionsMenu=menuBar()->addMenu(tr("Options"));
	recursive=optionsMenu->addAction(tr("Recursively"), this, SLOT(readDirEntry()));
	recursive->setCheckable(true);
	hiddenFilesAct=optionsMenu->addAction(tr("Look in hidden files"), this, SLOT(readDirEntry()));
	hiddenFilesAct->setCheckable(true);
	compareNamesAct=optionsMenu->addAction(tr("Compare filenames"));
	compareNamesAct->setCheckable(true);
	optionsMenu->addSeparator();
	settingsAct=optionsMenu->addAction(tr("Settings"), this, SLOT(settings()));

	actionsMenu=menuBar()->addMenu(tr("Actions"));
	scanAct=actionsMenu->addAction(QIcon(":/icons/view-refresh.png"), tr("Scan"), this, SLOT(scan()));
	removeSelectedAct=actionsMenu->addAction(tr("Remove selected"), this, SLOT(removeSelectedCopies()));
	removeAllAct=actionsMenu->addAction(QIcon(":/icons/edit-clear.png"), tr("Remove copies"), this, SLOT(removeAllCopies()));

	viewMenu=menuBar()->addMenu(tr("View"));
	showOnlyDupAct=viewMenu->addAction(tr("Only duplicated"), this, SLOT(showOnlyDup()));
	showOnlyDupAct->setCheckable(true);
	toolBarMenu=viewMenu->addMenu(tr("Toolbar"));
	showToolIconsAct=toolBarMenu->addAction(tr("Show icons"), this, SLOT(setToolSettings()));
	showToolIconsAct->setCheckable(true);
	toolBarMenu->addSeparator();
	toolTextBesideAct=toolBarMenu->addAction(tr("Text beside icons"), this, SLOT(setToolSettings()));
	toolTextBesideAct->setCheckable(true);
	toolTextUnderAct=toolBarMenu->addAction(tr("Text under icons"), this, SLOT(setToolSettings()));
	toolTextUnderAct->setCheckable(true);
	QActionGroup *group=new QActionGroup(this);
	group->addAction(toolTextBesideAct);
	group->addAction(toolTextUnderAct);
	group->setExclusive(true);
	transMenu=viewMenu->addMenu(tr("Language"));
	transEnAct=transMenu->addAction(tr("English"), this, SLOT(setEnglish()));
	transRuAct=transMenu->addAction(tr("Russian"), this, SLOT(setRussian()));
	group=new QActionGroup(this);
	group->addAction(transEnAct);
	group->addAction(transRuAct);
	group->setExclusive(true);
	transEnAct->setCheckable(true);
	transRuAct->setCheckable(true);

	helpMenu=menuBar()->addMenu(tr("Help"));
	aboutThisAct=helpMenu->addAction(QIcon(":/icons/icon.png"), tr("About..."), this, SLOT(aboutThis()));
	aboutQtAct=helpMenu->addAction(QIcon(":/icons/help-about.png"), tr("About Qt..."), qApp, SLOT(aboutQt()));

	toolBar=addToolBar(tr("Main toolbar"));
	toolBar->addAction(openDirAct);
	toolBar->addAction(addDirAct);
	toolBar->addSeparator();
	toolBar->addAction(recursive);
	toolBar->addSeparator();
	toolBar->addAction(scanAct);
	toolBar->addAction(removeSelectedAct);
	toolBar->addAction(removeAllAct);
}

MainWindow::~MainWindow()
{
	delete progress;
	delete sThread;
	delete dir;
	foreach (TFile* file, files)
	{
		if (file->duplicates != NULL)
		{
			file->duplicates->remove(file);
			if (file->duplicates->isEmpty())
				delete file->duplicates;
		}
		files.remove(file);
		delete file;
	}
	Common::clearTreeWidget(filList);
	Common::clearTreeWidget(dupList);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	Q_UNUSED(event)
	saveSettings();
}

void MainWindow::saveSettings()
{
	QSettings *settings=new QSettings(this);
	settings->beginGroup("options");
        settings->setValue("follow_sym_links", followSymLinks);
		settings->setValue("default_dir", defaultDir);
		settings->setValue("recursive", recursive->isChecked());
		settings->setValue("compare_names", compareNamesAct->isChecked());
		settings->value("hidden", hiddenFilesAct->isChecked());
		if (transEnAct->isChecked())
			settings->setValue("language", QString("en"));
		else
			settings->setValue("language", QString("ru"));
	settings->endGroup();
	settings->beginGroup("view");
		settings->setValue("only_dup", showOnlyDupAct->isChecked());
		settings->value("show_tool_icons", showToolIconsAct->isChecked());
		settings->value("tool_beside_under", toolTextBesideAct->isChecked());
	settings->endGroup();
	delete settings;
}

void MainWindow::loadSettings()
{
	QSettings *settings=new QSettings(this);
	settings->beginGroup("options");
        followSymLinks=settings->value("follow_sym_links", false).toBool();
		defaultDir=settings->value("default_dir", dir->absolutePath()).toString();
		if (dirs.size()==0)
			dirs.push_back(defaultDir);
		recursive->setChecked(settings->value("recursive", false).toBool());
		compareNamesAct->setChecked(settings->value("compare_names", false).toBool());
		hiddenFilesAct->setChecked(settings->value("hidden", false).toBool());
		QString language=settings->value("language", QString("en")).toString();
		if (language == "en")
			transEnAct->trigger();
		else if (language == "ru")
			transRuAct->trigger();
	settings->endGroup();
	settings->beginGroup("view");
		showOnlyDupAct->setChecked(settings->value("only_dup", false).toBool());
		showToolIconsAct->setChecked(settings->value("show_tool_icons", true).toBool());
		toolTextBesideAct->setChecked(settings->value("tool_beside_under", true).toBool());
		toolTextUnderAct->setChecked(!toolTextBesideAct->isChecked());
	settings->endGroup();
	delete settings;
	setToolSettings();
	readDirEntry();
}

void MainWindow::openDir()
{
	QFileDialog *dial=new QFileDialog(this);
	dirs.clear();
	dial->setFileMode(QFileDialog::DirectoryOnly);
	dial->setDirectory(dir->absolutePath());
	if (dial->exec())
	{
		dir->cd(dial->selectedFiles().at(0));
		dirs.push_back(dir->absolutePath());
		dirEdit->setText(dir->absolutePath());
		readDirEntry();
	}
	delete dial;
}

void MainWindow::addDir()
{
	QFileDialog *dial=new QFileDialog(this);
	bool ok;
	dial->setFileMode(QFileDialog::DirectoryOnly);
	dial->setDirectory(dir->absolutePath());
	if (dial->exec())
	{
		foreach (QString s, dial->selectedFiles())
		{
			ok=true;
			if (recursive->isChecked())
			{
				foreach(QString si, dirs)
				{
#ifdef Q_WS_WIN
					if (si.contains(s, Qt::CaseInsensitive))
#else
					if (si.contains(s, Qt::CaseSensitive))
#endif
					{
						ok=false;
						QMessageBox::warning(this, tr("Can\'t add dir!"), tr("Directory %1 is subdirectory of %2!").arg(si, s));
						break;
					}
#ifdef Q_WS_WIN
					if (s.contains(si, Qt::CaseInsensitive))
#else
					if (s.contains(si, Qt::CaseSensitive))
#endif
					{
						ok=false;
						QMessageBox::warning(this, tr("Can\'t add dir!"), tr("Directory %1 is subdirectory of %2!").arg(s, si));
						break;
					}
				}
			}
			if (ok)
			{
				dirs.push_back(s);
				dirEdit->setText(dirEdit->text()+QString(" ")+ dir->absolutePath());
			}
		}
		readDirEntry();
	}
	delete dial;
}

void MainWindow::scan()
{
	readDirEntry();
	progress->setCount(files.size());
	progress->setStopEnabled(true);
	progress->show();
	sThread->setCompareNames(compareNamesAct->isChecked());
	sThread->start();
}

void MainWindow::selectionChanged()
{
	QSet <TFile*> showed;
	Common::clearTreeWidget(dupList);
	foreach (QTreeWidgetItem *sItem, filList->selectedItems())
	{
		TFile *f=(TFile*)(sItem->data(0, Qt::UserRole).value<void*>());
		if (f==NULL)
			continue;
		QTreeWidgetItem *item;
		if (f->duplicates==NULL)
			continue;
		foreach (TFile *file, *(f->duplicates))
		{
			if (showed.contains(file))
				continue;
			item=new QTreeWidgetItem;
			item->setData(0, Qt::DisplayRole, file->name);
			item->setData(1, Qt::DisplayRole, file->fullName);
			dupList->addTopLevelItem(item);
			showed.insert(file);
		}
	}
	showed.clear();
}

void MainWindow::readDirEntry()
{
	W.clear();
	bool ok;
	TFile *file;
	setWindowFilePath(dir->absolutePath());
	foreach (file, files)
	{
		if (file->duplicates != NULL)
		{
			file->duplicates->remove(file);
			if (file->duplicates->isEmpty())
				delete file->duplicates;
		}
		files.remove(file);
		delete file;
	}
	//files.clear();
	Common::clearTreeWidget(filList);
	Common::clearTreeWidget(dupList);

	foreach (QString s, dirs)
	{
		ok=true;
		if (recursive->isChecked())
		{
			foreach(QString si, dirs)
			{
				if (s==si)
					continue;
#ifdef Q_WS_WIN
				if (s.contains(si, Qt::CaseInsensitive))
#else
				if (s.contains(si, Qt::CaseSensitive))
#endif
				{
					ok=false;
					QMessageBox::warning(this, tr("Can\'t use dir!"), tr("Directory %1 is subdirectory of %2!").arg(s, si));
					break;
				}
			}
		}
		if (ok)
		{
			dir->cd(s);
			QTime time;
			time.start();
            dfsDir();
			//qDebug() << "Opened in " << time.elapsed() << " msecs";
		}
	}
	filList->expandAll();
	refreshFiles();
	W.clear();
	sBar->showMessage(tr("%1 files found").arg(files.size()));
}

void MainWindow::dfsDir(QTreeWidgetItem *parent/*=NULL*/)
{
	if (W.contains(dir->canonicalPath()))
        return;
    else
		W.insert(dir->canonicalPath());
	//qDebug() << dir->absolutePath();
	TFile *file;
	QTreeWidgetItem *item;

	item=new QTreeWidgetItem(parent);
	item->setData(0, Qt::DisplayRole, dir->dirName());
	item->setData(0, Qt::DecorationRole, directoryIcon);
	if (parent != NULL)
		parent->addChild(item);
	else
		filList->addTopLevelItem(item);
	parent=item;
	foreach (const QFileInfo& fil, dir->entryInfoList(QDir::Files | QDir::Readable | (hiddenFilesAct->isChecked() ? QDir::Hidden : QDir::Readable), QDir::Name))
	{
		file=new TFile;
		file->name=fil.fileName();
		file->fullName=fil.absoluteFilePath();
		file->size=fil.size();
		file->created=fil.created();
		file->duplicates=NULL;
		files.insert(file);

		item=new QTreeWidgetItem(parent);
		item->setData(0, Qt::DisplayRole, file->name);
		item->setData(2, Qt::DisplayRole, file->size);
		item->setData(3, Qt::DisplayRole, fil.created().toString(Qt::SystemLocaleShortDate));
		item->setData(4, Qt::DisplayRole, file->fullName);
		item->setData(0, Qt::UserRole, QVariant::fromValue((void*)file));
		parent->addChild(item);

		file->item=item;
	}
	if (recursive->isChecked())
	{
        QFileInfo info;
		QString pth=dir->absolutePath();
		foreach (const QString &s, dir->entryList(QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot | (hiddenFilesAct->isChecked() ? QDir::Hidden : QDir::Readable), QDir::Name))
		{
			info.setFile(s);
			if ( (info.isSymLink() && followSymLinks) ||  !info.isSymLink() )
			{
				//qDebug() << info.isSymLink();
				dir->cd(s);
                dfsDir(parent);
				dir->cd(pth);
			}
			dir->cd(s);
			//qDebug() << dir->absolutePath() << dir->canonicalPath();
			if ( dir->absolutePath() == dir->canonicalPath() )
			{
				dfsDir(parent);
				dir->cd(pth);
			}
		}
	}
}

void MainWindow::refreshFiles()
{
	bool b=showOnlyDupAct->isChecked();
	foreach (TFile* fil, files)
	{
		if (fil->duplicates!=NULL)
		{
			fil->item->setData(1, Qt::DisplayRole, fil->duplicates->size());
			fil->item->setHidden(false);
		}
		else
		{
			fil->item->setData(1, Qt::DisplayRole, QVariant());
			fil->item->setHidden(b);
		}
	}
}

void MainWindow::scanFinished()
{
	progress->close();
	sThread->exit();
	sThread->closeFiles();
	refreshFiles();
	sBar->showMessage(tr("%1 files processed, %2 duplicated files found").arg(files.size()).arg(sThread->duplicatedFiles()));
}

void MainWindow::removeAllCopies()
{
	QSet <QSet <TFile*> * > filesWithCopies;
	foreach (TFile *f, files)
	{
		if (f->duplicates!=NULL && ! filesWithCopies.contains(f->duplicates))
			filesWithCopies.insert(f->duplicates);
	}
	removeCopiesDialog(filesWithCopies);
}

void MainWindow::removeSelectedCopies()
{
	QSet <QSet <TFile*> * > filesWithCopies;
	TFile *fil;
	foreach (QTreeWidgetItem* item, filList->selectedItems())
	{
		fil=(TFile*)(item->data(0, Qt::UserRole).value<void*>());
		if (fil->duplicates != NULL && (!filesWithCopies.contains(fil->duplicates)))
			filesWithCopies.insert(fil->duplicates);
	}
	removeCopiesDialog(filesWithCopies);
}

void MainWindow::removeCopiesDialog(const QSet <QSet <TFile*> * > & filesWithCopies)
{
	qint64 bytesFreed=0;
	qint32 filesRemoved=0;
	listToDelete=new DeleteList;
	listToDelete->setFilesWithCopies(filesWithCopies);
	if (listToDelete->exec()==QDialog::Accepted)
	{
		QMessageBox::StandardButton butt=QMessageBox::NoButton;
		QSet <TFile*> remFiles=listToDelete->getFiles();
		bool removed;
		progress->setCount(remFiles.size());
		progress->setStopEnabled(false);
		progress->show();
		foreach(TFile* f, remFiles)
		{
			progress->setCurrentFileName(f->name);
#ifdef SAFE_DEBUG
			while ((!(removed=/*QFile::remove(f->fullName)*/true)) && (butt!=QMessageBox::YesToAll))
#else
			while ((!(removed=QFile::remove(f->fullName))) && (butt!=QMessageBox::YesToAll))
#endif
			{
				butt=QMessageBox::warning(this, tr("Error"),
					tr("Can not delete file \"%1\". Skip?").arg(f->fullName),
					QMessageBox::Yes|QMessageBox::YesToAll|
					QMessageBox::Retry|QMessageBox::Cancel);
				if (butt==QMessageBox::Cancel)
				{// Sorry, Edsger Dijkstra, i can't offer to you one "if" and byte, spended on bool
					goto finish;		}
				if (butt!=QMessageBox::Retry)
					break;
			}
			if (removed)
			{
				bytesFreed+=f->size;
				++filesRemoved;
				//qDebug() << tr("Removed") << f->name.toAscii();
				if (f->duplicates==NULL)
				{
					f->duplicates->remove(f);
					if (f->duplicates->size() == 1)
					{
						(*(f->duplicates->begin()))->duplicates=NULL;
						delete f->duplicates;
					}
				}
				f->item->parent()->removeChild(f->item);
				delete f->item;
				files.remove(f);
				delete f;
			}
		}
	finish:		// enough sory
		progress->sudoClose();
		refreshFiles();
		if (filesRemoved)
			QMessageBox::information(this, tr("Finished"),
									 tr("Removed files: %1\nSpace freed: %2 bytes\n Average filesize: %3 bytes")
									 .arg(QString::number(filesRemoved),
										  QString::number(bytesFreed),
										  QString::number(bytesFreed / filesRemoved)));
	}
	Common::clearTreeWidget(dupList);
	delete listToDelete;
}

void MainWindow::showOnlyDup()
{
	if (showOnlyDupAct->isChecked())
	{
		foreach (TFile* fil, files)
		{
			if (fil->duplicates == NULL)
				fil->item->setHidden(true);
		}
	}
	else
	{
		foreach (TFile* fil, files)
		{
			if (fil->duplicates == NULL)
				fil->item->setHidden(false);
		}
	}
}

void MainWindow::aboutThis()
{
	QMessageBox::about(this, tr("About DuplicateFinder"), tr("<h3>Duplicate Finder %1</h3>"
															 "Program for easy finding and removing equal files.<br><br>"
															 "By ChemiKadze (<a href=\"mailto:chemikadze@gmail.com\">chemikadze@gmail.com</a>), based on Qt4.<br>"
															 "License GNU GPLv3.<br><br>"
															 "The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.").arg(VERSION));
}

void MainWindow::terminateThread()
{
	sThread->terminate();
	sThread->wait();
}

void MainWindow::setEnglish()
{
	if (trans!=NULL)
	{
		QApplication::removeTranslator(trans);
		delete trans;
		trans=NULL;
	}
}

void MainWindow::setRussian()
{
	if (trans!=NULL)
	{
		QApplication::removeTranslator(trans);
		delete trans;
	}
	trans=new QTranslator;
	trans->load("translation_ru.qm", ":/translations");
	QApplication::installTranslator(trans);
}


void MainWindow::changeEvent(QEvent *event)
 {
	if (event->type() == QEvent::LanguageChange)
	{
		QStringList headers;
		headers << tr("Filename")
				<< tr("Duplicates")
				<< tr("Size")
				<< tr("Creation date")
				<< tr("Full path");


		filList->setHeaderLabels(headers);
		headers.clear();
		headers << tr("Filename")
				<< tr("Full path");

		dupList->setHeaderLabels(headers);

		openDirButton->setText(tr("Open..."));
		fileMenu->setTitle(tr("File"));
		openDirAct->setText(tr("Open dir..."));
		addDirAct->setText(tr("Add dir..."));
		exitAct->setText(tr("Exit"));

		optionsMenu->setTitle(tr("Options"));
		recursive->setText(tr("Recursively"));
		compareNamesAct->setText(tr("Compare filenames"));
		hiddenFilesAct->setText(tr("Look in hidden files"));
		showOnlyDupAct->setText(tr("Only duplicated"));
		transMenu->setTitle(tr("Language"));
		transEnAct->setText(tr("English"));
		transRuAct->setText(tr("Russian"));
		settingsAct->setText(tr("Settings"));
		viewMenu->setTitle(tr("View"));
		toolBarMenu->setTitle(tr("Toolbar"));
		showToolIconsAct->setText(tr("Show icons"));
		toolTextBesideAct->setText(tr("Text beside icons"));
		toolTextUnderAct->setText(tr("Text under icons"));

		actionsMenu->setTitle(tr("Actions"));
		scanAct->setText(tr("Scan"));
		removeSelectedAct->setText(tr("Remove selected"));
		removeAllAct->setText(tr("Remove copies"));

		helpMenu->setTitle(tr("Help"));
		aboutThisAct->setText(tr("About..."));
		aboutQtAct->setText(tr("About Qt..."));

		toolBar->setWindowTitle(tr("Main toolbar"));
	}
	else
		QWidget::changeEvent(event);
 }

void MainWindow::setToolSettings()
{
	if (!showToolIconsAct->isChecked())
	{
		toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);
		toolTextBesideAct->setEnabled(false);
		toolTextUnderAct->setEnabled(false);
	}
	else
	{
		toolTextBesideAct->setEnabled(true);
		toolTextUnderAct->setEnabled(true);
		if (toolTextBesideAct->isChecked())
			toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
		else
			toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	}
}

void MainWindow::settings()
{
	saveSettings();
	OptionsDialog *dialog=new OptionsDialog(this);
        connect(dialog, SIGNAL(applyClicked()), this, SLOT(loadSettings()));
	if (dialog->exec())
	{
		loadSettings();
	}
}
