#pragma once

class Datetime {
	public:
		Datetime(void);
		int getDuration(Datetime myDatetime);
		bool isEarlierThan(Datetime myDatetime);
		Datetime addDuration(Datetime myDateTime, int durationToAdd);
		Datetime subtractDuration(Datetime myDateTime, int durationToSubtract);
		bool isEmptyDatetime();
		int getTime();
		int getDay();
		int getMonth();
		int getYear();
		void setTime();
		void setDay();
		void setMonth();
		void setYear();

	private:
		int _time;
		int _day;
		int _month;
		int _year;
};

