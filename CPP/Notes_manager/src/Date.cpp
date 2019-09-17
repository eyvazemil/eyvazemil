#include "Date.h"

//! constructor
Date::Date(int d, int m, int y) {
    this->day = d;
    this->month = m;
    this->year = y;
}

//! get day
int Date::get_day() const {
    return this->day;
}

//! get month
int Date::get_month() const {
    return this->month;
}

//! get year
int Date::get_year() const {
    return this->year;
}

//! compare date
int Date::Compare(const Date & rhs) const {
    if(this->year > rhs.year) return 1;
    else if(this->year == rhs.year) {
        if(this->month > rhs.month) return 1;
        else if(this->month == rhs.month) {
            if(this->day > rhs.day) return 1;
            else if(this->day == rhs.day) return 0;
            else return -1;
        } else return -1;
    } else return -1;
}