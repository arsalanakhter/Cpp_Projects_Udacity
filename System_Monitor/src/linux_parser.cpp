#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem(){
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  string line, mem_total, mem_avail, mem_id;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    if (std::getline(stream, line)) {
      std::istringstream linestream(line);
      if (linestream >> mem_id >> mem_total){
        std::getline(stream, line);
        if (std::getline(stream, line)) {
          std::istringstream linestream(line);
          if (linestream >> mem_id >> mem_avail){
            return (std::stof(mem_total) - std::stof(mem_avail))/std::stof(mem_total);
          }
        }        
      }
    }
  }
  return 0;
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line, uptime1, uptime2;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> uptime1 >> uptime2 ){
        long t = std::stoi(uptime1);
        return t;
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
// Not used. Bonus implementation in processor class.
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
// Not used. Bonus implementation in processor class.
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  vector<string> numbers;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    if (std::getline(stream, line)) {
      std::istringstream linestream(line);
      string num; 
      while (linestream >> num){
        numbers.push_back(num);
      }
    }
  }
  return numbers;
 }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value ){
        if (key == "processes") {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value ){
        if (key == "procs_running") {
          return std::stoi(value);
        }
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  std::ifstream stream(kProcDirectory + '/' + std::to_string(pid) + kCmdlineFilename);
  string line;
  if (stream.is_open()) {
    if (std::getline(stream, line)) {
      return line;
    }
  }
  return string();
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) {
  string line, key, value;
  std::ifstream stream(kProcDirectory + '/' +  std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value ){
        if (key == "VmSize:") {
          return value;
        }
      }
    }
  }
  return string();
 }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line, key, value;
  std::ifstream stream(kProcDirectory + '/' +  std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while(linestream >> key >> value ){
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return string();  
 }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int uid) { 
  string line, key, x, token, value;
  vector<string> line_words;
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream key(line);
      while(std::getline(key, token, ':')){
        line_words.push_back(token);
        if (token == std::to_string(uid)){
          line_words.pop_back();
          line_words.pop_back();
          return line_words.back();
        }
      }
    }
  }
  return string();  
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line, num;
  std::ifstream stream(kProcDirectory + '/' +  std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    if (std::getline(stream, line)) {
      std::istringstream linestream(line);
      for(int i = 1; i < 22; i++ )
        linestream >> num;
      linestream >> num;
      return std::stoi(num);
    }
  }
  return 0;  
 }


// Function for calculating individual process CPU Utilization.
// Not using Jiffies above
vector<string> LinuxParser::IndividualProcessCpuUtilization(int pid) { 
  string line;
  vector<string> numbers;
  std::ifstream stream(kProcDirectory + '/' +  std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    if (std::getline(stream, line)) {
      std::istringstream linestream(line);
      string num; 
      vector<string> req_nums;
      for (int i = 1; i < 23; i++){
        linestream >> num;
        if (i >= 14 && i<= 17){
          numbers.push_back(num);
        }
        if (i == 22){
          numbers.push_back(num);
        }
      }
    }
  }
  return numbers;
 }
