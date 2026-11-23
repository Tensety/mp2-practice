#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);
	
	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;
	v1[2] = 5;

	TDynamicVector<int> v2(v1);

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(4);
	v1[0] = 1;

	TDynamicVector<int> v2(v1);
	v2[0] = 99;

	ASSERT_NE(v1, v2);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

	ASSERT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(4);
	v[0] = 4;

	ASSERT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(4) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	v[0] = 7;

	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(4), v2(4);
	v1[1] = 10;

	v2 = v1;

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(5), v2(2);
	v2 = v1;

	ASSERT_EQ(5, v2.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(5), v2(2);
	v1[3] = 15;

	v2 = v1;

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(4), v2(4);
	v1[2] = 8;
	v2[2] = 8;

	ASSERT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(4);
	v[1] = 3;

	ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3), v2(4);

	ASSERT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{	
	const int k = 5;
	TDynamicVector<int> v(3), expected(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	expected[0] = 6; expected[1] = 7; expected[2] = 8;

	ASSERT_EQ(expected, v + k);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{	
	const int k = 5;
	TDynamicVector<int> v(3), expected(3);
	v[0] = 6; v[1] = 7; v[2] = 8;
	expected[0] = 1; expected[1] = 2; expected[2] = 3;

	ASSERT_EQ(expected, v - k);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	const int k = 3;
	TDynamicVector<int> v(3), expected(3);
	v[0] = 1; v[1] = 2; v[2] = 3;
	expected[0] = 3; expected[1] = 6; expected[2] = 9;

	ASSERT_EQ(expected, v * k);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), expected(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;
	expected[0] = 5; expected[1] = 7; expected[2] = 9;

	ASSERT_EQ(expected, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_different_size)
{
	TDynamicVector<int> v1(3), v2(4);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), expected(3);
	v1[0] = 5; v1[1] = 7; v1[2] = 9;
	v2[0] = 1; v2[1] = 2; v2[2] = 3;
	expected[0] = 4; expected[1] = 5; expected[2] = 6;

	ASSERT_EQ(expected, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_different_size)
{
	TDynamicVector<int> v1(3), v2(4);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	v1[0] = 1; v1[1] = 2; v1[2] = 3;
	v2[0] = 4; v2[1] = 5; v2[2] = 6;

	ASSERT_EQ(32, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_different_size)
{
	TDynamicVector<int> v1(3), v2(4);

	ASSERT_ANY_THROW(v1 * v2);
}
