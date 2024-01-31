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
#include <array>

#include <vector>
using namespace std;
//function prototypes
void add(int Id, float GPA, char first[30], char last[30], int size, Node** &hash);
void display(Node* current);
void remove(Node* &head, Node* current, Node* prev, int deleteID);
void average(Node* current, int counter, float sum);
void hashFunction(int oldsize, int currentsize, Node** &hash);
//main
int main(){
  vector<Node*> students;
  Node* head = NULL;
  bool stillRunning = true;

  Node** hash = new Node* [100];
  for(int i = 0; i < 100; i++){
    hash[i] = NULL;
    
  }
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
      int size = 100;
      
      add(id, GPA, first, last, size, hash);

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
void add(int Id, float GPA, char first[30], char last[30], int size, Node** &hash){
  //creating the new student and setting its values
  student* newstudent = new student();

  newstudent->setId(Id);

  strcpy(newstudent->first, first);
  strcpy(newstudent->last, last);

  newstudent->setGPA(GPA);

  Node* tempNode = new Node();
  tempNode->setStudent(newstudent);
  

  int index = newstudent->getId() % size;

  if(hash[index]->getNext() == NULL || hash[index] == NULL || hash[index]->getNext()->getNext() == NULL){
    if(hash[index] == NULL){
      hash[index] = tempNode;
    }
    else if(hash[index]->getNext() == NULL){
      hash[index]->getNext()->setNext(tempNode);
    }
    else if(hash[index]->getNext()->getNext() == NULL){
      hash[index]->getNext()->getNext()->setNext(tempNode);
    }

    
  }
  
  else{
    hashFunction(size, size*2, hash);
  }


  return;
}


void hashFunction(int oldsize, int currentsize, Node** &hash){
  Node** newHash = new Node* [currentsize];
  for(int i = 0; i < currentsize; i++){
    newHash[i] = NULL;
  }

  for(int i = 0; i < oldsize; i++){
    Node* tempNode = hash[i];
    while(tempNode!=NULL){
      int index = tempNode->getStudent()->getId() % currentsize;
      Node* finalNode = newHash[index];
      while(finalNode != NULL){
	finalNode = finalNode->getNext();
      }
      finalNode = tempNode;
      tempNode = tempNode->getNext();
      
    }
    
  }

  hash = newHash;


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
