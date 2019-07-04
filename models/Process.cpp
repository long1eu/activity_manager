//
// Created by Razvan Lung on 2019-07-04.
//

#include "Process.h"

Process::Process() = default;

Process::Process(const string &stringPid) {
  pid_ = stoi(stringPid);
  user_ = ProcessParser::getProcUser(pid_);
  memory_ = ProcessParser::GetVmSize(pid_);
  cmd_ = ProcessParser::GetCmd(pid_);
  time_ = ProcessParser::GetProcUpTime(pid_);
  cpu_ = ProcessParser::GetCpuPercent(pid_);
}

Process::Process(int pid, string user, string cmd, float cpu, float memory, float up_time)
    : pid_(pid), user_(move(user)), cmd_(move(cmd)), cpu_(cpu), memory_(memory), time_(up_time) {}

int Process::pid() const { return pid_; }
void Process::pid(int pid) { pid_ = pid; }
const string &Process::user() const { return user_; }
void Process::user(const string &user) { user_ = user; }
const string &Process::cmd() const { return cmd_; }
void Process::cmd(const string &cmd) { cmd_ = cmd; }
float Process::cpu() const { return cpu_; }
void Process::cpu(float cpu) { cpu_ = cpu; }
float Process::memory() const { return memory_; }
void Process::memory(float memory) { memory_ = memory; }
float Process::time() const { return time_; }
void Process::time(float time) { time_ = time; }

string Process::GetProcess() {
  if (!ProcessParser::IsPidExisting(pid_)) {
    return "";
  }

  memory_ = ProcessParser::GetVmSize(pid_);
  time_ = ProcessParser::GetProcUpTime(pid_);
  cpu_ = ProcessParser::GetCpuPercent(pid_);

  stringstream result;
  result << pid_ << "   "
         << user_ << "   "
         << to_string(memory_).substr(0, 5) << "     "
         << to_string(cpu_).substr(0, 5) << "     "
         << to_string(time_).substr(0, 5) << "    "
         << cmd_.substr(0, 30) << "...";
  return result.str();
}

