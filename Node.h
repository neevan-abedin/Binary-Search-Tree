#ifndef NODE_H
#define NODE_H
#include <iostream>

using namespace std;

class Node{
	public:
		Node();
		~Node();
		//Getters
		Node* getRight();
		Node* getLeft();
		int getValue();
		//Setters
		void setLeft(Node* newLeft);
		void setRight(Node* newRight);
		void setValue(int newValue);
	private:
		Node* left;
		Node* right;
		int value;
};

#endif