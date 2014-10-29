#include "test.h"
#include "calendarcanvas.h"

test::test(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QFrame* MainFrame = new QFrame;
	MainFrame->resize(1280, 768);
	MainFrame->show();

	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setStyleSheet("background:transparent;");

	CalendarCanvas* SFMLView = new CalendarCanvas(MainFrame, QPoint(0, 0), QSize(1920, 1080));
	SFMLView->show();
}

test::~test()
{

}
