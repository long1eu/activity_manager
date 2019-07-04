//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessContainer.h"

void ProcessContainer::RefreshList() {
  vector<string> pid_list = ProcessParser::GetPidList();
  list_.clear();

  for (const string &pid : pid_list) {
    Process proc(pid);
    list_.push_back(proc);
  }
}

string ProcessContainer::PrintList() {
  stringstream result;
  for (Process &process : list_) {
    result << process.GetProcess();
  }

  return result.str();
}

vector<vector<string>> ProcessContainer::GetList() {
  vector<vector<string>> values;
  vector<string> processes;

  for (Process &process:list_) {
    processes.emplace_back(process.GetProcess());
  }

  int lastIndex = 0;
  for (int i = 0; i < processes.size(); i++) {
    if (i % 10 == 0 && i > 0) {
      vector<string> sub(&processes[i - 10], &processes[i]);
      values.push_back(sub);
      lastIndex = i;
    }
    if ((i == (list_).size() - 1) && (i - lastIndex) < 10) {
      vector<string> sub(&processes[lastIndex], &processes[i + 1]);
      values.push_back(sub);
    }
  }

  return values;
}
