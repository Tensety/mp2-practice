#include <gtest/gtest.h>
#include <utility>
#include "stack.h"

TEST(Stack, can_create_stack_with_positive_size) {
    ASSERT_NO_THROW(Stack<int> s(5));
}

TEST(Stack, throws_when_create_stack_with_zero_size) {
    ASSERT_ANY_THROW(Stack<int> s(0));
}

TEST(Stack, throws_when_create_stack_with_negative_size) {
    ASSERT_ANY_THROW(Stack<int> s(-5));
}

TEST(Stack, throws_when_create_too_large_stack) {
    ASSERT_ANY_THROW(Stack<int> s(MAX_STACK_SIZE + 1));
}

TEST(Stack, new_stack_is_empty) {
    Stack<int> s(3);
    EXPECT_TRUE(s.isEmpty());
}

TEST(Stack, stack_becomes_full_at_max_capacity) {
    Stack<int> s(2);
    s.push(1);
    s.push(2);
    EXPECT_TRUE(s.isFull());
}

TEST(Stack, can_get_size_of_stack) {
    Stack<int> s(5);
    s.push(1);
    s.push(2);
    EXPECT_EQ(2, s.size());
}

TEST(Stack, can_push_and_get_top_element) {
    Stack<int> s(3);
    s.push(10);
    EXPECT_EQ(10, s.top());
}

TEST(Stack, can_pop_element) {
    Stack<int> s(3);
    s.push(10);
    s.push(20);
    s.pop();
    EXPECT_EQ(10, s.top());
}

TEST(Stack, throws_when_push_to_full_stack) {
    Stack<int> s(1);
    s.push(1);
    ASSERT_ANY_THROW(s.push(2));
}

TEST(Stack, throws_when_pop_from_empty_stack) {
    Stack<int> s(3);
    ASSERT_ANY_THROW(s.pop());
}

TEST(Stack, throws_when_get_top_from_empty_stack) {
    Stack<int> s(3);
    ASSERT_ANY_THROW(s.top());
}

TEST(Stack, copied_stack_is_equal_to_source_one) {
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);
    Stack<int> s2(s1);
    EXPECT_TRUE(s1 == s2);
}

TEST(Stack, copied_stack_has_its_own_memory) {
    Stack<int> s1(3);
    s1.push(1);
    Stack<int> s2(s1);
    s2.push(2);
    EXPECT_TRUE(s1 != s2);
}

TEST(Stack, can_assign_stacks_of_different_size) {
    Stack<int> s1(5), s2(2);
    s1.push(1);
    s2.push(2);
    s1 = s2;
    EXPECT_TRUE(s1 == s2);
}

TEST(Stack, can_assign_stacks_of_equal_size) {
    Stack<int> s1(3), s2(3);
    s1.push(1);
    s2.push(2);
    s1 = s2;
    EXPECT_TRUE(s1 == s2);
}

TEST(Stack, stacks_with_different_elements_are_not_equal) {
    Stack<int> s1(3), s2(3);
    s1.push(1);
    s2.push(2);
    EXPECT_FALSE(s1 == s2);
}

TEST(Stack, can_move_stack) {
    Stack<int> s1(3);
    s1.push(1);
    s1.push(2);
    Stack<int> s2(std::move(s1));
    EXPECT_EQ(2, s2.size());
}

TEST(Stack, can_move_assign_stack) {
    Stack<int> s1(3), s2(3);
    s2.push(1);
    s2.push(2);
    s1 = std::move(s2);
    EXPECT_EQ(2, s1.size());
}