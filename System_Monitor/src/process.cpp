#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() const { return pid_; }

// Set this process's PID at initialization
Process::Process(int pid) {pid_ = pid; ram_ = 0; cpu_usage_ = 0;}

// TODO: Return this process's CPU utilization
// Adapted from https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
float Process::CpuUtilization() { 
    vector<string> numbers = LinuxParser::IndividualProcessCpuUtilization(pid_);
    long int sys_uptime = LinuxParser::UpTime();
    if (!numbers.empty())
    {
        long utime = std::stoi(numbers[0]);
        long stime = std::stoi(numbers[1]);
        long cutime = std::stoi(numbers[2]);
        long cstime = std::stoi(numbers[3]);
        long starttime = std::stoi(numbers[4]);
        long hertz = sysconf(_SC_CLK_TCK);
        float total_time = utime + stime + cutime + cstime;
        long seconds = sys_uptime - (starttime / hertz);
        cpu_usage_ = ((total_time / hertz) / seconds);
        return cpu_usage_;
    }
    return 0.0;
}

// TODO: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_);
}

// TODO: Return this process's memory utilization
string Process::Ram() {
    string ram_s = LinuxParser::Ram(pid_);
    if (!ram_s.empty()){
        ram_ = std::stoi(ram_s);
        // Convert to MB for display
        return ((ram_ < 1000000 ) ? 
           ' '+std::to_string(static_cast<int>(ram_/1024.0)):
           std::to_string(static_cast<int>(ram_/1024.0)));
    }
    else
    {
        return "0.0";
    }  
 }

// TODO: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(std::stoi(LinuxParser::Uid(pid_)));
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return static_cast<long>(LinuxParser::UpTime(pid_)/sysconf(_SC_CLK_TCK));
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    // Compare by RAM Usage
    if (this->ram_ > a.ram_)
        return true;
    else 
        return false; 
    }