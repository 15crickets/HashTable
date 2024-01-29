#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <cstring>

using namespace std;

class student{
//initializing variables
 int id;
 float GPA;

 public:
 //declaring functions and variables.
  char first[30];
  char last[30];
  float getGPA();
  void setGPA(float tempGPA);
  int getId();
  void setId(int tempId);

};

#endif
