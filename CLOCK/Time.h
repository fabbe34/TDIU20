#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Time
{
private:
  int Timme,Minut,Sekund;
  string time_string;
public:
  Time(int Timme=0, int Minut=0, int Sekund=0);
  Time(string Time_string);
  int hour();
  int minute();
  int second();
  string to_string(bool b= false);
  bool is_am();
  void increment(int n =1);
  void decrement(int n =1);
  bool operator<<(Time right);
  operator string();
 
};
