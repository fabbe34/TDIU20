#ifndef SortedList_H
#define SortedList_H
#include <iostream>
#include <initializer_list>
class SortedList
{
private:
  class Node
  {
  public:
    ~Node();
    int Data;
    Node *Next;
    Node *Prev;
  };
  Node *First;
  Node *Last;
public:
class Iterator
  {
    private:
    Node* current;
    public:
    Iterator(Node* Posi);
    Iterator& operator++();

    Iterator& operator--();
    bool operator!=(const Iterator& iterator);
    int operator*();

  };
  SortedList();
  SortedList(SortedList && p);
  SortedList(std::initializer_list<int> n);
  SortedList(SortedList const& p);
  ~SortedList();
  void RemoveElement(const int & n);
  void Insert(const int & n);
  SortedList& operator=(SortedList const& rhs);
  SortedList& operator=(SortedList && rhs);
  bool operator==(SortedList const & rhs)const; 
  int First_value()const;
  int Last_value()const;
  int Prev_value(Node* n);
  Node* Index(const int & n) const;
  int Value( Node* n) const;
  bool Empty()const ;
  Node* begin() const;
  Node* end() const;
  std::string to_string()const;
};
std::ostream &operator<<( std::ostream &output, const SortedList & D );
#endif
