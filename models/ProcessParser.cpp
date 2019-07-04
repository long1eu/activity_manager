//
// Created by Razvan Lung on 2019-07-04.
//

#include "ProcessParser.h"

string ProcessParser::GetCmd(int pid) {
  string line;
  ifstream stream = Util::GetStream(Path::basePath() + to_string(pid) + Path::cmdPath());
  getline(stream, line);
  return line;
}

vector<string> ProcessParser::GetPidList() {
  DIR *dir;
  vector<string> container;
  if (!(dir = opendir("/proc")))
    throw runtime_error(strerror(errno));

  while (dirent *dirp = readdir(dir)) {
    if (dirp->d_type != DT_DIR) {
      continue;
    }

    if (all_of(dirp->d_name, dirp->d_name + strlen(dirp->d_name), [](char c) { return isdigit(c); })) {
      container.emplace_back(dirp->d_name);
    }
  }

  if (closedir(dir)) {
    throw runtime_error(strerror(errno));
  }

  return container;
}

float ProcessParser::GetVmSize(int pid) {
  string line;
  string name = "VmData";
  string value;
  float result = 0.0f;

  ifstream stream = Util::GetStream(Path::basePath() + to_string(pid) + Path::statusPath());
  while (getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      result = (stof(values[1]) / float(1024 * 1024));
      break;
    }
  }

  return result;
}

float ProcessParser::GetCpuPercent(int pid) {
  string line;
  string value;
  float result;
  ifstream stream = Util::GetStream(Path::basePath() + to_string(pid) + "/" + Path::statPath());
  getline(stream, line);
  string str = line;
  istringstream buf(str);
  istream_iterator<string> beg(buf), end;
  vector<string> values(beg, end);

  float proc_up_time = ProcessParser::GetProcUpTime(pid);
  float s_time = stof(values[14]);
  float cu_time = stof(values[15]);
  float cs_time = stof(values[16]);
  float start_time = stof(values[21]);
  float uptime = ProcessParser::GetSysUpTime();
  float freq = sysconf(_SC_CLK_TCK);
  float total_time = proc_up_time + s_time + cu_time + cs_time;
  float seconds = uptime - (start_time / freq);
  result = 100.0 * ((total_time / freq) / seconds);
  return result;
}

long int ProcessParser::GetSysUpTime() {
  string line;
  ifstream stream = Util::GetStream(Path::basePath() + Path::upTimePath());
  getline(stream, line);
  istringstream buf(line);
  istream_iterator<string> beg(buf), end;
  vector<string> values(beg, end);
  return stoi(values[0]);
}

float ProcessParser::GetProcUpTime(int pid) {
  string line;
  string value;

  ifstream stream = Util::GetStream(Path::basePath() + to_string(pid) + "/" + Path::statPath());
  getline(stream, line);
  string str = line;
  istringstream buf(str);
  istream_iterator<string> beg(buf), end;

  vector<string> values(beg, end); // done!

  return stof(values[13]) / sysconf(_SC_CLK_TCK) * 1.0f;
}

string ProcessParser::getProcUser(int pid) {
  string line;
  string name = "Uid:";
  string result;
  ifstream stream = Util::GetStream(Path::basePath() + to_string(pid) + Path::statusPath());
  // Getting UID for user
  while (getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      result = values[1];
      break;
    }
  }
  stream = Util::GetStream("/etc/passwd");
  name = ("x:" + result);
  // Searching for name of the user with selected UID
  while (getline(stream, line)) {
    if (line.find(name) != string::npos) {
      result = line.substr(0, line.find(':'));
      return result;
    }
  }
  return "";
}

vector<string> ProcessParser::GetSysCpuPercent(int coreNumber) {
  string line;
  string name = "cpu" + to_string(coreNumber);
  ifstream stream = Util::GetStream(Path::basePath() + Path::statPath());
  while (getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      // set of cpu data active and idle times;
      return values;
    }
  }
  return (vector<string>());
}

float ProcessParser::GetSysRamPercent() {
  string line;
  string name1 = "MemAvailable:";
  string name2 = "MemFree:";
  string name3 = "Buffers:";

  string value;
  ifstream stream = Util::GetStream(Path::basePath() + Path::memInfoPath());
  float total_mem = 0;
  float free_mem = 0;
  float buffers = 0;
  while (getline(stream, line)) {
    if (total_mem != 0 && free_mem != 0)
      break;
    if (line.compare(0, name1.size(), name1) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      total_mem = stof(values[1]);
    }
    if (line.compare(0, name2.size(), name2) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      free_mem = stof(values[1]);
    }
    if (line.compare(0, name3.size(), name3) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      buffers = stof(values[1]);
    }
  }

  return float(100.0 * (1 - (free_mem / (total_mem - buffers))));
}

string ProcessParser::GetSysKernelVersion() {
  string line;
  string name = "Linux version ";
  ifstream stream = Util::GetStream(Path::basePath() + Path::versionPath());
  while (getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      return values[2];
    }
  }
  return "";
}

int ProcessParser::GetNumberOfCores() {
  string line;
  string name = "cpu cores";
  ifstream stream = Util::GetStream(Path::basePath() + "cpuinfo");
  while (getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      return stoi(values[3]);
    }
  }
  return 0;
}

int ProcessParser::GetTotalThreads() {
  string line;
  int result = 0;
  string name = "Threads:";
  vector<string> _list = ProcessParser::GetPidList();
  for (int i = 0; i < _list.size(); i++) {
    string pid = _list[i];
    ifstream stream = Util::GetStream(Path::basePath() + pid + Path::statusPath());
    while (getline(stream, line)) {
      if (line.compare(0, name.size(), name) == 0) {
        istringstream buf(line);
        istream_iterator<string> beg(buf), end;
        vector<string> values(beg, end);
        result += stoi(values[1]);
        break;
      }
    }
  }

  return result;
}

int ProcessParser::GetTotalNumberOfProcesses() {
  string line;
  int result = 0;
  string name = "processes";
  ifstream stream = Util::GetStream(Path::basePath() + Path::statPath());
  while (std::getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      result += stoi(values[1]);
      break;
    }
  }
  return result;
}

int ProcessParser::GetNumberOfRunningProcesses() {
  string line;
  int result = 0;
  string name = "procs_running";
  ifstream stream = Util::GetStream(Path::basePath() + Path::statPath());
  while (std::getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      istringstream buf(line);
      istream_iterator<string> beg(buf), end;
      vector<string> values(beg, end);
      result += stoi(values[1]);
      break;
    }
  }
  return result;
}

string ProcessParser::GetOSName() {
  string line;
  string name = "PRETTY_NAME=";

  ifstream stream = Util::GetStream("/etc/os-release");
  while (getline(stream, line)) {
    if (line.compare(0, name.size(), name) == 0) {
      size_t found = line.find("=");
      found++;
      string result = line.substr(found);
      result.erase(remove(result.begin(), result.end(), '"'), result.end());
      return result;
    }
  }
  return "";
}

float ProcessParser::PrintCpuStats(const vector<string> &values1, const vector<string> &values2) {
  float activeTime = GetSysActiveCpuTime(values2) - GetSysActiveCpuTime(values1);
  float idleTime = GetSysIdleCpuTime(values2) - GetSysIdleCpuTime(values1);
  float totalTime = activeTime + idleTime;

  return 100.0 * (activeTime / totalTime);
}

bool ProcessParser::IsPidExisting(int pid) {
  return false;
}

float ProcessParser::GetSysActiveCpuTime(vector<string> values) {
  return (stof(values[CpuStates::kUser]) +
      stof(values[CpuStates::kNice]) +
      stof(values[CpuStates::kSystem]) +
      stof(values[CpuStates::kIrq]) +
      stof(values[CpuStates::kSoftIrq]) +
      stof(values[CpuStates::kSteal]) +
      stof(values[CpuStates::kGuest]) +
      stof(values[CpuStates::kGuestNice]));
}

float ProcessParser::GetSysIdleCpuTime(vector<string> values) {
  return (stof(values[CpuStates::kIdle]) + stof(values[CpuStates::kIoWait]));
}