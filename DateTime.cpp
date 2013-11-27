
#include "DateTime.h"

DateTime::DateTime() {
	
}

DateTime::DateTime(Date dt, Time tm) {
	this->date = dt;
	this->time = tm;
}

DateTime::DateTime(time_t unix) {
	this->date = Date(unix / SECS_PER_DAY);
	this->time = Time(unix % SECS_PER_DAY);
}

DateTime::DateTime(int moday, int mo, int yr, int hr, int min, int sec) {
	this->date = Date(moday, mo, yr);
	this->time = Time(hr, min, sec);
}

void DateTime::add(long t) {
	this->date.add(t / SECS_PER_DAY + this->time.add(t % SECS_PER_DAY));
}
void DateTime::minus(long t) {
	this->date.minus(t / SECS_PER_DAY + -this->time.minus(t % SECS_PER_DAY));
}

time_t DateTime::getUnixTime() {
	return (this->date.getUnixDate()*SECS_PER_DAY) + (this->time.getAsSeconds());
}