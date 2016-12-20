#include "FormulaTree.h"

                        //判断dataStack中的元素是否为运算符

FormulaTree::FormulaTree(stack<int>pDataStack) {                        
	create(root,pDataStack);                              //create递归得到表达式树
}



FormulaTree::~FormulaTree()
{
}


bool isSymbol(int p) {                             //判断p是否为操作符
	switch (p) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '#': return true;
	};
	return false;
}



void FormulaTree::create(Node* & pNode,stack<int>&pDataStack) {   //递归创造表达树
    
	
	pNode = new Node(pDataStack.top());
	if (!isSymbol(pDataStack.top()))
	{
		pDataStack.pop();
		return;
	}
	pDataStack.pop();
	create(pNode->rchild,pDataStack);
	create(pNode->lchild,pDataStack);
	return;
}

void FormulaTree::frontTranverse(Node*pNode) {         //前序遍历
	if (NULL == pNode) 
		return;
	else {
		if (isSymbol(pNode->data))
			cout << (char)pNode->data << "   ";
		else
			cout << pNode->data << "   ";
		frontTranverse(pNode->lchild);
		frontTranverse(pNode->rchild);
	}
	
}


void FormulaTree::midTranverse(Node*pNode) {       //中序遍历
	if (NULL == pNode)
		return;
	else {
		midTranverse(pNode->lchild);
		if (isSymbol(pNode->data))
			cout << (char)pNode->data << "   ";
		else
			cout << pNode->data << "   ";
		midTranverse(pNode->rchild);
	}
}


void FormulaTree::backTranverse(Node*pNode) {           //后续遍历
	if (NULL == pNode)
		return;
	else {
		backTranverse(pNode->lchild);
		backTranverse(pNode->rchild);
		if (isSymbol(pNode->data))
			cout << (char)pNode->data << "   ";
		else
			cout << pNode->data << "   ";
	}
}


