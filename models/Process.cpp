//
// Created by Razvan Lung on 2019-07-04.
//

#include <utility>
#include "Process.h"

Process::Process() = default;

Process::Process(const string &stringPid) {
  pid_ = stoi(stringPid);
  user_ = ProcessParser::getProcUser(pid_);

  //TODOs:
  //complete for mem
  //complete for cmd
  //complete for upTime
  //complete for cpu
}

Process::Process(int pid, string user, string cmd, float cpu, long memory, long up_time)
    : pid_(pid), user_(move(user)), cmd_(move(cmd)), cpu_(cpu), memory_(memory), time_(up_time) {}

int Process::pid() const { return pid_; }
void Process::pid(int pid) { pid_ = pid; }
const string &Process::user() const { return user_; }
void Process::user(const string &user) { user_ = user; }
const string &Process::cmd() const { return cmd_; }
void Process::cmd(const string &cmd) { cmd_ = cmd; }
float Process::cpu() const { return cpu_; }
void Process::cpu(float cpu) { cpu_ = cpu; }
long Process::memory() const { return memory_; }
void Process::memory(long memory) { memory_ = memory; }
long Process::time() const { return time_; }
void Process::time(long time) { time_ = time; }

string Process::GetProcess() {
  if (!ProcessParser::IsPidExisting(pid_)) {
    return "";
  }

  memory_ = ProcessParser::GetVmSize(pid_);
  time_ = ProcessParser::GetProcUpTime(pid_);
  cpu_ = ProcessParser::GetCpuPercent(pid_);

  return to_string(pid_) + "";
}

