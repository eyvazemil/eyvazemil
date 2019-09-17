#ifndef PA2_PROJECT_CLOCK_H
#define PA2_PROJECT_CLOCK_H

class Clock {
public:
    //! default constructor
    Clock() = default;
    //! constructor
    Clock(int h, int m, int sec);
    //! default copy constructor
    Clock(const Clock &) = default;
    //! get hour
    int get_hour() const;
    //! get minute
    int get_minute() const;
    //! get seconds
    int get_seconds() const;
    //! compare clock
    int Compare(const Clock &) const;
    //! operator=
    Clock & operator=(const Clock &) = default;
private:
    int hour, minute, seconds;
};

#endif //PA2_PROJECT_CLOCK_H
