#include "calendar/SettlersAgeCalendar.hpp"
#include <sstream>
#include <unordered_map>

static const std::unordered_map<unsigned int, const std::string> monthNames {
    {0, "Farrar"},
    {1, "Fairfax"},
    {2, "Jameson"},
    {3, "Norvell"},
    {4, "Selden"},
    {5, "Allerton"},
};


/**
 * Create a calendar starting at 0 USAT.
 */
SettlersAgeCalendar::SettlersAgeCalendar() : usat(0), years(0), months(0), days(0), hours(0), ticks(0)
{

}

/**
 * Create a calendar starting at the given USAT.
 */
SettlersAgeCalendar::SettlersAgeCalendar(unsigned int usat) : usat(usat)
{
    unsigned int usatRemaining = usat;

    ticks = usatRemaining % ticksPerHour;
    usatRemaining -= ticks;
    usatRemaining /= ticksPerHour;

    hours = usatRemaining % hoursPerDay;
    usatRemaining -= hours;
    usatRemaining /= hoursPerDay;

    days = usatRemaining % daysPerMonth;
    usatRemaining -= days;
    usatRemaining /= daysPerMonth;

    months = usatRemaining % monthsPerYear;
    usatRemaining -= months;
    usatRemaining /= monthsPerYear;

    years = usatRemaining;
}

/**
 * Advance the calendar by one unit of USAT time.
 */
void SettlersAgeCalendar::advance()
{
    ++usat;

    ++ticks;

    if (ticks < ticksPerHour)
        return;

    ticks = 0;
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

/**
 * Convert calendar to a human-readable string.
 * Example: `Fairfax 12 311SA, 3-26L`
 */
std::string SettlersAgeCalendar::to_string() const
{
    std::stringstream str;

    str << monthNames.at(months) << " " << (days + 1) << " " << (years + 1) << "SA, " << (hours + 1) << "hr";

    return str.str();
}
