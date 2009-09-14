#include "optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent/*=0*/):QDialog(parent)
{
	setModal(true);
	recursive=new QCheckBox(tr("Recursively"));
	followSymLinks=new QCheckBox(tr("Follow sym links"));
	hidden=new QCheckBox(tr("Look in hidden files"));
	dupl=new QCheckBox(tr("Show only duplicated"));
	language=new QComboBox();
	language->addItem(tr("English"));
	language->addItem(tr("Russian"));
	textPos=new QComboBox();
	textPos->addItem(tr("Text beside icons"));
	textPos->addItem(tr("Text under icons"));
	tool=new QCheckBox(tr("Show toolbar icons"));
	tool->setCheckable(true);
	openBtn=new QPushButton(tr("Change..."));
	defaultLbl=new QLabel(tr("Default dir"));
	defaultDir=new QLineEdit();
	defaultDir->setReadOnly(true);
	compareNames=new QCheckBox(tr("Compare filenames"));
	opts=new QGroupBox(tr("Scan options"));
	view=new QGroupBox(tr("View"));
	okBtn=new QPushButton(QIcon(":/icons/dialog-ok-apply.png"), tr("Ok"));
	cancelBtn=new QPushButton(QIcon(":/icons/dialog-cancel.png"), tr("Cancel"));
	applyBtn=new QPushButton(tr("Apply"));
	QVBoxLayout *la1=new QVBoxLayout;
	QVBoxLayout *la2=new QVBoxLayout;
	QGridLayout *grid=new QGridLayout;
	QHBoxLayout *btns=new QHBoxLayout;
	la1->addWidget(recursive);
	la1->addWidget(followSymLinks);
	la1->addWidget(hidden);
	la1->addWidget(compareNames);
	la1->addStretch(1);
	opts->setLayout(la1);
	view->setLayout(la2);
	la2->addWidget(dupl);
	la2->addWidget(tool);
	la2->addWidget(textPos);
	la2->addWidget(language);
	la2->addStretch(1);
	btns->addStretch(1);
	btns->addWidget(okBtn, 0);
	btns->addWidget(cancelBtn, 0);
	btns->addWidget(applyBtn, 0);
	grid->addWidget(opts, 0, 0, 1, 2);
	grid->addWidget(view, 0, 2, 1, 2);
	grid->addWidget(defaultLbl, 1, 0, 1, 4);
	grid->addWidget(defaultDir, 2, 0, 1, 3);
	grid->addWidget(openBtn, 2, 3);
	grid->addLayout(btns, 3, 0, 1, 4);
	setLayout(grid); 
	connect(applyBtn, SIGNAL(clicked()), this, SLOT(apply()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(ok()));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
	connect(tool, SIGNAL(clicked(bool)), textPos, SLOT(setEnabled(bool)));
	connect(openBtn, SIGNAL(clicked()), this, SLOT(setDefaultDir()));
	loadSettings();
}

void OptionsDialog::loadSettings()
{
	QSettings *settings=new QSettings(this);
	settings->beginGroup("options");
		followSymLinks->setChecked(settings->value("follow_sym_links", false).toBool());
		defaultDir->setText(settings->value("default_dir", QDir::home().absolutePath()).toString());
		recursive->setChecked(settings->value("recursive", false).toBool());
		compareNames->setChecked(settings->value("compare_names", false).toBool());
		hidden->setChecked(settings->value("hidden", false).toBool());
		qDebug() << settings->value("language", QString("en")).toString();
		if (settings->value("language", QString("en")).toString() == QString("en"))
			language->setCurrentIndex(0);
		else
			language->setCurrentIndex(1);
	settings->endGroup();
	settings->beginGroup("view");
		dupl->setChecked(settings->value("only_dup", false).toBool());
		tool->setChecked(settings->value("show_tool_icons", true).toBool());
		textPos->setCurrentIndex(int(!settings->value("tool_beside_under", true).toBool()));
	settings->endGroup();
	delete settings;
}

void OptionsDialog::saveSettings()
{
	QSettings *settings=new QSettings(this);
	settings->beginGroup("options");
		settings->setValue("follow_sym_links", followSymLinks->isChecked());
		settings->setValue("default_dir", defaultDir->text());
		settings->setValue("recursive", recursive->isChecked());
		settings->setValue("compare_names", compareNames->isChecked());
		settings->setValue("hidden", hidden->isChecked());
		if (language->currentIndex()==0)
			settings->setValue("language", QString("en"));
		else
			settings->setValue("language", QString("ru"));
	settings->endGroup();
	settings->beginGroup("view");
		settings->setValue("only_dup", dupl->isChecked());
		settings->setValue("show_tool_icons", tool->isChecked());
		settings->setValue("tool_beside_under", textPos->currentIndex()==0);
	settings->endGroup();
	delete settings;
}

void OptionsDialog::apply()
{
    saveSettings();
    emit applyClicked();
}

void OptionsDialog::ok()
{
    saveSettings();
    accept();
}

void OptionsDialog::setDefaultDir()
{
    QFileDialog *dial=new QFileDialog(this);
    dial->setFileMode(QFileDialog::DirectoryOnly);
    dial->setDirectory(defaultDir->text());
    if (dial->exec())
    {
        defaultDir->setText(dial->selectedFiles().first());
    }
}

void OptionsDialog::changeEvent(QEvent *event)
 {
	if (event->type() == QEvent::LanguageChange)
	{
		recursive->setText(tr("Recursively"));
		followSymLinks->setText(tr("Follow sym links"));
		hidden->setText(tr("Look in hidden files"));
		dupl->setText(tr("Show only duplicated"));
		language->setItemText(0, tr("English"));
		language->setItemText(1, tr("Russian"));
		textPos->setItemText(0, tr("Text beside icons"));
		textPos->setItemText(1, tr("Text under icons"));
		tool->setText(tr("Show toolbar icons"));
		openBtn->setText(tr("Change..."));
		defaultLbl->setText(tr("Default dir"));
		opts->setTitle(tr("Options"));
		view->setTitle(tr("View"));
		okBtn->setText(tr("Ok"));
		cancelBtn->setText(tr("Cancel"));
	}
}
