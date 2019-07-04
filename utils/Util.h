//
// Created by Razvan Lung on 2019-07-04.
//

#pragma once

#include <sstream>
#include <fstream>

using namespace std;
class Util {
 public:
  static string ConvertToTime(long int input_seconds);
  static string GetProgressBar(const float &percent);
  static ifstream GetStream(const string &path);
};