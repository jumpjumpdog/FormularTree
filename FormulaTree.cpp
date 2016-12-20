#include "FormulaTree.h"

                        //�ж�dataStack�е�Ԫ���Ƿ�Ϊ�����

FormulaTree::FormulaTree(stack<int>pDataStack) {                        
	create(root,pDataStack);                              //create�ݹ�õ����ʽ��
}



FormulaTree::~FormulaTree()
{
}


bool isSymbol(int p) {                             //�ж�p�Ƿ�Ϊ������
	switch (p) {
	case '+':
	case '-':
	case '*':
	case '/':
	case '#': return true;
	};
	return false;
}



void FormulaTree::create(Node* & pNode,stack<int>&pDataStack) {   //�ݹ鴴������
    
	
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

void FormulaTree::frontTranverse(Node*pNode) {         //ǰ�����
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


void FormulaTree::midTranverse(Node*pNode) {       //�������
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


void FormulaTree::backTranverse(Node*pNode) {           //��������
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


