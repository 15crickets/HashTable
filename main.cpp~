/*
Author: Vikram Vasudevan
Date: 1/3/2024
Description: This program essentially runs StudentList but using Linked Lists. Each student is linked to a node, and the nodes are linked together sequentially. When a student is added or removed, the node chain is altered to accommodate that change. This program can add students, delete them, print the students, average the GPAs of the students, and end itself.

Citations: Node.h and Node.cpp files came from Ashvika. Also, I used this website to help me figure out how to print out decimals to 2 places: https://www.geeksforgeeks.org/iomanip-setprecision-function-in-c-with-examples/




 */

#include <iostream>
#include <cstring>
#include "Node.h"
#include "student.h"
#include <iomanip>

using namespace std;
//function prototypes
void add(Node* &head, Node* current, Node* prev, int Id, float GPA, char first[30], char last[30]);
void display(Node* current);
void remove(Node* &head, Node* current, Node* prev, int deleteID);
void average(Node* current, int counter, float sum);
//main
int main(){
  Node* head = NULL;
  bool stillRunning = true;
  //while loop where code runs
  while (stillRunning == true){
    //prompt user to begin one of the functions
    cout << "Enter 'ADD', 'PRINT', 'DELETE', 'AVERAGE', or 'QUIT'" << endl;
    char input[15];
    for(int i = 0; i < 7; i++){
      input[i] = '\0';
    }
    cin.get(input, 15);
    cin.ignore(15, '\n');
    //if statements that determine what happens based on which function is called.
    if(strcmp(input, "ADD") == 0){
      //collecting information from the user about the student
      int id;
      float GPA;
      char first[30];
      char last[30];
      cout << "What is the student's first name? " << endl;
      cin.get(first, 30);
      cin.get();
      cout << "What is the student's last name? " << endl;
      cin.get(last, 30);
      cin.get();
      cout << "What is the student's ID? " << endl;
      cin >> id;
      cin.get();
      cout << "What is the student's GPA? " << endl;
      cin >> GPA;
      cin.get();
      //calling the add function
      add(head, head, head, id, GPA, first, last);

    }
    if(strcmp(input, "PRINT") == 0){
      //calling the display function
      display(head);
    }
    if(strcmp(input, "QUIT") == 0){
      //ending the while loop
      stillRunning = false;
    }
    if(strcmp(input, "AVERAGE") == 0){
      //calling the average function
      average(head, 0, 0);
    }
    if(strcmp(input, "DELETE") == 0){
      //getting the ID to be deleted.
      cout << "What ID would you like to delete?" << endl;
      int deleteID;
      cin >> deleteID;
      cin.get();
      //calling the delete function
      remove(head, head, head, deleteID);
    }
  }
  return 0;
}

//add function
void add(Node* &head, Node* current, Node* prev, int Id, float GPA, char first[30], char last[30]){
  //creating the new student and setting its values
  student* newstudent = new student();
 
  newstudent->setId(Id);
   
  strcpy(newstudent->first, first);
  
  strcpy(newstudent->last, last);
  newstudent->setGPA(GPA);

  //if there is nothing in the list, set the beginning of the list to the new student.
  if(head == NULL){
    head = new Node();
    head->setStudent(newstudent);
  }
  else{
    //create a temporary node that holds the student.
    Node* tempNode = new Node();
    tempNode->setStudent(newstudent);
    //if the ID is less than that of the head, the new node becomes the head.
    if(Id < head->getStudent()->getId()){
      Node* newTemp = head;
      head = tempNode;
      head->setNext(newTemp);
    }
    //if current is past the last node in the list, the current node becomes the new node.
    else if(current == NULL){
      current = tempNode;
      prev->setNext(current);
    }
    //if the ID is between the last node and the current node, then the node is added between them.
    else if(prev->getStudent()->getId() < Id && current->getStudent()->getId() > Id){
      prev->setNext(tempNode);
      tempNode->setNext(current);
    }
    //if none of that is true, call add again.
    else{
      add(head, current->getNext(), current, Id, GPA, first, last);
    }
    return;
  }
  return;
}
//remove function
void remove(Node* &head, Node* current, Node* prev, int deleteID){
  //if there's nothing in the list, return
  if(head == NULL){
    return;
  }
  
  else{
    //if the entered ID = the current ID, delete the node and restructure the links.
    if(current->getStudent()->getId() == deleteID){
      if(current == head){
        Node* tempNode = current->getNext();
        delete head;
        head = tempNode;
      }
      else{
        prev->setNext(current->getNext());
        delete current;
      }
    }
    //otherwise, call remove again.
    else{
      if(current->getNext()!= NULL){
        remove(head, current->getNext(), current, deleteID);
      }
      else{
        return;
      }
      return;
    }
  }
}

//display function
void display(Node* current){
  //if the current node doesn't exist, return.
  if(current == NULL){
    return;
  }
  //print out the information of the current student.
  cout << current->getStudent()->first << " " << current->getStudent()->last;
  cout << ", " << current->getStudent()->getId() << ", " << fixed << setprecision(2) << current->getStudent()->getGPA() << endl;
  //progress to the next node and the next student.
  if(current->getNext() != NULL){
    display(current->getNext());
  }
  return;

}

//average function
void average(Node* current, int counter, float sum){
  //if you've reached the end of the list, print out the average.
  if(current == NULL){
    if(counter == 0){
      cout << "There are no students in the list" << endl;
    }
    else{
      cout << "The average of all the students' GPAs is " << fixed << setprecision(2) << (sum/counter) << endl;
    }
    return;
  }
  //add the GPA to the current sum and increment the counter
  else{
    counter++;
    sum = sum + current->getStudent()->getGPA();
    average(current->getNext(), counter, sum);
  }
}
