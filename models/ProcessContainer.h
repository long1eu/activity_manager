//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <vector>
#include <sstream>
#include "Process.h"
#include "ProcessParser.h"

using namespace std;

class ProcessContainer {

 private:
  vector<Process> list_;

 public:
  ProcessContainer() {
    RefreshList();
  }

  void RefreshList();
  string PrintList();
  vector<vector<string>> GetList();
};
