#include <format>
#include <iostream>
#include <vector>
using namespace std;

struct Person {
  const char *name;
  int height;
  int weight;
  int time_100m_sprint;
  int distance_jumping_long;
  int distance_jumping_hight;

  int calc_score();

  void setHight(int);
  void setWeight(int);

  string introduce() {
    return format(
        R"({}'s height is {}, weight is {}, running 100m spends {}s, jumps {}cm long, and {}cm high)",
        name, height, weight, time_100m_sprint, distance_jumping_long,
        distance_jumping_hight);
  }
};

// let people feel interesting about your introduce

int main() {
  Person li_Xinting{"李新亭", 160, 50, 12, 223, 78};
  cout << li_Xinting.introduce();
}
