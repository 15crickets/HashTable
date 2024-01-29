#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include "student.h"
using namespace std;

class Node{
 public:
  Node(); //default constructor
  Node(student*); //modified constructor
  ~Node(); //destructor
  
  //getters and setters
  void setNext(Node* newnext);
  Node* getNext();
  void setStudent(student* newstudent);
  student* getStudent();

  //things that are stored in the node
  student* stu;
  Node* next;
};
#endif
