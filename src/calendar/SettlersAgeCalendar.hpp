#ifndef SETTLERS_AGE_CALENDAR_H_
#define SETTLERS_AGE_CALENDAR_H_

#include <string>

class SettlersAgeCalendar
{
public:
    SettlersAgeCalendar();
    SettlersAgeCalendar(unsigned int usat);

    ~SettlersAgeCalendar() = default;

    void advance();
    unsigned int to_usat() const;
    std::string to_string() const;

    static constexpr unsigned int ticksPerHour = 10;
    static constexpr unsigned int hoursPerDay = 12;
    static constexpr unsigned int daysPerMonth = 20;
    static constexpr unsigned int monthsPerYear = 6;

    static constexpr unsigned int ticksPerDay = ticksPerHour * hoursPerDay;
    static constexpr unsigned int ticksPerMonth = ticksPerDay * daysPerMonth;
    static constexpr unsigned int ticksPerYear = ticksPerMonth * monthsPerYear;

private:

    unsigned int usat;  // Universal Settler's Age Time (USAT)
    unsigned int years;
    unsigned int months;
    unsigned int days;
    unsigned int hours;
    unsigned int ticks;
};

#endif /* SETTLERS_AGE_CALENDAR_H_ */
