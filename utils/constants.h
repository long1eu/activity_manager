//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <string>

using namespace std;

enum class CpuStates {
  kUser, kNice, kSystem, kIdle, kIoWait, kIrq, kSoftIrq, kSteal, kGuest, kGuestNice
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
// Users/long1eu/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/191.7479.33/CLion.app/Contents/bin/cmake/mac/bin/cmake"
// --build /Users/long1eu/CLionProjects/activity_manager/cmake-build-debug --target activity_manager -- -j 4//[100%] Built target activity_manager