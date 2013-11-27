
#include "Date.h"

Date::Date() {

}

Date::Date(int day, int mo, int yr) {

}

Date::Date(date_t unixDate) {
	setFromUnixDate(unixDate);
}

void Date::add(long days) {

}

void Date::minus(long days) {

}

int Date::getWeekDay() {
	return this->weekDay;
}

int Date::getYearDay() {
	return this->yearDay;
}

boolean Date::isLeapYear() {
	return LEAP_YEAR(this->year);
}

static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};
date_t Date::getUnixDate() {
	date_t days = 0;
	for (int i=1970; i<this->year; i++) {
		days += LEAP_YEAR(i) ? 366 : 365;
	}

	for (int i=0; i<this->month-1; i++) {
		if (i==1 && LEAP_YEAR(year)) { //Feb
			days += 29;
		} else {
			days += monthDays[i];
		}
	}
	days += this->day-1;
	return days;
}

void Date::setFromUnixDate(date_t udays) {

	date_t tdays = udays;
	this->weekDay = (udays + 4) % 7 + 1;

	int tyear = 1970;
	date_t days = 0;
	while((days += (LEAP_YEAR(tyear) ? 366 : 365)) <= tdays) {
		tyear++;
	}
	this->year = tyear;

	days -= LEAP_YEAR(tyear) ? 366 : 365;
	tdays -= days; // Day of Year (0 based)
	this->yearDay = tdays + 1;

	int tmonth=0;
	int monthLen=0;
	for (tmonth=0; tmonth<12; tmonth++) {
		if (tmonth==1) { // Feb
			if (LEAP_YEAR(tyear)) {
				monthLen=29;
			} else {
				monthLen=28;
			}
		} else {
			monthLen = monthDays[tmonth];
		}
    
		if (tdays >= monthLen) {
			tdays -= monthLen;
		} else {
			break;
		}
	}
	this->month = tmonth + 1;
	this->day = tdays + 1;
}

Date Date::findDateAt(WeekInMonth wk, WeekDay wd, int month, int year) {
	Date tm = Date(1, month, year);

	int num = 0;
	int fst = 1+(7+(wd-tm.getWeekDay()))%7;
	for (int i=1; i<=5; i++) {
		if (fst + 7*(i-1) <= monthDays[month-1])
			num=i;
	}
	int aday=0;
	if (wk==0) aday = fst+7*(num-1);
	else aday = fst+7*(wk-1);

	tm.add((aday-1)*SECS_PER_DAY);
	return tm;
}