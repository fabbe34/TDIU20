#include "SortedList.h"
using namespace std;
SortedList::SortedList():
First{new Node{0, nullptr, nullptr}},Last{First}
{}
SortedList::SortedList(std::initializer_list<int> n):
First{new Node{0, nullptr, nullptr}}, Last{First}
{
  for ( auto v : n )
  {
    Insert(v);
  }
}
SortedList::SortedList(SortedList const& p):
First{new Node{0,nullptr,nullptr}}, Last{First}
{
  
  Node*tmp{p.Index(0)};
  while(tmp != nullptr)
  {
    Insert(tmp->Data);
    tmp = tmp -> Next;
  }
}
SortedList::SortedList(SortedList && p):
First{new Node{0,nullptr,nullptr}}, Last{First}
{
  swap(First,p.First);
  swap(Last,p.Last);
}
SortedList::~SortedList()
{
  delete First;
}
SortedList::Node::~Node()
{
  delete Next;   
}
bool SortedList::Empty() const
{
  if(First->Next == nullptr)
  {
    return true;
  }
  return false;
}
bool SortedList::operator==(SortedList const & rhs)const
{
  if((rhs.Empty() & !Empty()) ||(!rhs.Empty() & Empty() ))
  {
    return false;
  }
  Node*Right{rhs.First};
  Node *Left{First};
  while(Right->Next != nullptr)
  {
    if(Left != Right)
    {
      return false;
    }
    if(Left->Next !=nullptr)
    {
      Left= Left->Next;
    }
    else 
    {
      return false;
    }
    Right = Right ->Next;
  }
  return true;
}

void SortedList::Insert(const int & n)
{
  Node* t{First};
  if(t ->Next != nullptr)
  {
    while(n >t->Next->Data)
    {
      t = t->Next;
      if(t->Next == nullptr)
      {
        break;
      }
    }
  }
  t->Next  = new Node{n, t->Next,t};
  if(t->Next->Data > Last->Data)
  {
    Last = t->Next;
  }
  if(t->Next->Next != nullptr)
  {
    t->Next->Next->Prev = t->Next;
  }
}
void SortedList::RemoveElement(const int & n)
{
  if(!Empty())
  {
    Node* tmp{First};
    for(int i =0 ; i<n ;i++)
    {
      tmp = tmp ->Next;
      if(tmp->Next == nullptr)
      {
      throw std::out_of_range ("Invalid index");  
      }
    }
    Node* Delete{tmp->Next};
    if(tmp->Next->Next != nullptr)
    {
      tmp->Next = tmp->Next->Next;
      tmp->Next->Prev= tmp;
      Delete->Next = nullptr;  
    }
    else
    {
      Last = tmp;
      tmp->Next =nullptr;
    }
    delete Delete;
    }
  else
  {
   throw std::out_of_range ("Empty list"); 
  }
}
int SortedList::First_value()const
{
  if(!Empty())
  {
    return First->Next->Data;
  }
  else
  {
    throw std::out_of_range ("Empty list");
  }
}
int SortedList::Last_value() const
{
  if(!Empty())
  {
    return Last->Data;
  }
  else
  {
    throw std::out_of_range ("Empty list");
  } 
}
int SortedList::Prev_value(Node* n) 
{
  return  n ->Prev->Data;
}
int SortedList::Value(Node*n) const
{
  return n->Data;
}
SortedList::Node* SortedList::Index(const int & n) const
{  
  Node* tmp{First->Next};
  if(tmp != nullptr)
  {
    for(int i =0; i < n ;i++)
    {
      if(tmp->Next != nullptr)
      {
        tmp = tmp->Next;
      }
      else 
      {
        throw std::out_of_range ("Invalid index");
      }
    } 
    return tmp; 
    }
  else
  {
    throw std::out_of_range ("Empty List");
  }
}

SortedList& SortedList::operator=(SortedList && rhs)
{
  swap(First, rhs.First);
  swap(Last, rhs.Last);
  return *this;
}

SortedList& SortedList::operator=( SortedList const & copyList)
{    
  SortedList tmp{copyList};
  Node * tmp_L {tmp.First};
  Node* tmp_First{this->First};
  while(tmp_L->Next != nullptr)
  {
    if(tmp_First ->Next!=nullptr)
    {
      swap(tmp_First,tmp_L);
      tmp_First= tmp_First->Next;
    }
    else
    {
      Insert(tmp_L->Data);
    }
    tmp_L = tmp_L->Next;     
  } 
  swap(First,tmp.First);
  swap(Last,tmp.Last);
  return *this;
}
string SortedList::to_string() const
{
  string text ="";
  if(!Empty())
  {
    Node* t{First->Next};
    while(t != nullptr)
    {
      text += std::to_string(t->Data) +",";
      t = t->Next;
    }
  }
  return text.substr(0,text.size()-1);
}
std::ostream &operator<<( std::ostream &output, const SortedList & D )
{
  output << D.to_string();
  return output;
}

//-------------------------------------------------
//-----------ITERATORER----------------------------
//-------------------------------------------------
SortedList::Node* SortedList::begin() const
{
  return First->Next;
}
SortedList::Node* SortedList::end()const
{
  return Last;
}
SortedList::Iterator::Iterator(Node* Posi):
current{Posi}
{ }
SortedList::Iterator& SortedList::Iterator::operator++()
{
  if(current->Next !=nullptr)
  {
    current = current ->Next;
  }
  return *this;
}
SortedList::Iterator& SortedList::Iterator::operator--()
{
  if(current->Prev->Prev !=nullptr)
  {
    current = current->Prev;
  }
  return *this;
}
bool SortedList::Iterator::operator!=(const Iterator& iterator)
{
  return current != iterator.current;
}
int SortedList::Iterator::operator*()
{
  return current->Data;
}