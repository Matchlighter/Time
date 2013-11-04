/*
	Time Library - Simple, useful time library for the Arduino
	Copyright (c) Matchlighter 2013
	Portions copyright (c) Michael Magolis 2009

	This library is distributed under the terms of the GNU
	Lesser General Public License.

	Currently only works with times > than the Unix Epoch (Later than 00:00:00 on Jan 1, 1970)
*/

#include "Time.h"

Time::Time(int hr, int min, int sec, int day, int mo, unsigned long yr) {
	set(hr, min, sec, day, mo, yr);
}

Time::Time(time_t unx) {
	set(unx);
}

void Time::add(time_t t) {
	set(getUnixTime()+t);
}

void Time::minus(time_t t) {
	set(getUnixTime()-t);
}

unsigned int Time::getSeconds() {
	return cacheTime.Second;
}
unsigned int Time::getMinutes() {
	return cacheTime.Minute;
}
unsigned int Time::getHours() {
	return cacheTime.Hour;
}
unsigned int Time::getDate() {
	return cacheTime.Date;
}
unsigned int Time::getMonth() {
	return cacheTime.Month;
}
unsigned int Time::getYear() {
	return cacheTime.Year;
}

int Time::getWeekDay() {
	return int(getUnixTime() / SECS_PER_DAY + 4) % 7 + 1; //Probably not the fastest way of doing this, but it does the job.
}

boolean Time::isLeapYear() {
	return LEAP_YEAR(cacheTime.Year);
}

static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};

time_t Time::getUnixTime() {
	return this->unixTime;
}

void Time::refreshCached() {
	time_t tunx = unixTime;
	cacheTime.Second = tunx % 60;
	tunx /= 60;
	cacheTime.Minute = tunx % 60;
	tunx /= 60;
	cacheTime.Hour = tunx % 24;
	tunx /= 24;

	cacheTime.WeekDay = (tunx + 4) % 7 + 1;

	unsigned long tyear = 1970;
	unsigned long days = 0;
	while((days += (LEAP_YEAR(tyear) ? 366 : 365)) <= tunx) {
		tyear++;
	}
	cacheTime.Year = tyear;

	days -= LEAP_YEAR(tyear) ? 366 : 365;
	tunx -= days; // Day of Year (0 based)
	cacheTime.YearDay = tunx + 1;

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
    
		if (tunx >= monthLen) {
			tunx -= monthLen;
		} else {
			break;
		}
	}
	cacheTime.Month = tmonth + 1;
	cacheTime.Date = tunx + 1;
}

void Time::set(time_t unx) {
	unixTime = unx;
	refreshCached();
}

time_t getUnixFor(int hours, int minutes, int seconds, int date, int month, int year) {
	unsigned long days = 0;
	for (int i=1970; i<year; i++) {
		days += LEAP_YEAR(i) ? 366 : 365;
	}

	for (int i=0; i<month-1; i++) {
		if (i==1 && LEAP_YEAR(year)) { //Feb
			days += 29;
		} else {
			days += monthDays[i];
		}
	}
	days += date-1;
	return (days * SECS_PER_DAY) + (hours * SECS_PER_HOUR) + (minutes * SECS_PER_MIN) + seconds;
}

void Time::set(int hr, int min, int sec, int day, int mo, unsigned long yr) {
	set(getUnixFor(hr, min, sec, day, mo, yr));
}

Time Time::findDateAt(WeekInMonth wk, WeekDay wd, int month, int year) {
	Time tm = Time(0, 0, 0, 1, month, year);

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

