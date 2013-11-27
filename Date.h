/*

*/

#ifndef Date_h
#define Date_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <DateTime.h>

class Date {
public:
	Date();
	Date(int day, int mo, int yr);
	Date(date_t unixDate);

	void add(long days);
	void minus(long days);

	int getWeekDay();
	int getYearDay();
	boolean isLeapYear();

	date_t getUnixDate();
	void setFromUnixDate(date_t unixDate);

	static Date findDateAt(WeekInMonth wk, WeekDay wd, int month, int year); //Finds the date of the wd day in the wk week of month, year

	int day;
	int month;
	int year;

private:
	int weekDay;
	int yearDay;
};

#endif