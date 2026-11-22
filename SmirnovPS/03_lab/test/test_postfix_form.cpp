#include <gtest/gtest.h>
#include "postfix_form.h"

TEST(TPostfix, default_constructor_sets_empty_infix) {
    TPostfix p;
    EXPECT_EQ("", p.getInfix());
}

TEST(TPostfix, default_constructor_sets_empty_postfix) {
    TPostfix p;
    EXPECT_EQ("", p.getPostfix());
}

TEST(TPostfix, can_get_infix_expression) {
    TPostfix p("a+b");
    EXPECT_EQ("a+b", p.getInfix());
}

TEST(TPostfix, converts_lowercase_expression_correctly) {
    TPostfix p("a+(b-c)*d-f/(g+h)");
    EXPECT_EQ("abc-d*+fgh+/-", p.getPostfix());
}

TEST(TPostfix, converts_uppercase_expression_correctly) {
    TPostfix p("A+(B-C)*D-F/(G+H)");
    EXPECT_EQ("ABC-D*+FGH+/-", p.getPostfix());
}

TEST(TPostfix, throws_on_unmatched_opening_parenthesis) {
    ASSERT_ANY_THROW(TPostfix("(a+b"));
}

TEST(TPostfix, throws_on_unmatched_closing_parenthesis) {
    ASSERT_ANY_THROW(TPostfix("a+b)"));
}

TEST(TPostfix, throws_on_invalid_character) {
    ASSERT_ANY_THROW(TPostfix("a+["));
}

TEST(TPostfix, calculates_expression_correctly) {
    TPostfix p("A+(B-C)*D-F/(G+H)");
    EXPECT_DOUBLE_EQ(17.0, p.Calculate({
        {'A', 10}, {'B', 8}, {'C', 3}, {'D', 2}, {'F', 12}, {'G', 1}, {'H', 3}
        }));
}

TEST(TPostfix, throws_when_calculate_empty_expression) {
    TPostfix p;
    ASSERT_ANY_THROW(p.Calculate({}));
}

TEST(TPostfix, throws_when_operand_value_not_found) {
    TPostfix p("a+b");
    ASSERT_ANY_THROW(p.Calculate({ {'a', 5} }));
}

TEST(TPostfix, throws_on_division_by_zero) {
    TPostfix p("a/b");
    ASSERT_ANY_THROW(p.Calculate({ {'a', 10}, {'b', 0} }));
}