//
// Created by Razvan Lung on 2019-07-04.
//


#include <string>
#include "ProcessParser.h"

using namespace std;

class Process {
 public:
  Process();
  explicit Process(const string &pid);
  Process(int pid, string user, string cmd, float cpu, long memory, long up_time);

 public:
  int pid() const;
  void pid(int pid);
  const string &user() const;
  void user(const string &user);
  const string &cmd() const;
  void cmd(const string &cmd);
  float cpu() const;
  void cpu(float cpu);
  long memory() const;
  void memory(long memory);
  long time() const;
  void time(long time);

  string GetProcess();

 private:
  int pid_{};
  string user_;
  string cmd_;
  float cpu_{};
  long memory_{};
  long time_{};
};
