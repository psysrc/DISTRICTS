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

/**
 * Convert calendar to a human-readable string.
 * Example: `Fairfax 12 311SA, 3-26L`
 */
std::string SettlersAgeCalendar::to_string() const
{
    std::stringstream str;

    const char lightOrNight = (hours < hoursOfLightPerDay) ? 'L' : 'N';

    str << monthNames.at(months) << " " << (days + 1) << " " << (years + 1) << "SA, " << (hours + 1) << "-" << (minutes + 1) << lightOrNight;

    return str.str();
}
