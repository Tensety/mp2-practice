#ifndef __POSTFIX_FORM_H__
#define __POSTFIX_FORM_H__

#include <string>
#include <vector>
#include <utility>

class TPostfix {
private:
	std::string infix;
	std::string postfix;

	bool isOperand(char c) const noexcept;
	bool isOperator(char c) const noexcept;
	int getPriority(char c) const noexcept;
	void transformToPostfix();

public:
	TPostfix(const std::string& inf = "");

	std::string getInfix() const noexcept;
	std::string getPostfix() const noexcept;

	void SetOperandValue(std::vector<std::pair<char, double>>& operands) const;
	double Calculate(const std::vector<std::pair<char, double>>& operands) const;
};

#endif
