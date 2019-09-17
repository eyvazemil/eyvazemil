#include "Clock.h"

//! constructor
Clock::Clock(int h, int m, int sec) {
    this->hour = h;
    this->minute = m;
    this->seconds = sec;
}

//! get hour
int Clock::get_hour() const {
    return this->hour;
}

//! get minute
int Clock::get_minute() const {
    return this->minute;
}

//! get seconds
int Clock::get_seconds() const {
    return this->seconds;
}

//! compare clock
int Clock::Compare(const Clock & rhs) const {
    if(this->hour > rhs.hour) return 1;
    else if(this->hour == rhs.hour) {
        if(this->minute > rhs.minute) return 1;
        else if(this->minute == rhs.minute) {
            if(this->seconds > rhs.seconds) return 1;
            else if(this->seconds == rhs.seconds) return 0;
            else return -1;
        } else return -1;
    } else return -1;
}