#include "time_utility.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <iomanip>

namespace time_utility {
std::time_t SetTime(size_t hours, size_t minutes) {
    if (hours > MAX_HOUR_NUMBER_PER_DAY)
        throw std::out_of_range("Wrong value of hours! (must be from 0 to 23)");
    if (minutes > MAX_MINUTE_NUMBER_PER_HOUR)
        throw std::out_of_range("Wrong value of minutes! (must be from 0 to 59)");

    using std::chrono::system_clock;
    std::time_t current_time = system_clock::to_time_t(system_clock::now());

    std::tm tm_result_time;
    localtime_s(&tm_result_time, &current_time);
    tm_result_time.tm_hour = static_cast<int>(hours);
    tm_result_time.tm_min = static_cast<int>(minutes);

    return std::mktime(&tm_result_time);
}

void PrintTime(const std::time_t& time_to_print) {
    std::tm tm_local;
    localtime_s(&tm_local, &time_to_print);

    char buffer[26];
    asctime_s(buffer, sizeof(buffer), &tm_local);
    std::cout << buffer;
}


std::time_t GenerateRandomTime(std::mt19937& generator) {
    std::uniform_int_distribution<size_t> hour_randomizer(0, MAX_HOUR_NUMBER_PER_DAY);
    std::uniform_int_distribution<size_t> minute_randomizer(0, MAX_MINUTE_NUMBER_PER_HOUR);

    size_t hours = hour_randomizer(generator);
    size_t minutes = minute_randomizer(generator);

    std::time_t generated_time = SetTime(hours, minutes);
    return generated_time;
}



}  // namespace time_utility
