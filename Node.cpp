#include <iostream>
#include <cstring>
#include "Node.h"

using namespace std;

Node:: Node(){
  stu = new student();
  next = NULL;
}
Node::Node(student* newstudent){
  next = NULL;
  stu = newstudent;
  
}

Node :: ~Node(){
  delete stu;
  next = NULL;
}

void Node :: setNext(Node* newnext){
  next = newnext;
}

Node* Node:: getNext(){
  return next;
}

void Node :: setStudent(student* newstudent){
  stu = newstudent;
}

student* Node :: getStudent(){
  return stu;
}
