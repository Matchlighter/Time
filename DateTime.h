/*

*/

#ifndef DateTime_h
#define DateTime_h

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

typedef unsigned long time_t;
typedef unsigned long date_t;

#include <Time.h>
#include <Date.h>

class DateTime {
public:
	DateTime();
	DateTime(Date dt, Time tm);
	DateTime(time_t unix);
	DateTime(int moday, int mo, int yr, int hr, int min, int sec);

	void add(long t);
	void minus(long t);

	time_t getUnixTime();

	Date date;
	Time time;
private:

};

#endif