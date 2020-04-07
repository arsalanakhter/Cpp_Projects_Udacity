#ifndef PROCESSOR_H
#define PROCESSOR_H
// Adapted from
// https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
class Processor {
 public:
  Processor();
  void Read_New_Values();
  void Store_Values_as_Prev();
  int Compute_Prev_Total_Idle();
  int Compute_Total_Idle();
  int Compute_Prev_non_Idle();
  int Compute_Total_non_Idle();
  int Compute_Prev_Total();
  int Compute_Total();
  int Compute_Total_Diff();
  int Compute_Idle_Diff();
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    int user_, prev_user_;
    int nice_, prev_nice_;
    int system_, prev_system_;
    int idle_, prev_idle_;
    int iowait_, prev_iowait_;
    int irq_, prev_irq_;
    int softirq_, prev_softirq_;
    int steal_, prev_steal_;
    int guest_;
    int guest_nice_;
};

#endif