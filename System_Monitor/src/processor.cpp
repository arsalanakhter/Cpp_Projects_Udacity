#include "processor.h"
#include "linux_parser.h"

Processor::Processor(){}
void Processor::Read_New_Values(){
    std::vector<std::string> cpu_numbers = LinuxParser::CpuUtilization();
    user_ = std::stoi(cpu_numbers[1]);
    nice_ = std::stoi(cpu_numbers[2]);
    system_ = std::stoi(cpu_numbers[3]);
    idle_ = std::stoi(cpu_numbers[4]);
    iowait_ = std::stoi(cpu_numbers[5]); 
    irq_ = std::stoi(cpu_numbers[6]); 
    softirq_ = std::stoi(cpu_numbers[7]);
    steal_ = std::stoi(cpu_numbers[8]); 
    guest_ = std::stoi(cpu_numbers[9]);
    guest_nice_ = std::stoi(cpu_numbers[10]);
}
void Processor::Store_Values_as_Prev()
{
    prev_user_ = user_;
    prev_nice_ = nice_;
    prev_system_= system_;
    prev_idle_= idle_;
    prev_iowait_ = iowait_;
    prev_irq_ = irq_;
    prev_softirq_= softirq_;
    prev_steal_= steal_;
}

int Processor::Compute_Prev_Total_Idle(){
    return prev_idle_ + prev_iowait_;
}
int Processor::Compute_Total_Idle(){
    return idle_ + iowait_;
}
int Processor::Compute_Prev_non_Idle(){
    return  prev_user_ + prev_nice_ + prev_system_ + prev_irq_ + prev_softirq_ + prev_steal_;
}
int Processor::Compute_Total_non_Idle(){
    return user_ + nice_ + system_ + irq_ + softirq_ + steal_;
}
int Processor::Compute_Prev_Total(){
    return Compute_Prev_Total_Idle() + Compute_Prev_non_Idle();
}
int Processor::Compute_Total(){
    return Compute_Total_non_Idle() + Compute_Total_Idle();
}
int Processor::Compute_Total_Diff(){
    return Compute_Total() - Compute_Prev_Total();

}
int Processor::Compute_Idle_Diff(){
    return Compute_Total_Idle() - Compute_Prev_Total_Idle();
}
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    Store_Values_as_Prev(); // For next cycle
    Read_New_Values();
    float t_diff = Compute_Total_Diff();
    float i_diff = Compute_Idle_Diff();
    if (t_diff != 0){
        return (t_diff - i_diff)/t_diff;} 
    else 
      return 0.0;
 }