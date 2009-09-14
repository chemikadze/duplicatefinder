#include "progresswidget.h"

ProgressWidget::ProgressWidget()
{
	QGridLayout *la=new QGridLayout;
	setWindowTitle(tr("Please wait..."));
	label=new QLabel();
	format=tr("Processing \"%1\", %2 from %3...");
	progBar=new QProgressBar;
	progBar->setTextVisible(true);
	stopBtn=new QPushButton(QIcon(":/icons/process-stop.png"), tr("Stop"));
	la->addWidget(label, 0, 0, 1, 3);
	la->addWidget(progBar, 1, 0, 1, 3);
	la->addWidget(stopBtn, 2, 2);
	connect(stopBtn, SIGNAL(clicked()), this, SLOT(slotStop()));
	setLayout(la);
	setModal(true);
}

void ProgressWidget::changeEvent(QEvent* event)
{
	if (event->type() == QEvent::LanguageChange)
	{
		format=tr("Processing \"%1\", %2 from %3...");
		setWindowTitle(tr("Please wait..."));
		stopBtn->setText(tr("Stop"));
	}
	else
		QWidget::changeEvent(event);
}

void ProgressWidget::slotStop()
{
	emit stop();
	progBar->setValue(progBar->maximum());
}

void ProgressWidget::setCount(int count)
{
	if (count < 0)
	{
		progBar->setRange(0, 10);
		progBar->setTextVisible(false);
	}
	else
	{
		progBar->setRange(0, count);
		progBar->setTextVisible(true);
	}
	progBar->setValue(0);
	label->setText("");
}

void ProgressWidget::step()
{
	progBar->setValue(progBar->value()+1);
	if (progBar->value() > progBar->maximum())
		progBar->setValue(0);
}

void ProgressWidget::setCurrentFileName(const QString& s)
{
	if (s.length() > 20)
	{
		QString ss=s;
		ss.resize(20);
		label->setText(format.arg(ss).arg(progBar->value()).arg(progBar->maximum()));
	}
	else
	{
		label->setText(format.arg(s).arg(progBar->value()).arg(progBar->maximum()));
	}
	step();
}

void ProgressWidget::closeEvent(QCloseEvent *event)
{
	if (progBar->value() >= progBar->maximum())
		event->accept();
	else
		event->ignore();
}

void ProgressWidget::setStopEnabled(bool b)
{
	stopBtn->setEnabled(b);
}

void ProgressWidget::sudoClose()
{
	progBar->setValue(progBar->maximum());
	close();
}

void ProgressWidget::setValue(int v)
{
	progBar->setValue(v);
}
