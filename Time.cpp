/*
	Time Library - Simple, useful time library for the Arduino
	Copyright (c) Matchlighter 2013
	Portions copyright (c) Michael Magolis 2009

	This library is distributed under the terms of the GNU
	Lesser General Public License.

	Currently only works with times > than the Unix Epoch (Later than 00:00:00 on Jan 1, 1970)
*/

#include "Time.h"

Time::Time() {
	Time(0);
}

Time::Time(int hr, int min, int sec) {
	this->second = sec;
	this->minute = min;
	this->hour = hr;
}

Time::Time(time_t unx) {
	setFromSeconds(unx);
}

int Time::add(long t) {
	this->second += t % SECS_PER_MIN;
	this->minute += (t % SECS_PER_HOUR) / SECS_PER_MIN;
	this->hour += (t % SECS_PER_DAY) / SECS_PER_HOUR;
	return propToDays();
}

int Time::minus(long t) {
	this->second -= t % SECS_PER_MIN;
	this->minute -= (t % SECS_PER_HOUR) / SECS_PER_MIN;
	this->hour -= (t % SECS_PER_DAY) / SECS_PER_HOUR;
	return propToDays();
}

int Time::add(Time t) {
	this->second += t.second;
	this->minute += t.minute;
	this->hour += t.hour;
	return propToDays();
}

int Time::minus(Time t) {
	this->second -= t.second;
	this->minute -= t.minute;
	this->hour -= t.hour;
	return propToDays();
}

int Time::propToDays() {
	int days = 0;

	while (second < 0) {
		second += 60;
		minute -= 1;
	}
	minute += (second / 60);
	second %= 60;

	while (minute < 0) {
		minute += 60;
		hour -= 1;
	}
	hour += minute / 60;
	minute %= 60;

	while (hour < 0) {
		hour += 24;
		days -= 1;
	}
	days += hour / 24;
	hour %= 24;

	return days
}

void Time::set(Time otm) {
	this->second = otm.second;
	this->minute = otm.minute;
	this->hour = otm.hour;
}

time_t Time::getAsSeconds() {
	return (hour * SECS_PER_HOUR) + (minute * SECS_PER_MIN) + second;
}

void Time::setFromSeconds(time_t secs) {
	this->second = secs % 60;
	secs /= 60;
	this->minute = secs % 60;
	secs /= 60;
	this->hour = secs % 24;
	secs /= 24;
}