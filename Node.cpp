#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(){
	right = NULL;
	left = NULL;
}

Node::~Node(){
}

Node* Node::getRight(){
	return right;
}

Node* Node::getLeft(){
	return left;
}

int Node::getValue(){
	return value;
}	

void Node::setLeft(Node* newLeft){
	left = newLeft;
}

void Node::setRight(Node* newRight){
	right = newRight;
}

void Node::setValue(int newValue){
	value = newValue;
}