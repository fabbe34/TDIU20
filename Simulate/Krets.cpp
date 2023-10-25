#include "Krets.h"

using namespace std;
Connection::Connection(std::string n):
  Charge{0},name{n}
{  }
Connection& Connection::operator=(double const & d)
{
  Charge = d;
  return *this;
}
Connection::operator double() const
{
  return Charge;
}
string Connection::get_Connection_name() const
{
  return name;
}
//-----------------------------------------------
//---------------Component---------------------------
//-----------------------------------------------

Component::Component(string  namn,Connection& Left,Connection& Right)
:name{namn},left{Left},right{Right}
{}
string Component::get_name()const
{
    return name;
}
double Component::getVoltage() const
{
  return abs(left-right);
}

//-----------------------------------------------
//---------------BATTERY---------------------------
//-----------------------------------------------
Battery::Battery(string  namn,double   Voltage,Connection& Left,Connection& Right):
Component{namn,Left,Right}, voltage{Voltage}//R�?TT
{
}
void Battery::Update(double const & )
{
  left = 0;
  right =voltage;
}
double Battery::getCurrent() const
{
  return 0;
}

//-----------------------------------------------
//---------------resistor---------------------------
//-----------------------------------------------
resistor::resistor(string namn,double Resistance,Connection& Left,Connection& Right):
Component{namn,Left,Right}, resistance{Resistance}
{
  if(resistance <=0)
  {
  
    throw Invalid_input("Negative nummber");
  }

}
double resistor::getCurrent() const
{
  return  (getVoltage()) /resistance ;
}

void resistor::Update(double const & d)
{
  double value= (d* (getVoltage()/resistance));
  left= left-value;
  right = right + value;
}
//-----------------------------------------------
//--------------capacitance---------------------------
//-----------------------------------------------

Capacitor::Capacitor(string  namn,double farad,Connection& Left,Connection& Right):
  Component{namn,Left,Right}, Farad{farad}, voltage{0}, curr{0}
{
  if(farad <=0)
  {
    throw Invalid_input("Negative nummber");
  }
}
double Capacitor::getCurrent() const
{
  return (Farad *(getVoltage()-voltage));
}

void Capacitor::Update(double const & d)
{
  double temp= Farad *(getVoltage()-voltage)*d;
  voltage +=temp;
  if(left < right)
  {
    right = right -temp;
    left = left +temp;
  }
  else if(left >= right )
  {
    left = left-temp;
    right = right +temp;
  }
}
//-----------------------------------------------
//--------------Net--------------------------------
//-----------------------------------------------
Net::Net(double it , double  loop , double Time ):
  Comp{},Cone{},iterationer{it},utskrift{loop},time{Time}
{

}
void Net::addComponent(Component* const & n )
{

  Comp.push_back(n);
}

Connection& Net::operator()(std::string const & n) const
{
  Connection* tmp;
  bool NAME_EXIST{false};
  for(int i =0; i <int(Cone.size());i++)
  {
    if(n == Cone[i]->get_Connection_name())
    {
      tmp = Cone[i];
      NAME_EXIST = true;
      break;
    }
  }
  
  if(!NAME_EXIST)
  {

    throw Invalid_input("Connection dosent exist ");
  }
  return *tmp;
}
void Net::addConnection(string const & n)
{
  for(int i =0 ; i < int(Cone.size()); i++)
  {
    if(n == Cone[i]->get_Connection_name())
    {
      throw Invalid_input("Connection already exist");
    }
  }
  Cone.push_back(new Connection{n});
}
void Net::simulate() const
{
  //Utskrift
  for(int i = 0;  i <int(Comp.size());i++)
  {
    cout <<setw(16)<<Comp[i]->get_name();
  }
  cout<<endl;
  for(int i = 0;  i <int(Comp.size());i++)
  {
    cout <<setw(8)<<"Volt"<<setw(8)<<"Curr";
  }
  cout<<endl;
  for(int o=0 ; o<utskrift;o++)
  {
    //Simulering av krets
    for (int c=0; c <  iterationer/utskrift; c++)
	   {
	    for( int i=0; i < int(Comp.size()); i++)
	    {
		      Comp[i]->Update(time);
	    }
	   }
    //Utskrift
    for(int i = 0;  i <int(Comp.size());i++)
    {
      cout<<std::setprecision(2)<<fixed<<setw(8)<<Comp[i]->getVoltage()<<setw(8)<< Comp[i]->getCurrent();
    }
    cout<<endl;
  }
}
Net::~Net()
{
    for(int i =0; i <int(Comp.size()) ; i++)
    {
        delete Comp[i];
    }
    for(int i =0; i <int(Cone.size()) ; i++)
    {
        delete Cone[i];
    }
}
