#ifndef SETTLERS_AGE_CALENDAR_H_
#define SETTLERS_AGE_CALENDAR_H_

class SettlersAgeCalendar
{
public:
    SettlersAgeCalendar();

    ~SettlersAgeCalendar() = default;

    void advance();
    unsigned int to_usat() const;

private:
    static const unsigned int minutesPerHour = 36;
    static const unsigned int hoursPerDay = 12;
    static const unsigned int daysPerMonth = 24;
    static const unsigned int monthsPerYear = 6;

    unsigned int usat;  // Universal Settler's Age Time (USAT)
    unsigned int years;
    unsigned int months;
    unsigned int days;
    unsigned int hours;
    unsigned int minutes;
};

#endif /* SETTLERS_AGE_CALENDAR_H_ */
