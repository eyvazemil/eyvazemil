#include "Time.h"

//! constructor
Time::Time(const Date & d, const Clock & c) {
    this->date = d;
    this->clock = c;
}

//! get date
Date Time::get_date() const {
    return this->date;
}

//! get clock
Clock Time::get_clock() const {
    return this->clock;
}

//! compare time
int Time::Compare(const Time & rhs) const {
    if(this->date.Compare(rhs.date) > 0) return 1;
    else if(this->date.Compare(rhs.date) == 0) {
        if(this->clock.Compare(rhs.clock) > 0) return 1;
        else if(this->clock.Compare(rhs.clock) == 0) return 0;
        else return -1;
    } else return -1;
}

//! operator =
Time & Time::operator=(const Time & rhs) {
    this->date = rhs.get_date();
    this->clock = rhs.get_clock();
    return *this;
}

//! create a string from time
std::string Time::time_to_string() const {
    std::string final_string, day, month, year, hour, minute, seconds;
    int d = get_date().get_day(), mon = get_date().get_month(), y = get_date().get_year();
    int h = get_clock().get_hour(), min = get_clock().get_minute(), sec = get_clock().get_seconds();
    if(d < 10)
        day += "0";
    day += std::to_string(d);
    if(mon < 10)
        month += "0";
    month += std::to_string(mon);
    year = std::to_string(y);
    if(h < 10)
        hour += "0";
    hour += std::to_string(h);
    if(min < 10)
        minute += "0";
    minute += std::to_string(min);
    if(sec < 10)
        seconds += "0";
    seconds += std::to_string(sec);

    final_string = day + "/" + month + "/" + year + " " + hour + ":" + minute + ":" + seconds;

    return final_string;
}
