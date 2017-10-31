#include "utmatrix.h"
#include <gtest.h>

// ТИПИЗИРОВАННЫЕ ТЕСТЫ
// https://github.com/google/googletest/blob/master/googletest/docs/AdvancedGuide.md#typed-tests
// sample: https://github.com/google/googletest/blob/master/googletest/samples/sample6_unittest.cc

// СПОСОБ 1
// типизированный класс
template <class T>
class MatrixTest : public testing::Test {
 protected:
   TMatrix<T> m1;
   TMatrix<T> m2;
   TMatrix<T> m3;

public:
  MatrixTest() : m1(5), m2(5), m3(5) 
  {
    for (int i = 0; i < 5; i++)
      for (int j = i; j < 5; j++)
        m1[i][j] = (T)(i * 5 + j);

    for (int i = 0; i < 5; i++)
      for (int j = i; j < 5; j++)
        m2[i][j] = (T)(2*(i * 5 + j));

    for (int i = 0; i < 5; i++)
      for (int j = i; j < 5; j++)
        m3[i][j] = (T)(3*(i * 5 + j));
  }

  virtual ~MatrixTest() {}
};

// список типов, которые хотим протестировать
typedef ::testing::Types<int, double> MyTypes;
// св¤зываем класс и типы
TYPED_TEST_CASE(MatrixTest, MyTypes);

// тесты
TYPED_TEST(MatrixTest, can_add)
{
  EXPECT_EQ(m3, m1 + m2);
}

TYPED_TEST(MatrixTest, can_substract)
{
  EXPECT_EQ(m1, m3 - m2);
}

//----------------------------------------------------------------------------------------------
// СПОСОБ 2
// типизированный класс (здесь - такой же, как предыдущий)
template <class T>
class MatrixTest2 : public MatrixTest<T> {
};

// что будем тестировать
TYPED_TEST_CASE_P(MatrixTest2);

// тесты
TYPED_TEST_P(MatrixTest2, can_add)
{
  EXPECT_EQ(m3, m1 + m2);
}

TYPED_TEST_P(MatrixTest2, can_substract)
{
  EXPECT_EQ(m1, m3 - m2);
}

// перечисл¤ем все тесты
REGISTER_TYPED_TEST_CASE_P(
  MatrixTest2, // им¤ класса
  can_add, can_substract); // тесты

// перечисл¤ем все типы
typedef ::testing::Types<int, double> MyTypes2;

INSTANTIATE_TYPED_TEST_CASE_P(ParameterizedMatrix, // название реализации
                              MatrixTest2,         // название тестируемой группы
                              MyTypes2);           // название типов 
