//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessParser.h"

using namespace std;

class Process {
 public:
  Process();
  explicit Process(const string &pid);
  Process(int pid, string user, string cmd, float cpu, float memory, float up_time);

 public:
  int pid() const;
  void pid(int pid);
  const string &user() const;
  void user(const string &user);
  const string &cmd() const;
  void cmd(const string &cmd);
  float cpu() const;
  void cpu(float cpu);
  float memory() const;
  void memory(float memory);
  float time() const;
  void time(float time);

  string GetProcess();

 private:
  int pid_{};
  string user_;
  string cmd_;
  float cpu_{};
  float memory_{};
  float time_{};
};
