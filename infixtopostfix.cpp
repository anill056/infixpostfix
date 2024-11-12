#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>


using namespace std;

bool greaterthanequal(char op1, char op2) { //operator precedence bool func.
	if (op1 == '*' || op1 == '/') {
		return true;
	}
	else if (op2 == '+' || op2 == '-') {
		return true;
	}
	else return false;
}

string infixtopostfix(string infix) { //intfixtopostfix function
	string postfix = "";
	stack<char> stack;

	for (int i = 0; i < infix.length(); i++) {
		char next = infix[i];
		if (isdigit(next)) {
			do {
				postfix += infix[i];
				i++;
			} while (isdigit(infix[i]));
			i--;
			postfix += " ";
		}
		else if (next == '/' || next == '*' ||
			next == '+' || next == '-')
		{
			while (!stack.empty() && stack.top() != '(') {
				if (greaterthanequal(stack.top(), next))  //op1 vs op2 ; op1>=op2
				{
					postfix += stack.top();
					postfix += " ";
					stack.pop(); //delete operator from stack
				}
				else break; //otherwise
			}
			stack.push(next);
		}
		else if (next == '(') {
			stack.push(next);
		}
		else if (next == ')')
		{
			while (!stack.empty())
			{

				if (stack.top() == '(')
				{
					stack.pop();
					break;
				}
				postfix += stack.top();
				postfix += " ";
				stack.pop();
			}
		}
	}
	while (!stack.empty())
	{
		postfix += stack.top();
		postfix += " ";
		stack.pop();
	}
	return postfix;
}

double calculatepostfix(string postfix) {
	stack<double> stack;

	for (int i = 0; i < postfix.length(); i++) {
		if (isdigit(postfix[i])) {
			string num; //string to int entered all the numbers.

			while (i < postfix.length() && isdigit(postfix[i])) {
				num += postfix[i];
				i++;
			}
			stack.push(stod(num)); //string to double convertion
			i--;
		}
		else if (postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '+' || postfix[i] == '-') {
			double val2 = stack.top();  stack.pop();
			double val1 = stack.top(); stack.pop();

			switch (postfix[i])
			{
			case '+': stack.push(val1 + val2); break;
			case '-': stack.push(val1 - val2); break;
			case '/': stack.push(val1 / val2); break;
			case '*': stack.push(val1 * val2); break;
			}
		}
	}
	return stack.top(); //sum of the problem
}

bool isbalanced(string infix) {
	stack<char> stack;
	for (int i = 0; i < infix.length(); i++) {
		char ch = infix[i];
		if (ch == '(') {
			stack.push(ch);
		}
		else if (ch == ')') {
			if (stack.empty() || stack.top() != '(') { //if there is no closing parenthesis for the opening
				return false;
			}
			stack.pop(); //delete '('
		}
	}
	return stack.empty(); //check all parenthesis whether are balanced or not.
}

int main() {
	
		string infix;
		cout << "Enter an infix expression: ";
		getline(cin, infix);

		if (!isbalanced(infix)) {
			cout << "\nBrackets are not balanced!" << endl;
			return 1;
		}
		else {
			cout << "\nBrackets are balanced!" << endl;
		}

		string postfix = infixtopostfix(infix);
		cout << "\nInfix converted to postfix: " << postfix << endl;

		double result = calculatepostfix(postfix);
		cout << "\nCalculation result: " << result << endl;

		return 0;
}

