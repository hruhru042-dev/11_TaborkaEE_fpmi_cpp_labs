#define BOOST_TEST_MODULE PerfectNumbersTest
#include <boost/test/included/unit_test.hpp>
#include "../lab2_ex4/perfect.h"
BOOST_AUTO_TEST_SUITE(PerfectNumbers)



BOOST_AUTO_TEST_CASE(Symmetry) {
    BOOST_CHECK(findPerfectNumbers(50) == findPerfectNumbers(100));
    BOOST_CHECK(findPerfectNumbers(500) == findPerfectNumbers(500));
}

BOOST_AUTO_TEST_CASE(ReturnEmptyVector) {
    BOOST_CHECK(findPerfectNumbers(-10).empty());
    BOOST_CHECK(findPerfectNumbers(0).empty());
    BOOST_CHECK(findPerfectNumbers(1).empty());
    BOOST_CHECK(findPerfectNumbers(5).empty());
}

BOOST_AUTO_TEST_CASE(NoDuplicates) {
    auto result = findPerfectNumbers(10000);
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = i + 1; j < result.size(); ++j) {
            BOOST_CHECK(result[i] != result[j]);
        }
    }
}


BOOST_AUTO_TEST_CASE(SortedAscending) {
    auto result = findPerfectNumbers(10000);
    for (size_t i = 1; i < result.size(); ++i) {
        BOOST_CHECK(result[i - 1] < result[i]);
    }
}

bool isPerfect(int n) {
    int sum = 0;
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) sum += i;
    }
    return sum == n;
}

BOOST_AUTO_TEST_CASE(ValidityCheck) {
    auto result = findPerfectNumbers(10000);
    for (int num : result) {
        BOOST_CHECK(isPerfect(num));
    }
}
BOOST_AUTO_TEST_SUITE_END()