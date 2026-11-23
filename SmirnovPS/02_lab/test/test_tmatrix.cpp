#include "tmatrix.h"

#include <gtest\gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m1(4);
	m1[0][0] = 5;
	m1[1][2] = 10;

	TDynamicMatrix<int> m2(m1);

	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m1(4);
	m1[0][0] = 5;

	TDynamicMatrix<int> m2(m1);
	m2[0][0] = 99;

	ASSERT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);

	ASSERT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(4);
	m[1][2] = 42;

	ASSERT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(4);

	ASSERT_ANY_THROW(m[0].at(-1) = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(4);

	ASSERT_ANY_THROW(m[0].at(4) = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(4);
	m[0][0] = 7;

	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(4), m2(4);
	m1[0][1] = 12;

	m2 = m1;

	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5), m2(2);
	m2 = m1;

	ASSERT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5), m2(2);
	m1[0][3] = 15;

	m2 = m1;

	ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(4), m2(4);
	m1[1][1] = 8;
	m2[1][1] = 8;

	ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(4);
	m[0][2] = 3;

	ASSERT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3), m2(4);

	ASSERT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), expected(3);
	m1[0][0] = 1; m1[1][1] = 2;
	m2[0][0] = 3; m2[1][1] = 4;

	expected[0][0] = 4; expected[1][1] = 6;

	ASSERT_EQ(expected, m1 + m2);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(4);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_add_scalar_to_matrix)
{	
	const int k = 5;
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 4; m[1][0] = 9;

	TDynamicMatrix<int> expected(2);
	expected[0][0] = 6; expected[0][1] = 9; expected[1][0] = 14;

	EXPECT_EQ(m + k, expected);
}

TEST(TDynamicMatrix, can_subtract_scalar_from_matrix)
{
	const int k = 3;
	TDynamicMatrix<int> m(2);
	m[0][0] = 1; m[0][1] = 4; m[1][0] = 9;

	TDynamicMatrix<int> expected(2);
	expected[0][0] = -2; expected[0][1] = 1; expected[1][0] = 6;

	EXPECT_EQ(m - k, expected);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(3), expected(3);
	m1[0][0] = 5; m1[1][1] = 7;
	m2[0][0] = 2; m2[1][1] = 4;

	expected[0][0] = 3; expected[1][1] = 3;

	ASSERT_EQ(expected, m1 - m2);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(3), m2(4);

	ASSERT_ANY_THROW(m1 - m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar)
{	
	const int k = 3;
    TDynamicMatrix<int> m(2);
    m[0][0] = 4; m[0][1] = 8; m[1][0] = 12;

    TDynamicMatrix<int> expected(2);
    expected[0][0] = 12; expected[0][1] = 24; expected[1][0] = 36;

    EXPECT_EQ(m * k, expected);
}

TEST(TDynamicMatrix, can_multiply_matrix_by_vector)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2; m[1][0] = 3;

    TDynamicVector<int> v(2);
    v[0] = 4; v[1] = 5;

    TDynamicVector<int> expected(2);

    expected[0] = 14; expected[1] = 15;

    EXPECT_EQ((m * v),expected);
}

TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_different_size) {
	TDynamicMatrix<int> m(3);
	TDynamicVector<int> v(2);
	ASSERT_ANY_THROW(m * v);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(2);
	m1[0][0] = 1; m1[0][1] = 2; m1[1][0] = 3;

	m2[0][0] = 4; m2[0][1] = 5; m2[1][0] = 6;

	TDynamicMatrix<int> expected(2);
	expected[0][0] = 4; expected[0][1] = 17; expected[1][0] = 18;	

	EXPECT_EQ((m1 * m2), expected);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_no_equal_size)
{
	TDynamicMatrix<int> m1(2), m2(3);

	ASSERT_ANY_THROW(m1 * m2);
}