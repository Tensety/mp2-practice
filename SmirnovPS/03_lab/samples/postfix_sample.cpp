#include <iostream>
#include "stack.h"
#include "postfix_form.h"

int main()
{
    std::string expression;
    std::cout << "Enter expression: ";
    std::getline(std::cin, expression);

    try {
        TPostfix p(expression);
        std::cout << "Infix:   " << p.getInfix() << "\n";
        std::cout << "Postfix: " << p.getPostfix() << "\n";

        std::vector<std::pair<char, double>> operands;
        p.SetOperandValue(operands);

        double result = p.Calculate(operands);
        std::cout << "Result:  " << result << "\n";

    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
