#include <Time.h>

void setup() {
  Serial.begin(9600);
  Time t = Time(1,2,3,3,11,2013);
  Serial.println(t.getUnixTime());
  
  t = Time::findDateAt(First,Monday,Nov,2013);
  Serial.println(t.getUnixTime());
}

void loop() {
  delay(1000);
}