#include"FormulaTree.h"



void  initSymStack(stack<char>& );                            //初始化符号栈
int tranverse(char);                                         //将符号转化成特定的int
char priorityJudge(stack<char>&, char);                       //+-*/#的优先级判断
void toNiPorlandExp(stack<char>&, stack<int>&, char );       //将中缀表达式转化成后缀            
char priorityMap[5][5] = { {'=','=','>','>','<'},{ '=','=','>','>','<' },{'<','<','=','=','<'},{ '<','<','=','=','<' },{'>','>','>','>','='} };    //优先级表


int  main() {
	string str;
	stack<int>  dataStack;
	stack<char> symStack;
	getline(cin, str);                                                //完成对字符串的读取
	str  +=  "#";
	initSymStack(symStack);                                      //初始化符号栈                        
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

char priorityJudge(stack<char>&pSymbolStack,char pSymbol ) {         //优先级判断
	char temp;
	int intTemp, intSymbol;
	temp = pSymbolStack.top();
	if (temp == '(')
		return '>';

	intTemp = tranverse(temp);
	intSymbol = tranverse(pSymbol);

	return priorityMap[intTemp][intSymbol];
}


void  initSymStack(stack<char>&pSymbolStack) {                //初始符号栈

	if (pSymbolStack.empty()) {                    //如果符号栈不为空，则将符号栈的元素全部pop，然后压入栈底元素#
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




void toNiPorlandExp(stack<char>&symStack,stack<int>&dataStack, char pSymbol) {    //将中缀表达式转化为后缀表达式
	switch (pSymbol) {
	case '#': {
		while (symStack.top() != '#')
		{
			dataStack.push(symStack.top());
			symStack.pop();
		}
	};    break;
	case '(':symStack.push(pSymbol); break;
	case')': while (symStack.top() != '(') {                    //将两个括号内的符号全部弹出并压入数据栈
		dataStack.push(symStack.top());
		symStack.pop();
	}
			 symStack.pop();         break;                         //弹出左括号并舍弃
	default: if (priorityJudge(symStack, pSymbol)=='>')
		   symStack.push(pSymbol);
			 else {                                      //运算符
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

