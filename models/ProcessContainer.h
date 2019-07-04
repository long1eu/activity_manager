//
// Created by Razvan Lung on 2019-07-04.
//

#ifndef PROCESS_CONTAINER_H_
#define PROCESS_CONTAINER_H_

#include "Process.h"
#include "ProcessParser.h"

using namespace std;

class ProcessContainer {

 public:
  ProcessContainer() {
    RefreshList();
  }

 public:
  void RefreshList();
  string PrintList();
  vector<vector<string>> GetList();

 private:
  vector<Process> list_;
};

#endif /* PROCESS_CONTAINER_H_ */