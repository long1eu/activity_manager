//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <string>

using namespace std;

enum CpuStates {
  kUser = 1, kNice, kSystem, kIdle, kIoWait, kIrq, kSoftIrq, kSteal, kGuest, kGuestNice
};

class Path {
 public:
  static string basePath() { return "/proc/"; }
  static string cmdPath() { return "/cmdline"; }
  static string statusPath() { return "/status"; }
  static string statPath() { return "stat"; }
  static string upTimePath() { return "uptime"; }
  static string memInfoPath() { return "meminfo"; }
  static string versionPath() { return "version"; }
};