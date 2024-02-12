/*
Author: Vikram Vasudevan
Date: 2/12/2024
Description: This program takes in nodes and stores them in a hash table. It is an extension of the Linked Lists project, except that the students aren't all stored in one linked list, but are rather stored in several smaller ones that are stored in an array. 

Citations: Node.h and Node.cpp files came from Ashvika. Also, I used this website to help me figure out how to print out decimals to 2 places: https://www.geeksforgeeks.org/iomanip-setprecision-function-in-c-with-examples/. Additionally, Sophia helped me with conceptualizing how to delete students.


 */

#include <iostream>
#include <cstring>
#include "Node.h"
#include "student.h"
#include <iomanip>
#include <array>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;
//function prototypes
void rehashMechanics(Node* tempNode, Node ** &hash, Node ** & newHash, int index, bool &rehash);
void add(int Id, float GPA, char first[30], char last[30], int &size, Node** &hash);
void display(Node ** hash, int &size);
void remove(Node* &head, Node* current, Node* prev, int deleteID);
void hashFunction(int &size, int currentsize, Node** &hash, bool &rehash);
void randomize(Node ** &hash, vector<char*> first, vector <char*> last, int &size, int numPeople);
//main
int main(){
  Node* head = NULL;
  bool stillRunning = true;

  //creating the hash array and starting it with a size of 100.
  Node** hash = new Node* [100];
  int size = 100;
  for(int i = 0; i < 100; i++){
    hash[i] = NULL;
    
  }
  //creating vectors for the names
  vector<char*> firstNames;
  vector<char*> lastNames;

  fstream first_stream;
  fstream second_stream;

  //opening the files
  first_stream.open("first.txt");
  for(int i = 0; i < 20; i++){
    char* temp = new char [15];
    first_stream.getline(temp, 15);
    firstNames.push_back(temp);

  }
  first_stream.close();
  second_stream.open("last.txt");
  for(int i = 0; i < 20; i++){
    char* temp = new char[15];
    second_stream.getline(temp, 15);
    lastNames.push_back(temp);
    
  }
  
  randomize(hash, firstNames, lastNames, size, 400);
//while loop where code runs
  while (stillRunning == true){
    //prompt user to begin one of the functions
    cout << size << endl;
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
      
      add(id, GPA, first, last, size, hash);

    }
    if(strcmp(input, "PRINT") == 0){
      //calling the display function
      display(hash, size);
    }
    if(strcmp(input, "QUIT") == 0){
      //ending the while loop
      stillRunning = false;
    }
    if(strcmp(input, "DELETE") == 0){
      //getting the ID to be deleted.
      cout << "What ID would you like to delete?" << endl;

      //citation sophia
      int deleteID;
      cin >> deleteID;
      cin.get();
      int index = deleteID % size;
      
      //calling the delete function
      remove(hash[index], hash[index], hash[index], deleteID);
    }
  }
  return 0;
}

//add function
void add(int Id, float GPA, char first[30], char last[30], int &size, Node** &hash){

  //creating the new student and setting its values
  cout << "HI" << endl;
  student* newstudent = new student();

  newstudent->setId(Id);
  strcpy(newstudent->first, first);
  strcpy(newstudent->last, last);
  
  newstudent->setGPA(GPA);

  Node* tempNode = new Node();
  tempNode->setStudent(newstudent);
  

  int index = newstudent->getId() % size;
  cout << "Index: " << index << endl;

  if(hash[index] == NULL){
    cout << "1" << endl;
    hash[index] = tempNode;
  }
  else if(hash[index]->getNext() == NULL){
    cout << "2" << endl;
    hash[index]->setNext(tempNode);
  }
  else if(hash[index]->getNext()->getNext()==NULL){
    cout << "3" << endl;
    hash[index]->getNext()->setNext(tempNode);
  }
  else{
    bool rehash = true;
    cout << "4" << endl;
    hash[index]->getNext()->getNext()->setNext(tempNode);
    while(rehash == true){
      hashFunction(size, size*2, hash, rehash);
    }

  }


  return;
}


void hashFunction(int &size, int currentsize, Node** &hash, bool &rehash){

  rehash = false;
  Node** newHash = new Node*[currentsize];
  for(int i = 0; i < currentsize; i++){
    newHash[i] = NULL;

  }


  for(int i = 0; i < size; i++){
    Node* tempNode = hash[i];
    Node* secondTempNode = NULL;
    Node* thirdTempNode = NULL;
    Node* fourthTempNode = NULL;
    if(tempNode->getNext() != NULL){
      secondTempNode = tempNode->getNext();
      if(tempNode->getNext()->getNext() != NULL){
        thirdTempNode = tempNode->getNext()->getNext();
        if(tempNode->getNext()->getNext()->getNext() != NULL){
          fourthTempNode = tempNode->getNext()->getNext()->getNext();
        }
      }
    }
    int index;
    if(fourthTempNode != NULL){
      cout << "4" << endl;
      index = fourthTempNode->getStudent()->getId() % currentsize;
      rehashMechanics(fourthTempNode, hash, newHash, index, rehash);
      tempNode->getNext()->getNext()->setNext(NULL);
    }
    if(thirdTempNode != NULL){
      cout << "3" << endl;
      index = thirdTempNode->getStudent()->getId() % currentsize;
      rehashMechanics(thirdTempNode, hash, newHash, index, rehash);
      tempNode->getNext()->setNext(NULL);
    }
    if(secondTempNode != NULL){
      cout << "2" << endl;
      index = secondTempNode->getStudent()->getId() % currentsize;
      rehashMechanics(secondTempNode, hash, newHash, index, rehash);
      tempNode->setNext(NULL);
    }
    if(tempNode != NULL){
      cout << "1" << endl;
      index = tempNode->getStudent()->getId() % currentsize;
      rehashMechanics(tempNode, hash, newHash, index, rehash);
    }
    

  }
  size = size * 2;
  hash = newHash;
  return;

}

void rehashMechanics(Node* tempNode, Node ** &hash, Node ** & newHash, int index, bool &rehash){
  int iterator = 0;
  if(newHash[index] == NULL){
    newHash[index] = tempNode;
  }
  else{
    Node* finalNode = newHash[index];
    while(finalNode->getNext() != NULL){
      finalNode = finalNode->getNext();
      iterator++;
    }
    if(iterator == 3){
      rehash = true;
    }
    finalNode->setNext(tempNode);
    cout << finalNode->getStudent()->getId();
  }
  tempNode->setNext(NULL);
  cout << tempNode->getStudent()->getId() << " " << index << endl;


}
void randomize(Node ** &hash, vector<char*> first, vector <char*> last, int &size, int numPeople){
  srand(time(NULL));

  int ID = 100000;
  for(int i = 0; i < numPeople; i++){
    int randNumFirst = rand()%20;
    int randNumSecond = rand()%20;

    float GPA = (float) (rand()%(100-1+1) + 1)/25;
    cout << "First name: " <<  first.at(randNumFirst) << endl;
    cout << "Last name: " << last.at(randNumSecond) << endl;
    cout << "GPA: " << GPA << endl;
    cout << "ID: " << ID << endl;
    cout << endl;
    add(ID, GPA, first.at(randNumFirst), last.at(randNumSecond), size, hash);
    ID++;


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
void display(Node ** hash, int &size){
  //if the current node doesn't exist, return.
  for(int i = 0; i < size; i++){
    if(hash[i] != NULL){
      cout << "First name: " << hash[i]->getStudent()->first << endl;
      cout << "Last name: " << hash[i]->getStudent()->last << endl;
      cout << "ID: " << hash[i]->getStudent()->getId() << endl;
      cout << "GPA: " << hash[i]->getStudent()->getGPA() << endl;
      if(hash[i]->getNext() != NULL){
        cout << "First name: " << hash[i]->getNext()->getStudent()->first << endl;
        cout << "Last name: " << hash[i]->getNext()->getStudent()->last << endl;
        cout << "ID: " << hash[i]->getNext()->getStudent()->getId() << endl;
        cout << "GPA: " << hash[i]->getNext()->getStudent()->getGPA() << endl;
        if(hash[i]->getNext()->getNext()!=NULL){
          cout << "Name: " << hash[i]->getNext()->getNext()->getStudent()->first << endl;
          cout << "Last name: " << hash[i]->getNext()->getNext()->getStudent()->last << endl;
          cout << "ID: " << hash[i]->getNext()->getNext()->getStudent()->getId() << endl;
          cout << "GPA: " << hash[i]->getNext()->getNext()->getStudent()->getGPA() << endl;
        }

      }


   }
  }
  return;

}

