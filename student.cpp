#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

//function that sets the student's id
void student::setId(int tempId){
    id = tempId;
}

//function that returns the id of the student.
int student::getId(){
    return id;
}
//function that sets the GPA of the student.
void student::setGPA(float tempGPA){
    GPA = tempGPA;
}
//functon that gets the GPA of the student
float student::getGPA(){
    return GPA;
}
