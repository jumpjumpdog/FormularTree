#pragma once
#ifndef FORMULATREE
#define FORMULATREE

#include"iostream"
#include"stack"
#include"string"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::stack;

bool isSymbol(int);
struct Node {
	int data;

	Node* lchild;
	Node* rchild;

	Node() :data(NULL),lchild(NULL),rchild(NULL){};
	Node(int p) :data(p), lchild(NULL), rchild(NULL) {};
};



class FormulaTree
{
public:
	FormulaTree(stack<int>);
	~FormulaTree();

	void create(Node* & , stack<int>&);
	void frontTranverse(Node*);
	void backTranverse(Node*);
	void midTranverse(Node*); 

 
	Node* root;
};
  

#endif // !FORMULATREE


