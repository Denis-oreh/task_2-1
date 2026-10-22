#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "../lib/include/Matrix.h"
#include "../lib/include/ConstGenerator.h"
#include "../lib/include/RandomGenerator.h"
#include "../lib/include/InputGenerator.h"
#include "../lib/include/Task1Exercise.h"
#include "../lib/include/Task2Exercise.h"

// Matrix: конструкторы
TEST(MatrixConstructors, DefaultIsEmpty)
{
    Matrix m;
    EXPECT_EQ(m.getRows(), 0u);
    EXPECT_EQ(m.getColumns(), 0u);
    EXPECT_EQ(m.toString(), "");
}

TEST(MatrixConstructors, SizedMatrixIsZeroFilled)
{
    Matrix m(3, 4);
    EXPECT_EQ(m.getRows(), 3u);
    EXPECT_EQ(m.getColumns(), 4u);
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            EXPECT_EQ(m[i][j], 0);
        }
    }
}

// Matrix: копирование и перемещение

TEST(MatrixCopy, CopyIsDeep)
{
    Matrix a(2, 2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    Matrix b = a;          // конструктор копирования
    b[0][0] = 999;

    EXPECT_EQ(a[0][0], 1);  // оригинал не изменился
    EXPECT_EQ(b[0][0], 999);
}

TEST(MatrixCopy, CopyAssignmentIsDeep)
{
    Matrix a(2, 2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    Matrix b;
    b = a;                 // оператор присваивания копированием
    b[1][1] = 777;

    EXPECT_EQ(a[1][1], 4);
    EXPECT_EQ(b[1][1], 777);
}

TEST(MatrixMove, MoveLeavesSourceEmpty)
{
    Matrix a(2, 2);
    a[0][0] = 42;

    Matrix b = std::move(a);
    EXPECT_EQ(b[0][0], 42);
    EXPECT_EQ(a.getRows(), 0u);
    EXPECT_EQ(a.getColumns(), 0u);
}

TEST(MatrixCopy, SelfAssignmentIsSafe)
{
    Matrix a(2, 2);
    a[0][0] = 5;
    a = a;                 // не должно сломаться =)
    EXPECT_EQ(a[0][0], 5);
}

// Matrix: операторы сравнения

TEST(MatrixEquality, EqualMatrices)
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(MatrixEquality, DifferentValues)
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    b[0][0] = 1;
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a != b);
}

TEST(MatrixEquality, DifferentSizes)
{
    Matrix a(2, 2);
    Matrix b(3, 3);
    EXPECT_FALSE(a == b);
}

// Matrix: ввод/вывод

TEST(MatrixIO, OutputFormat)
{
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    std::ostringstream os;
    os << m;
    EXPECT_EQ(os.str(), "2 2\n1 2\n3 4");
}

TEST(MatrixIO, InputRoundtrip)
{
    std::istringstream is("2 3\n1 2 3\n4 5 6");
    Matrix m;
    is >> m;

    EXPECT_EQ(m.getRows(), 2u);
    EXPECT_EQ(m.getColumns(), 3u);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[1][2], 6);
}

TEST(MatrixIO, InputFailsOnBadData)
{
    std::istringstream is("2 3\n1 2 3\n4 5 x");
    Matrix m;
    is >> m;
    EXPECT_FALSE(is);
}

// Generators

TEST(ConstGeneratorTest, ReturnsConstant)
{
    ConstGenerator gen(42);
    EXPECT_EQ(gen.generate(), 42);
    EXPECT_EQ(gen.generate(), 42);
    EXPECT_EQ(gen.generate(), 42);
}

TEST(RandomGeneratorTest, ValuesInRange)
{
    RandomGenerator gen(-10, 10);
    for (int i = 0; i < 1000; i++)
    {
        int v = gen.generate();
        EXPECT_GE(v, -10);
        EXPECT_LE(v, 10);
    }
}

TEST(RandomGeneratorTest, SwapsMinMaxIfReversed)
{
    RandomGenerator gen(10, -10);   // нарочно наоборот
    for (int i = 0; i < 100; i++)
    {
        int v = gen.generate();
        EXPECT_GE(v, -10);
        EXPECT_LE(v, 10);
    }
}

TEST(InputGeneratorTest, ReadsFromStream)
{
    std::istringstream is("10 20 30");
    InputGenerator gen(is);
    EXPECT_EQ(gen.generate(), 10);
    EXPECT_EQ(gen.generate(), 20);
    EXPECT_EQ(gen.generate(), 30);
}

// Task1: заменить максимальный элемент каждой строки нулем

TEST(Task1Test, SimpleCase)
{
    // Строка 0: максимум 5 (col 1) -> 0
    // Строка 1: максимум 9 (col 0) -> 0
    // Строка 2: максимум 8 (col 2) -> 0
    Matrix m(3, 3);
    int data[3][3] =
    {
        {1, 5, 3},
        {9, 2, 4},
        {6, 7, 8}
    };
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
            m[i][j] = data[i][j];

    RandomGenerator dummyGen(0, 0);
    Task1Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[0][1], 0);
    EXPECT_EQ(result[0][2], 3);

    EXPECT_EQ(result[1][0], 0);
    EXPECT_EQ(result[1][1], 2);
    EXPECT_EQ(result[1][2], 4);

    EXPECT_EQ(result[2][0], 6);
    EXPECT_EQ(result[2][1], 7);
    EXPECT_EQ(result[2][2], 0);
}

TEST(Task1Test, FirstMaxInRowIsReplaced)
{
    // Максимум 7 встречается дважды в строке; заменяется первый
    Matrix m(1, 4);
    m[0][0] = 7; m[0][1] = 1; m[0][2] = 7; m[0][3] = 2;

    RandomGenerator dummyGen(0, 0);
    Task1Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[0][1], 1);
    EXPECT_EQ(result[0][2], 7);
    EXPECT_EQ(result[0][3], 2);
}

TEST(Task1Test, NegativeMaximum)
{
    // Все отрицательные: максимум -1 в col 1
    Matrix m(1, 3);
    m[0][0] = -5; m[0][1] = -1; m[0][2] = -3;

    RandomGenerator dummyGen(0, 0);
    Task1Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result[0][0], -5);
    EXPECT_EQ(result[0][1], 0);
    EXPECT_EQ(result[0][2], -3);
}

TEST(Task1Test, SingleColumn)
{
    Matrix m(3, 1);
    m[0][0] = 4;
    m[1][0] = 9;
    m[2][0] = 2;

    RandomGenerator dummyGen(0, 0);
    Task1Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[1][0], 0);
    EXPECT_EQ(result[2][0], 0);
}

TEST(Task1Test, OriginalIsNotModified)
{
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    RandomGenerator dummyGen(0, 0);
    Task1Exercise task(m, dummyGen);
    task.solve();

    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][1], 4);
}

TEST(Task1Test, EmptyMatrixReturnsEmpty)
{
    Matrix m;
    RandomGenerator dummyGen(0, 0);
    Task1Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result.getRows(), 0u);
    EXPECT_EQ(result.getColumns(), 0u);
}

// Task2: вставить перед строками, первый элемент которых делится на 3, строку из нулей

TEST(Task2Test, SimpleCase)
{
    // Первые элементы: 3 (делится), 1 (нет), 6 (делится)
    Matrix m(3, 2);
    m[0][0] = 3; m[0][1] = 4;
    m[1][0] = 1; m[1][1] = 2;
    m[2][0] = 6; m[2][1] = 8;

    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    Matrix result = task.solve();

    // Ожидается: 0-строка, 3 4, 1 2, 0-строка, 6 8
    EXPECT_EQ(result.getRows(), 5u);
    EXPECT_EQ(result.getColumns(), 2u);

    EXPECT_EQ(result[0][0], 0); EXPECT_EQ(result[0][1], 0);
    EXPECT_EQ(result[1][0], 3); EXPECT_EQ(result[1][1], 4);
    EXPECT_EQ(result[2][0], 1); EXPECT_EQ(result[2][1], 2);
    EXPECT_EQ(result[3][0], 0); EXPECT_EQ(result[3][1], 0);
    EXPECT_EQ(result[4][0], 6); EXPECT_EQ(result[4][1], 8);
}

TEST(Task2Test, NoRowsInserted)
{
    Matrix m(2, 2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 2; m[1][1] = 4;

    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result.getRows(), 2u);
    EXPECT_EQ(result[0][0], 1);
    EXPECT_EQ(result[1][1], 4);
}

TEST(Task2Test, AllRowsInserted)
{
    Matrix m(2, 2);
    m[0][0] = 3; m[0][1] = 1;
    m[1][0] = 9; m[1][1] = 2;

    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result.getRows(), 4u);
    EXPECT_EQ(result[0][0], 0);
    EXPECT_EQ(result[1][0], 3);
    EXPECT_EQ(result[2][0], 0);
    EXPECT_EQ(result[3][0], 9);
}

TEST(Task2Test, ZeroIsDivisibleByThree)\
{
    // 0 % 3 == 0 -> строка из нулей вставляется
    Matrix m(1, 2);
    m[0][0] = 0; m[0][1] = 5;

    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result.getRows(), 2u);
    EXPECT_EQ(result[0][0], 0); EXPECT_EQ(result[0][1], 0);
    EXPECT_EQ(result[1][0], 0); EXPECT_EQ(result[1][1], 5);
}

TEST(Task2Test, NegativeDivisibleByThree)
{
    // -6 % 3 == 0 -> вставляется
    Matrix m(1, 2);
    m[0][0] = -6; m[0][1] = 7;

    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result.getRows(), 2u);
    EXPECT_EQ(result[0][0], 0); EXPECT_EQ(result[0][1], 0);
    EXPECT_EQ(result[1][0], -6); EXPECT_EQ(result[1][1], 7);
}

TEST(Task2Test, OriginalIsNotModified)
{
    Matrix m(2, 2);
    m[0][0] = 3; m[0][1] = 1;
    m[1][0] = 1; m[1][1] = 2;

    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    task.solve();

    // исходная матрица не должна измениться
    EXPECT_EQ(m.getRows(), 2u);
    EXPECT_EQ(m[0][0], 3);
    EXPECT_EQ(m[0][1], 1);
}

TEST(Task2Test, EmptyMatrixReturnsEmpty)
{
    Matrix m;
    RandomGenerator dummyGen(0, 0);
    Task2Exercise task(m, dummyGen);
    Matrix result = task.solve();

    EXPECT_EQ(result.getRows(), 0u);
    EXPECT_EQ(result.getColumns(), 0u);
}