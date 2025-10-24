/**
 * @file test_math_utility.cpp
 */

#include <gtest/gtest.h>
#include "../src/utility/header/mathUtility.h"

using namespace Coruh::Utility;

TEST(MathUtilityTest, MeanMedianOddEven) {
    double a[] {1, 3, 5, 7, 9};
    EXPECT_DOUBLE_EQ(MathUtility::calculateMean(a, 5), 5.0);
    EXPECT_DOUBLE_EQ(MathUtility::calculateMedian(a, 5), 5.0);

    double b[] {10, 2, 8, 4};
    EXPECT_DOUBLE_EQ(MathUtility::calculateMean(b, 4), (10.0 + 2.0 + 8.0 + 4.0) / 4.0);
    // Sorted -> {2,4,8,10} median -> (4+8)/2 = 6
    EXPECT_DOUBLE_EQ(MathUtility::calculateMedian(b, 4), 6.0);
}

TEST(MathUtilityTest, MinMaxAndComparator) {
    double values[] {5.5, -2.0, 3.0, 9.1, 0.0};
    double minv = 0, maxv = 0;
    MathUtility::calculateMinMax(values, 5, &minv, &maxv);
    EXPECT_DOUBLE_EQ(minv, -2.0);
    EXPECT_DOUBLE_EQ(maxv, 9.1);

    // Comparator semantics
    double x = 1.0, y = 2.0, z = 1.0;
    EXPECT_LT(MathUtility::compareDouble(&x, &y), 0);
    EXPECT_GT(MathUtility::compareDouble(&y, &x), 0);
    EXPECT_EQ(MathUtility::compareDouble(&x, &z), 0);
}

