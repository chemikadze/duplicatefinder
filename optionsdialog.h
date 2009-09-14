#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtGui>
#include "global.h"

class OptionsDialog : public QDialog
{
        Q_OBJECT

	QGroupBox *view;
	QGroupBox *opts;

	QCheckBox *recursive;
	QCheckBox *compareNames;
	QCheckBox *followSymLinks;
	QCheckBox *hidden;
	QCheckBox *dupl;
	QComboBox *language;
	QCheckBox *tool;
	QComboBox *textPos;
	QPushButton *openBtn;
	QLabel *defaultLbl;
	QLineEdit *defaultDir;
	QPushButton *okBtn, *cancelBtn, *applyBtn;
private:
	void changeEvent(QEvent *event);
private slots:
	void loadSettings();
	void saveSettings();
	void ok();
	void apply();
	void setDefaultDir();
signals:
	void applyClicked();
public:
	OptionsDialog(QWidget *parent=0);
};

#endif // OPTIONSDIALOG_H
