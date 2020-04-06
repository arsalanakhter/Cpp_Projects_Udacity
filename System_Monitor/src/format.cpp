#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
    long min, hour; 
    min = seconds / 60;
    hour = min / 60;
    return std::to_string(int(hour)) + ':' + 
           std::to_string(int(min % 60)) + ':' +
           ((int(seconds % 60) < 10 ) ? 
           '0'+std::to_string(int(seconds % 60)):
           std::to_string(int(seconds % 60)));

}