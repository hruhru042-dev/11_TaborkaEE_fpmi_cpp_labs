
#include "../lab2_ex4/perfect.h"
#include <gtest/gtest.h>
TEST(PerfectNumbersTest, BorderlineValues) {
    EXPECT_EQ(findPerfectNumbers(6), (std::vector<int>{6}));
    EXPECT_EQ(findPerfectNumbers(30), (std::vector<int>{6, 28}));
    EXPECT_EQ(findPerfectNumbers(500), (std::vector<int>{6, 28, 496}));
    EXPECT_EQ(findPerfectNumbers(9000), (std::vector<int>{6, 28, 496, 8128}));
}
TEST(PerfectNumbersTest, Symmetry) {
    EXPECT_EQ(findPerfectNumbers(100), findPerfectNumbers(100));
    EXPECT_EQ(findPerfectNumbers(500), findPerfectNumbers(500));
}
TEST(PerfectNumbersTest, RerurnEmptyVector) {
    EXPECT_TRUE(findPerfectNumbers(-10).empty());
    EXPECT_TRUE(findPerfectNumbers(0).empty());
    EXPECT_TRUE(findPerfectNumbers(1).empty());
    EXPECT_TRUE(findPerfectNumbers(5).empty());
}
TEST(PerfectNumbersTest, NoDuplicates) {
    auto result = findPerfectNumbers(10000);
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = i + 1; j < result.size(); ++j) {
            EXPECT_NE(result[i], result[j]); //EXPECT_NE(a, b) проверяет, что a != b
        }
    }
}
TEST(PerfectNumbersTest, SortedAscending) {
    auto result = findPerfectNumbers(10000);
    for (size_t i = 1; i < result.size(); ++i) {
        EXPECT_LT(result[i - 1], result[i]); //EXPECT_LT(a, b) проверяет, что a < b
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
