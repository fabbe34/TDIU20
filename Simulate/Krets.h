#ifndef Krets_H
#define Krets_H
#include <iostream>
#include <vector>
#include <iomanip>
class Connection
{
private:
  double Charge  ;
  std::string name;
public:
  Connection(std::string n);
  Connection& operator=(double const & d);
  operator double() const ;
  std::string get_Connection_name()const ;
};

class Component
{
private:
  std::string name;
protected:
  Connection& left;
  Connection& right;
public:
  Component( std::string  namn,Connection& Left,Connection& Right );
  virtual ~Component()=default;
  virtual void Update(double const & d)=0;
  virtual double getCurrent() const =0;
  double getVoltage() const;
  std::string get_name()const ;
};

class Battery: public Component
{
private:
  double voltage;
public:
  Battery(std::string  namn,double   Voltage,Connection& Left,Connection& Right);
  void Update(double const & d)  override ;
  double getCurrent()const  override ;

};



class resistor: public Component
{
private:
  double resistance;
public:
  resistor(std::string namn,double Resistance,Connection& Left,Connection& Right);
  void Update(double const & d) override;
  double getCurrent()  const override;
};
class Capacitor: public Component
{
private:
  double Farad;
  double voltage;
  double curr;
public:
  Capacitor(std::string namn,double farad,Connection& Left,Connection& Right);
  void Update(double const & d)  override;
  double getCurrent() const  override;
};
class Net
{
private:
std::vector<Component*> Comp;
std::vector<Connection*> Cone;
double iterationer,utskrift,time;
public:
  ~Net();
  Net(double it , double loop , double Time ) ;
  void addComponent(Component* const &n);
  void addConnection(std::string const & n);
  void simulate()const ;
  Connection& operator()(std::string const & n) const;
};

class Invalid_input : std::invalid_argument
{
public:
using invalid_argument::invalid_argument;
};
#endif
