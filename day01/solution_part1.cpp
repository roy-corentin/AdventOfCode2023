#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Solution {
public:
  int calibration(std::vector<std::string> &list) {
    int result = 0;

    for (std::string line : list)
      result += calibrate_line(line);

    return result;
  }

private:
  int calibrate_line(std::string line) {
    int left = 0;
    int right = line.length() - 1;
    while (left < right) {
      if (line[left] < '0' || line[left] > '9')
        left++;
      if (line[right] < '0' || line[right] > '9')
        right--;

      if (line[left] >= '0' && line[left] <= '9' && line[right] >= '0' &&
          line[right] <= '9')
        return ((line[left] - '0') * 10) + (line[right] - '0');
    }

    return 0;
  }
};

int main() {
  std::unique_ptr<Solution> soluce = std::make_unique<Solution>();
  std::vector<std::string> list;

  std::ifstream datafile("data1.txt");

  if (datafile.is_open()) {
    std::string line;
    while (datafile) {
      std::getline(datafile, line);
      list.push_back(line);
    }
  }
  std::cout << soluce->calibration(list) << std::endl;
  return 0;
}
