//
// Created by Razvan Lung on 2019-07-04.
//

#ifndef SYS_INFO_H_
#define SYS_INFO_H_

#include <string>
#include <iostream>
#include <vector>
#include "ProcessParser.h"

class SysInfo {
 private:
  vector<string> last_cpu_stats_;
  vector<string> current_cpu_stats_;
  vector<string> cores_stats_;
  vector<vector<string>> last_cpu_cores_stats_;
  vector<vector<string>> current_cpu_cores_stats_;
  float cpu_percent_;
  float mem_percent_;
  string os_name_;
  string kernel_ver_;
  long up_time_;
  int total_proc_;
  int running_proc_;
  int threads_;

 public:
  SysInfo() {
    GetOtherCores(ProcessParser::GetNumberOfCores());
    SetLastCpuMeasures();
    SetAttributes();
    os_name_ = ProcessParser::GetOSName();
    kernel_ver_ = ProcessParser::GetSysKernelVersion();
  }

  float mem_percent() const;
  long up_time() const;
  int threads() const;
  int total_proc() const;
  int running_proc() const;
  string kernel_ver() const;
  string os_name() const;
  float cpu_percent() const;

  void SetAttributes();
  void SetLastCpuMeasures();
  void GetOtherCores(int _size);
  void SetCpuCoresStats();
  vector<string> GetCoresStats() const;
};

#endif /* SYS_INFO_H_ */
