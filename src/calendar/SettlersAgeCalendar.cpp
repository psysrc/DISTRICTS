#include "calendar/SettlersAgeCalendar.hpp"

/**
 * Create a calendar starting at 0 USAT.
 */
SettlersAgeCalendar::SettlersAgeCalendar() : usat(0), years(0), months(0), days(0), hours(0), minutes(0)
{

}

/**
 * Advance the calendar by one unit of USAT time.
 */
void SettlersAgeCalendar::advance()
{
    ++usat;

    ++minutes;

    if (minutes < minutesPerHour)
        return;

    minutes = 0;
    ++hours;

    if (hours < hoursPerDay)
        return;

    hours = 0;
    ++days;

    if (days < daysPerMonth)
        return;

    days = 0;
    ++months;

    if (months < monthsPerYear)
        return;

    months = 0;
    ++years;
}

/**
 * Convert calendar to USAT (Universal Settler's Age Time).
 */
unsigned int SettlersAgeCalendar::to_usat() const
{
    return usat;
}
