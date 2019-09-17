#ifndef PA2_PROJECT_TIME_H
#define PA2_PROJECT_TIME_H

#include "Date.h"
#include "Clock.h"
#include <string>

class Time {
public:
    //! default constructor
    Time() = default;
    //! constructor
    Time(const Date &, const Clock &);
    //! get date
    Date get_date() const;
    //! get clock
    Clock get_clock() const;
    //! compare time
    int Compare(const Time &) const;
    //! operator=
    Time & operator=(const Time &);
    //! create a string from time
    std::string time_to_string() const;
private:
    Date date;
    Clock clock;
};

//! time comparator for the std::map
struct compareTime {
    bool operator()(const Time & lhs, const Time & rhs) const {
        if(lhs.Compare(rhs) > 0) return true;
        else return false;
    }
};

#endif //PA2_PROJECT_TIME_H
