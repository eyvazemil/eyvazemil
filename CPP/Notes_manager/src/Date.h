#ifndef PA2_PROJECT_DATE_H
#define PA2_PROJECT_DATE_H

class Date {
public:
    //! default constructor
    Date() = default;
    //! constructor
    Date(int d, int m, int y);
    //! default copy constructor
    Date(const Date &) = default;
    //! get dat
    int get_day() const;
    //! get month
    int get_month() const;
    //! get year
    int get_year() const;
    //! compare date
    int Compare(const Date &) const;
    //! operator=
    Date & operator=(const Date &) = default;
private:
    int day, month, year;
};

#endif //PA2_PROJECT_DATE_H
