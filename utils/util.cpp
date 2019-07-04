//
// Created by Razvan Lung on 2019-07-04.
//

#include "util.h"

string Util::ConvertToTime(long int input_seconds) {
  long minutes = input_seconds / 60;
  long hours = minutes / 60;
  long seconds = int(input_seconds % 60);
  minutes = int(minutes % 60);

  return to_string(hours) + ":" + to_string(minutes) + ":" + to_string(seconds);
}

string Util::GetProgressBar(const float &percent) {
  stringstream result;
  result << "0%% ";

  int _size = 50;
  int boundaries;

  try {
    boundaries =
        percent / 100 * _size; // NOLINT(bugprone-narrowing-conversions,cppcoreguidelines-narrowing-conversions)
  } catch (...) {
    boundaries = 0;
  }

  for (int i = 0; i < _size; i++) {
    if (i < boundaries) {
      result << "|";
    } else {
      result << " ";
    }
  }

  result << " " + to_string(percent).substr(0, 5) << " /100%%";
  return result.str();
}

ifstream Util::GetStream(const string &path) {
  ifstream stream;
  stream.open(path, ifstream::in);
  if (!stream && !stream.is_open()) {
    stream.close();
    throw runtime_error("Non-existing PID.");
  }

  return stream;
}
