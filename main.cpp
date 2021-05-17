#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <string.h>
#include "Node.h"

using namespace std;

void parseNumbers(char input[], vector<int> &integers);

Node* insert(Node* Root, int integer);

void print(char prefix[], Node* Root, bool isLeft);

Node* deleteNode(Node* Root,int value);
 
int main() {
 	Node* Root = NULL;
 	cout << "Enter '1' for console input or '2' for file input." << endl;
 	int in;
	cin >> in;
	
	vector<int> integers;
	if (in == 1) { //console input
		char input[100];
		cin.ignore(10000,'\n');
		cout << "Enter your numbers separated by spaces: " << endl;
		cin.get(input,1000);
		cin.clear();
		cin.ignore(10000,'\n');
		
		parseNumbers(input,integers);
		for(int i = 0; i < integers.size();i++){
			Root = insert(Root, integers[i]);
		}
	}
	else if(in == 2) { //file input
		cin.ignore(10000,'\n');
		cout << "Enter the name of your text file: \n>>";
		char input[1000];
		cin.get(input,100);
		cin.clear();
		cin.ignore(10000,'\n');
		
		
		ifstream myfile;
		myfile.open(input);
		
		if (!myfile) { 
			cout << "File not found.\n";
			return 0;
		}
		else {
			char fileInput[100000];
			int i = 0;
			while (!myfile.eof()) { 
				fileInput[i] = myfile.get();
				if (fileInput[i] == ' '){
					fileInput[i+1] = '\0';
				}
				i++;
			}
			fileInput[i-1] = '\0';
			myfile.close();
			parseNumbers(fileInput,integers);
			for(int i = 0; i < integers.size();i++){
				Root = insert(Root, integers[i]);
			}
		}
	}
	
	bool running = true;
	while (running) {
		cout << "Enter '1' to insert, '2' to print, '3' to delete, or '4' to quit: ";
		cin >> in;
		if (in == 1) { //insert
			cout << "Enter one integer: ";
			int newInt;
			cin >> newInt;
			Root = insert(Root,newInt);
		}
		else if (in == 2){ //print
			char* str = new char[100];
			str[0] = '\0';
			print(str,Root,false);
			delete []str;
		}
		else if (in == 3){ //delete
			cout << "Which value would you like to delete within the tree?\n>>";
			int deleteValue;
			cin >> deleteValue;
			Root = deleteNode(Root,deleteValue); 
		}
		else if (in == 4){ //quit
			running = false;
			cout << "Program has ended" << endl;
		}
	}
}

void parseNumbers(char input[], vector<int> &integers) {
	int i = 1;//input index
	int j = 0;//number index
	int spacePointers[2];
	spacePointers[0] = -1;
	while (i < strlen(input)){
		if (input[i] == ' '){
			spacePointers[1] = i;
			int number = 0;
			int exponent = 0;
			for (int k = spacePointers[1] - 1; k > spacePointers[0]; k--){
				number += (input[k] - 48) * pow(10,exponent);
				exponent++;
			}
			cout << "Number is: " << number << endl << endl;
			integers.push_back(number);
			spacePointers[0] = spacePointers[1];
		}
		i++;
	}
	int number = 0;
	int exponent = 0;
	for (int k = strlen(input)-1; k > spacePointers[0]; k--){
			number += (input[k] - 48) * pow(10,exponent);
			exponent++;
	}
	cout << "Number is: " << number << endl << endl;
	integers.push_back(number);
}

Node* insert(Node* Root, int integer) {
	if (Root == NULL) { 
		Root = new Node();
		Root->setValue(integer);
		return Root;
	}
	else if (integer == Root->getValue()) {
		cout << "Sorry, you can't enter two of the same integers.'" << endl;
	}
	else if (integer < Root->getValue()) { //move integer to left if less than root
		Root->setLeft(insert(Root->getLeft(),integer));
	}
	else if (integer > Root->getValue()) { //move integer to right if greater than root
		Root->setRight(insert(Root->getRight(),integer));
	}
	return Root;
}

void print(char prefix[], Node* Root, bool isLeft) {
	char* Prefix = NULL;
	if (Root!=NULL){
		cout << prefix << (isLeft ? "├── " : "└── ") << Root->getValue() << endl;
		if (Prefix != NULL){
			delete []Prefix;
		}
		Prefix = new char[100];
		Prefix = strcpy(Prefix,prefix);
		print(strcat(prefix,(isLeft ? "│   " : "    ")), Root->getLeft(), true);
		print(strcat(Prefix,(isLeft ? "│   " : "    ")), Root->getRight(), false);
	}
}

Node* deleteNode(Node* Root,int value){
	if (Root == NULL){
		cout << "Value not found." << endl;
		return Root;
	}
	else if (value < Root->getValue()){
		Root->setLeft(deleteNode(Root->getLeft(),value));
	}
	else if (value > Root->getValue()){
		Root->setRight(deleteNode(Root->getRight(),value));
	}
	else{
		if (Root->getLeft() == NULL){
			Node* temp = new Node();
			temp = Root->getRight();
			Root->~Node();
			return temp;
		}
		else if (Root->getRight() == NULL){
			Node* temp = new Node();
			temp = Root->getLeft();
			Root->~Node();
			return temp;
		}
		else{
			Node* parent = Root->getRight(); 
			
			// Find Minimum Node
			Node* child = Root->getRight(); 
			
			while (child->getLeft() != NULL) { 
				parent = child; 
				child = child->getLeft(); 
			}
			if (parent == child){
				Root->setRight(NULL);
				Root->setValue(child->getValue());
			}
			else{
				parent->setLeft(child->getRight());
				Root->setValue(child->getValue());
			}
			return Root;
		}
	}
	return Root;
}