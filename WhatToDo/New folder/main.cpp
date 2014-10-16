#include "anothergui.h"
#include <QtWidgets/QApplication>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian_calendar.hpp>

using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AnotherGUI w;
	w.show();
	//ptime aa(date(2010,10,10),hours(2));
	//cout << to_iso_string(aa);
	return a.exec();
}
