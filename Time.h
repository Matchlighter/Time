/*

*/

#ifndef Time_h
#define Time_h

#if ARDUINO >= 100
#include <Arduino.h> 
#else
#include <WProgram.h> 
#endif

#include <DateTime.h>

class Time {
public:
	Time();
	Time(int hr, int min, int sec);
	Time(time_t off);

	//These return the # of day rollovers that occurred
	int add(long t);
	int minus(long t);
	int add(Time t);
	int minus(Time t);

	void set(Time otm);

	time_t getAsSeconds();
	void setFromSeconds(time_t secs);

	int second;
	int minute;
	int hour;

private:
	int propToDays();
};

#endif