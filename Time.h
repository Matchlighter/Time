/*

*/

#ifndef Time_h
#define Time_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24UL)
#define DAYS_PER_WEEK (7UL)
#define SECS_PER_WEEK (SECS_PER_DAY * DAYS_PER_WEEK)
#define SECS_PER_YEAR (SECS_PER_WEEK * 52UL)

//USEFUL MACROS
#define LEAP_YEAR(year) ((year%400==0) || (year%100!=0 && year%4==0))

typedef struct {
	unsigned int Second;
	unsigned int Minute;
	unsigned int Hour;
	unsigned int WeekDay;
	unsigned int YearDay;
	unsigned int Date;
	unsigned int Month;
	unsigned int Year;
} NormalTime;

typedef unsigned long time_t;

typedef enum {
	InvalidDay, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday
} WeekDay;

typedef enum { //Currently Unused
	InvalidMonth, Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec
} Month;

typedef enum {
	Last,
	First,
	Second,
	Third,
	Fourth
} WeekInMonth;

class Time {
public:
	Time(int hr, int min, int sec, int day, int mo, unsigned long yr);
	Time(unsigned long);
	void add(time_t t);
	void minus(time_t t);

	unsigned int getSeconds();
	unsigned int getMinutes();
	unsigned int getHours();
	unsigned int getDate();
	unsigned int getMonth();
	unsigned int getYear();

	void set(time_t unx);
	void set(int hr, int min, int sec, int day, int mo, unsigned long yr);

	static Time findDateAt(WeekInMonth wk, WeekDay wd, int month, int year); //Finds the date of the wd day in the wk week of month, year

	int getWeekDay();
	time_t getUnixTime();
	boolean isLeapYear();
private:
	void refreshCached();
	time_t unixTime;
	NormalTime cacheTime;
};

#endif