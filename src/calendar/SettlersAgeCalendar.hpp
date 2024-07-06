#ifndef SETTLERS_AGE_CALENDAR_H_
#define SETTLERS_AGE_CALENDAR_H_

#include <string>

class SettlersAgeCalendar
{
public:
    SettlersAgeCalendar();

    ~SettlersAgeCalendar() = default;

    void advance();
    unsigned int to_usat() const;
    std::string to_string() const;

private:
    static constexpr unsigned int minutesPerHour = 36;
    static constexpr unsigned int hoursPerDay = 12;
    static constexpr unsigned int daysPerMonth = 24;
    static constexpr unsigned int monthsPerYear = 6;

    static constexpr unsigned int hoursOfLightPerDay = 6;

    unsigned int usat;  // Universal Settler's Age Time (USAT)
    unsigned int years;
    unsigned int months;
    unsigned int days;
    unsigned int hours;
    unsigned int minutes;
};

#endif /* SETTLERS_AGE_CALENDAR_H_ */
