//
// Created by Razvan Lung on 2019-07-04.
//

#include "SysInfo.h"

void SysInfo::GetOtherCores(int _size) {
  cores_stats_ = vector<string>();
  cores_stats_.resize(_size);
  last_cpu_cores_stats_ = vector<vector<string>>();
  last_cpu_cores_stats_.resize(_size);
  current_cpu_cores_stats_ = vector<vector<string>>();
  current_cpu_cores_stats_.resize(_size);
  for (int i = 0; i < _size; i++) {
    last_cpu_cores_stats_[i] = ProcessParser::GetSysCpuPercent(i);
  }
}

void SysInfo::SetLastCpuMeasures() {
  last_cpu_stats_ = ProcessParser::GetSysCpuPercent();
}

void SysInfo::SetCpuCoresStats() {
  for (int i = 0; i < current_cpu_cores_stats_.size(); i++) {
    current_cpu_cores_stats_[i] = ProcessParser::GetSysCpuPercent(i);
  }

  for (int i = 0; i < current_cpu_cores_stats_.size(); i++) {
    cores_stats_[i] =
        ProcessParser::PrintCpuStats(last_cpu_cores_stats_[i], current_cpu_cores_stats_[i]);
  }
  last_cpu_cores_stats_ = current_cpu_cores_stats_;
}

void SysInfo::SetAttributes() {
  mem_percent_ = ProcessParser::GetSysRamPercent();
  up_time_ = ProcessParser::GetSysUpTime();
  total_proc_ = ProcessParser::GetTotalNumberOfProcesses();
  running_proc_ = ProcessParser::GetNumberOfRunningProcesses();
  threads_ = ProcessParser::GetTotalThreads();
  current_cpu_stats_ = ProcessParser::GetSysCpuPercent();
  cpu_percent_ = ProcessParser::PrintCpuStats(last_cpu_stats_, current_cpu_stats_);
  last_cpu_stats_ = current_cpu_stats_;

  SetCpuCoresStats();
}

vector<string> SysInfo::GetCoresStats() const {
  vector<string> result = vector<string>();
  for (int i = 0; i < cores_stats_.size(); i++) {
    string temp = ("cpu" + to_string(i) + ": ");

    float check;
    if (!cores_stats_[i].empty()) {
      try {

        check = stof(cores_stats_[i]);
      } catch (...) {
        cout << "EEE" << endl;
      }
    }

    if (!check || cores_stats_[i] == "nan") {
      return vector<string>();
    }

    temp += Util::GetProgressBar(stof(cores_stats_[i]));
    result.emplace_back(temp);
  }
  return result;
}

float SysInfo::cpu_percent() const { return cpu_percent_; }
float SysInfo::mem_percent() const { return mem_percent_; }
long SysInfo::up_time() const { return up_time_; }
string SysInfo::kernel_ver() const { return kernel_ver_; }
int SysInfo::total_proc() const { return total_proc_; }
int SysInfo::running_proc() const { return running_proc_; }
int SysInfo::threads() const { return threads_; }
string SysInfo::os_name() const { return os_name_; }

