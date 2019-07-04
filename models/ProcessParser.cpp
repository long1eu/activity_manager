//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessParser.h"

string ProcessParser::GetCmd(int pid) {
  return string();
}

vector<string> ProcessParser::GetPidList() {
  return vector<string>();
}

long ProcessParser::GetVmSize(int pid) {
  return string();
}

float ProcessParser::GetCpuPercent(int pid) {
  return string();
}

long int ProcessParser::GetSysUpTime() {
  return 0;
}

long int ProcessParser::GetProcUpTime(int pid) {
  return string();
}

string ProcessParser::getProcUser(int pid) {
  return string();
}

vector<string> ProcessParser::GetSysCpuPercent(int coreNumber) {
  return vector<string>();
}

float ProcessParser::GetSysRamPercent() {
  return 0;
}

string ProcessParser::GetSysKernelVersion() {
  return string();
}

int ProcessParser::GetNumberOfCores() {
  return 0;
}

int ProcessParser::GetTotalThreads() {
  return 0;
}

int ProcessParser::GetTotalNumberOfProcesses() {
  return 0;
}

int ProcessParser::GetNumberOfRunningProcesses() {
  return 0;
}

string ProcessParser::GetOSName() {
  return string();
}

float ProcessParser::PrintCpuStats(const vector<string> &values1, const vector<string> &values2) {
  return string();
}

bool ProcessParser::IsPidExisting(int pid) {
  return false;
}
