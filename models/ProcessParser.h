//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <fstream>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <thread>
#include <chrono>
#include <iterator>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cerrno>
#include <cstring>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include "../utils/constants.h"
#include "../utils/util.h"

using namespace std;

class ProcessParser {

 private:
  ifstream stream_;

 public:
  static string GetCmd(int pid);
  static vector<string> GetPidList();
  static float GetVmSize(int pid);
  static float GetCpuPercent(int pid);
  static long int GetSysUpTime();
  static float GetProcUpTime(int pid);
  static string getProcUser(int pid);
  static vector<string> GetSysCpuPercent(int coreNumber = 0);
  static float GetSysRamPercent();
  static string GetSysKernelVersion();
  static int GetNumberOfCores();
  static int GetTotalThreads();
  static int GetTotalNumberOfProcesses();
  static int GetNumberOfRunningProcesses();
  static string GetOSName();
  static float PrintCpuStats(const vector<string> &values1, const vector<string> &values2);
  static bool IsPidExisting(int pid);

 private:
  static float GetSysIdleCpuTime(vector<string> values);
  static float GetSysActiveCpuTime(vector<string> values);
};
