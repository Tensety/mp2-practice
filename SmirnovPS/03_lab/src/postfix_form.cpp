#include "postfix_form.h"
#include "stack.h"
#include <iostream>
#include <stdexcept>

bool TPostfix::isOperand(char c) const noexcept {
	return (c >= 'a' && c <= 'z') ||
		   (c >= 'A' && c <= 'Z');
}

bool TPostfix::isOperator(char c) const noexcept {
	return c == '+' || c == '-' ||
		   c == '*' || c == '/' ||
		   c == '(' || c == ')';
}

int TPostfix::getPriority(char c) const noexcept {
	switch (c) {
	case '=': return 0;
	case '(': return 1;
	case '+': return 2;
	case '-': return 2;
	case '*': return 3;
	case '/': return 3;
	}
}

void TPostfix::transformToPostfix() {
	postfix.clear();
	if (infix.empty())
		throw std::invalid_argument("Expression is empty");

	Stack<char> s1(infix.size());
	Stack<char> s2(infix.size());

	for (char c : infix) {
		if (isOperand(c))
			s1.push(c);
		else if (isOperator(c))
			if (c == '(')
				s2.push(c);
			else if (c == ')') {
				while (!s2.isEmpty() && s2.top() != '(') {
					s1.push(s2.top());
					s2.pop();
				}
				if (s2.isEmpty())
					throw std::invalid_argument("Expression has unmatched ')' ");
				s2.pop();
			}
			else {
				while (!s2.isEmpty() && getPriority(s2.top()) >= getPriority(c)) {
					s1.push(s2.top());
					s2.pop();
				}
				s2.push(c);
			}
		else
			throw std::invalid_argument("Invalid symbol in expression");
	}

	while (!s2.isEmpty()) {
		if (s2.top() == '(')
			throw std::invalid_argument("Expression has unmatched '(' ");
		s1.push(s2.top());
		s2.pop();
	}

	while (!s1.isEmpty()) {
		s2.push(s1.top());
		s1.pop();
	}

	while (!s2.isEmpty()) {
		postfix += s2.top();
		s2.pop();
	}
}

TPostfix::TPostfix(const std::string& inf) : infix(inf) {
	if (!infix.empty())
		transformToPostfix();
}

std::string TPostfix::getInfix() const noexcept { return infix; }
std::string TPostfix::getPostfix() const noexcept { return postfix; }

void TPostfix::SetOperandValue(std::vector<std::pair<char, double>>& operands) const {
	operands.clear();
	for (char c : postfix)
		if (isOperand(c)) {
			bool exists = false;
			for (const auto& p : operands)
				if (p.first == c) {
					exists = true;
					break;
				}
			if (!exists) {
				double val;
				std::cout << "Enter value for " << c << ": ";
				std::cin >> val;
				operands.push_back({ c, val });
			}
		}
}

double TPostfix::Calculate(const std::vector<std::pair<char, double>>& operands) const {
	if (postfix.empty())
		throw std::invalid_argument("Postfix expression is empty");

	Stack<double> st(postfix.size());

	for (char c : postfix) {
		if (isOperand(c)) {
			bool found = false;
			for (const auto& p : operands)
				if (p.first == c) {
					st.push(p.second);
					found = true;
					break;
				}
			if (!found)
				throw std::invalid_argument("Operand value not found");
		}
		else {
			double right = st.top();
			st.pop();
			double left = st.top();
			st.pop();

			switch (c) {
			case '+': st.push(left + right); break;
			case '-': st.push(left - right); break;
			case '*': st.push(left * right); break;
			case '/':
				if (right == 0.0)
					throw std::invalid_argument("Division by zero");
				st.push(left / right);
				break;
			}
		}
	}

	return st.top();
}