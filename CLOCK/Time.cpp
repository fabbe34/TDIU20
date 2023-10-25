#include <iostream>
#include <string>
#include "Time.h"
using namespace std;
string under_10(int tal);
string twelve(int Timme,int Minut,int Sekund);

Time::Time(int Timme, int Minut, int Sekund)
    : Timme{Timme} , Minut{Minut}, Sekund{Sekund}
    {
      if(Timme > 24 || Timme<0)
      {
        throw logic_error{"Invalid Time format"};
      }
      if(Minut >60 || Minut<0|| Sekund >60 || Sekund <0)
      {
        throw logic_error{"Invalid Time format"};
      }
    }
Time::Time(string Time_string)
  : Timme{stoi(Time_string.substr(0,2))} , Minut{stoi(Time_string.substr(3,5))}, Sekund{stoi(Time_string.substr(6,8))}
  {
    if(Timme > 24 || Timme<0)
    {
      throw logic_error{"Invalid Time format"};
    }
    if(Minut >60 || Minut<0|| Sekund >60 || Sekund <0)
    {
      throw logic_error{"Invalid Time format"};
    }

  }
int Time::hour()
{
  return Timme;
}
int Time::minute()
{
  return Minut;
}
int Time::second()
{
  return Sekund;
}
string Time::to_string(bool b)
{
  if(!b)
  {
    return  under_10(Timme) + ":"+under_10(Minut)+ ":"+under_10(Sekund);
  }
  else
  {
    return twelve(Timme,Minut,Sekund);
  }
}
string under_10(int tal)
{
  if(tal < 10)
  {
    return "0"+to_string(tal);
  }
  else
  {
    return to_string(tal);
  }
}
string twelve(int Timme,int Minut,int Sekund)
{
  if(Timme >12)
  {
    return  under_10(Timme-12) + ":"+under_10(Minut)+ ":"+under_10(Sekund)+" pm";
  }
  else
  {
    return  under_10(Timme) + ":"+under_10(Minut)+ ":"+under_10(Sekund)+ " am";
  }
}
bool Time::is_am()
{
  if(Timme >12)
  {
    return false;
  }
  return true;
}
void Time::increment (int n)
{
  for( int i = 0; i<n ; i++)
  {Sekund+=1;
  if(Sekund ==60)
  {
    Sekund = 0;
    Minut += 1;
      if(Minut == 60)
      {
        Minut = 0;
        Timme += 1 ;
        if(Timme == 24)
        {
          Timme = 0;
        }
      }
    }
  }
}

void Time::decrement(int n )
{
  for(int i =0; i<n ; i++)
    {
      Sekund -=1;
      if(Sekund ==-1)
      {
        Sekund = 59;
        Minut -= 1;
        if(Minut==-1)
        {
          Minut = 59;
          Timme -= 1;
          if(Timme ==-1)
          {
            Timme =23;
          }
        }
      }
    }
  }
bool Time::operator<<(Time right)
{
  int Left_sek= (right.hour()*3600)+ (right.minute()*60) +right.second();
  int Right_sek= (Timme*3600) + (Minut*60) + Sekund;
  if(Right_sek < Left_sek)
  {
    return true;
  }
  return false;

}
Time::operator string()
{
  return to_string();
}
