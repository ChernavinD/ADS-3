// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int prior(char x) {
	if (x == '(')
		return 0;
	else if (x == ')')
		return 1;
	else if (x == '+' || x == '-')
		return 2;
	else if (x == '*' || x == '/')
		return 3;
}

std::string infx2pstfx(std::string inf) {
  TStack<char> stack1;
	std::string result = "";
	for (int i = 0; i < inf.length(); i++) {
		if (inf[i] >= '0' && inf[i] <= '9') {
			while (inf[i] >= '0' && inf[i] <= '9') {
				result += inf[i];
				i++;
			}
			result += ' ';
			i--;
		} else if (stack1.isEmpty()) {
			stack1.push(inf[i]);
    		} else if (inf[i] == '(') {
			stack1.push(inf[i]);
  		} else if (prior(inf[i]) > prior(stack1.get())) {
			stack1.push(inf[i]);
   		} else if (prior(inf[i]) <= prior(stack1.get())) {
			while (prior(inf[i]) <= prior(stack1.get())) {
				if (stack1.get() != '(' && stack1.get() != ')') {
					result += stack1.get();
					result += ' ';
				}
				stack1.pop();
				if (stack1.isEmpty())
				break;
			}
			stack1.push(inf[i]);
		} else if (inf[i] == ')') {
			stack1.pop();
			while (stack1.get() != '(') {
				result += stack1.get();
				result += ' ';
				stack1.pop();
			}
			stack1.pop();
		}
	}
	while (!stack1.isEmpty()) {
		if (stack1.get() == '(' ||
			stack1.get() == ')') {
			stack1.pop();
			continue;
		}
		result += stack1.get();
		result += ' ';
		stack1.pop();
	}
	return result;
}

int eval(std::string pst) {
  TStack<int> stack2;
	std::string temp = "";
	int a, b;
	for (int i = 0; i < pst.length(); i++) {
		if (pst[i] >= '0' && pst[i] <= '9') {
			while (pst[i] >= '0' && pst[i] <= '9') {
				temp += pst[i];
				i++;
			}
			stack2.push(atoi(temp.c_str()));
			temp = "";
		}
		else if (pst[i] != ' ') {
			b = stack2.get();
			stack2.pop();
			a = stack2.get();
			stack2.pop();
			if (pst[i] == '+') {
				stack2.push(a + b);
				pst[i] = ' ';
			} else if (pst[i] == '-') {
				stack2.push(a - b);
				pst[i] = ' ';
			} else if (pst[i] == '*') {
				stack2.push(a * b);
				pst[i] = ' ';
			} else if (pst[i] == '/') {
				stack2.push(a / b);
				pst[i] = ' ';
			}
		}
	}
	a = stack2.get();
	while (!stack2.isEmpty())
		stack2.pop();
	return a;
}
