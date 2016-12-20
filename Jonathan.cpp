#include"FormulaTree.h"



void  initSymStack(stack<char>& );                            //��ʼ������ջ
int tranverse(char);                                         //������ת�����ض���int
char priorityJudge(stack<char>&, char);                       //+-*/#�����ȼ��ж�
void toNiPorlandExp(stack<char>&, stack<int>&, char );       //����׺���ʽת���ɺ�׺            
char priorityMap[5][5] = { {'=','=','>','>','<'},{ '=','=','>','>','<' },{'<','<','=','=','<'},{ '<','<','=','=','<' },{'>','>','>','>','='} };    //���ȼ���


int  main() {
	string str;
	stack<int>  dataStack;
	stack<char> symStack;
	getline(cin, str);                                                //��ɶ��ַ����Ķ�ȡ
	str  +=  "#";
	initSymStack(symStack);                                      //��ʼ������ջ                        
	string temp;
	for (int i = 0; str[i] != '\0'; i++) {
		temp.clear();
		if (isdigit(str[i])) {
			while (isdigit(str[i])) {
				temp += str[i++];
			}
			dataStack.push(atoi(&temp[0]));
			i--;
			//cout << atoi(&temp[0])<<endl;
		}
		else
			toNiPorlandExp(symStack, dataStack, str[i]);
	}

	cout << endl;

	FormulaTree* forTree = new FormulaTree(dataStack);
	forTree->frontTranverse(forTree->root);
	cout << endl;
	forTree->midTranverse(forTree->root);
	cout << endl;
	forTree->backTranverse(forTree->root);
	cout << endl;

}

char priorityJudge(stack<char>&pSymbolStack,char pSymbol ) {         //���ȼ��ж�
	char temp;
	int intTemp, intSymbol;
	temp = pSymbolStack.top();
	if (temp == '(')
		return '>';

	intTemp = tranverse(temp);
	intSymbol = tranverse(pSymbol);

	return priorityMap[intTemp][intSymbol];
}


void  initSymStack(stack<char>&pSymbolStack) {                //��ʼ����ջ

	if (pSymbolStack.empty()) {                    //�������ջ��Ϊ�գ��򽫷���ջ��Ԫ��ȫ��pop��Ȼ��ѹ��ջ��Ԫ��#
		pSymbolStack.push('#');
	}
	else
	{
		while (!pSymbolStack.empty()) {
			pSymbolStack.pop();
		}
		pSymbolStack.push('#');
	}
}


int tranverse(char p) {
	switch (p) {
	case '+':return 0; break;
	case '-':return 1; break;
	case '*':return 2; break;
	case '/':return 3; break;
	case '#':return 4; break;
	};
}




void toNiPorlandExp(stack<char>&symStack,stack<int>&dataStack, char pSymbol) {    //����׺���ʽת��Ϊ��׺���ʽ
	switch (pSymbol) {
	case '#': {
		while (symStack.top() != '#')
		{
			dataStack.push(symStack.top());
			symStack.pop();
		}
	};    break;
	case '(':symStack.push(pSymbol); break;
	case')': while (symStack.top() != '(') {                    //�����������ڵķ���ȫ��������ѹ������ջ
		dataStack.push(symStack.top());
		symStack.pop();
	}
			 symStack.pop();         break;                         //���������Ų�����
	default: if (priorityJudge(symStack, pSymbol)=='>')
		   symStack.push(pSymbol);
			 else {                                      //�����
				 dataStack.push(symStack.top());
				 symStack.pop();
				 while (priorityJudge(symStack, pSymbol)=='>'||priorityJudge(symStack,pSymbol)=='=') {
					 if (symStack.top() == '#')
						 break;
					 dataStack.push(symStack.top());
					 symStack.pop();
				 }
				 symStack.push(pSymbol);
			 };  break;
	}
}

