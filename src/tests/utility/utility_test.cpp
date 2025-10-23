#define ENABLE_UTILITY_TEST

#include "gtest/gtest.h"
#include "../../utility/header/commonTypes.h"
#include "../../utility/header/mathUtility.h"

#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <limits>
#include <cmath>
#ifdef _WIN32
  #include <direct.h>
#elif __linux__
  #include <unistd.h>
#endif


using namespace Coruh::Utility;

class MathUtilityTest : public ::testing::Test {
 public:
  int a;
 protected:
  void SetUp() override {
    //Setup test data
  }

  void TearDown() override {
    // Clean up test data
  }
};



TEST_F(MathUtilityTest, CalculateMean) {
  int b = this->a;
  // Test data
  const double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  const int datalen = sizeof(data) / sizeof(data[0]);
  // Perform the calculation
  double result = MathUtility::calculateMean(data, datalen);
  // Check the result
  EXPECT_DOUBLE_EQ(result, 3.0);
}


TEST_F(MathUtilityTest, CalculateMedianOdd) {
  // Test data
  const double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  const int datalen = sizeof(data) / sizeof(data[0]);
  // Perform the calculation
  double result = MathUtility::calculateMedian(data, datalen);
  // Check the result
  EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST_F(MathUtilityTest, CalculateMedianEven) {
  // Test data
  const double data[] = { 1.0, 2.0, 3.0, 4.0 };
  const int datalen = sizeof(data) / sizeof(data[0]);
  // Perform the calculation
  double result = MathUtility::calculateMedian(data, datalen);
  // Check the result
  EXPECT_DOUBLE_EQ(result, 2.5);
}

TEST_F(MathUtilityTest, CompareDoubleLessTest) {
  // Test data
  const double val1 = 2.0;
  const double val2 = 4.0;
  // Perform the comparison
  int result = MathUtility::compareDouble(&val1, &val2);
  // Check the result
  EXPECT_EQ(result, -1);
}

TEST_F(MathUtilityTest, CompareDoubleGreaterTest) {
  // Test data
  const double val1 = 4.0;
  const double val2 = 2.0;
  // Perform the comparison
  int result = MathUtility::compareDouble(&val1, &val2);
  // Check the result
  EXPECT_EQ(result, 1);
}

TEST_F(MathUtilityTest, CompareDoubleEqualTest) {
  // Test data
  const double val1 = 3.0;
  const double val2 = 3.0;
  // Perform the comparison
  int result = MathUtility::compareDouble(&val1, &val2);
  // Check the result
  EXPECT_EQ(result, 0);
}

TEST_F(MathUtilityTest, CalculateMinMaxTest_1) {
  // Test data
  const double data[] = { 1.0, 2.0, 3.0, 4.0, 5.0 };
  const int datalen = sizeof(data) / sizeof(data[0]);
  double min, max;
  // Perform the calculation
  MathUtility::calculateMinMax(data, datalen, &min, &max);
  // Check the result
  EXPECT_DOUBLE_EQ(min, 1.0);
  EXPECT_DOUBLE_EQ(max, 5.0);
}

TEST_F(MathUtilityTest, CalculateMinMaxTest_2) {
  double data[] = { 3.14, 1.0, -2.5, 7.2, -5.0 };
  double min, max;
  MathUtility::calculateMinMax(data, sizeof(data) / sizeof(data[0]), &min, &max);
  EXPECT_DOUBLE_EQ(min, -5.0);
  EXPECT_DOUBLE_EQ(max, 7.2);
}

// Additional Edge Case Tests
TEST_F(MathUtilityTest, CalculateMeanSingleElement) {
  const double data[] = { 42.0 };
  const int datalen = 1;
  double result = MathUtility::calculateMean(data, datalen);
  EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(MathUtilityTest, CalculateMeanEmptyArray) {
  const double data[] = {};
  const int datalen = 0;
  double result = MathUtility::calculateMean(data, datalen);
  EXPECT_TRUE(std::isnan(result) || std::isinf(result)); // Should handle division by zero
}

TEST_F(MathUtilityTest, CalculateMedianSingleElement) {
  const double data[] = { 42.0 };
  const int datalen = 1;
  double result = MathUtility::calculateMedian(data, datalen);
  EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST_F(MathUtilityTest, CalculateMedianTwoElements) {
  const double data[] = { 1.0, 2.0 };
  const int datalen = 2;
  double result = MathUtility::calculateMedian(data, datalen);
  EXPECT_DOUBLE_EQ(result, 1.5);
}

TEST_F(MathUtilityTest, CalculateMedianNegativeNumbers) {
  const double data[] = { -5.0, -2.0, -1.0, -3.0, -4.0 };
  const int datalen = 5;
  double result = MathUtility::calculateMedian(data, datalen);
  EXPECT_DOUBLE_EQ(result, -3.0);
}

TEST_F(MathUtilityTest, CalculateMedianDuplicateValues) {
  const double data[] = { 1.0, 1.0, 1.0, 1.0 };
  const int datalen = 4;
  double result = MathUtility::calculateMedian(data, datalen);
  EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST_F(MathUtilityTest, CalculateMinMaxSingleElement) {
  const double data[] = { 42.0 };
  const int datalen = 1;
  double min, max;
  MathUtility::calculateMinMax(data, datalen, &min, &max);
  EXPECT_DOUBLE_EQ(min, 42.0);
  EXPECT_DOUBLE_EQ(max, 42.0);
}

TEST_F(MathUtilityTest, CalculateMinMaxAllSameValues) {
  const double data[] = { 5.0, 5.0, 5.0, 5.0 };
  const int datalen = 4;
  double min, max;
  MathUtility::calculateMinMax(data, datalen, &min, &max);
  EXPECT_DOUBLE_EQ(min, 5.0);
  EXPECT_DOUBLE_EQ(max, 5.0);
}

TEST_F(MathUtilityTest, CalculateMinMaxZeroValues) {
  const double data[] = { 0.0, -0.0, 0.0 };
  const int datalen = 3;
  double min, max;
  MathUtility::calculateMinMax(data, datalen, &min, &max);
  EXPECT_DOUBLE_EQ(min, 0.0);
  EXPECT_DOUBLE_EQ(max, 0.0);
}

TEST_F(MathUtilityTest, CompareDoubleWithZero) {
  const double val1 = 0.0;
  const double val2 = 1.0;
  int result = MathUtility::compareDouble(&val1, &val2);
  EXPECT_EQ(result, -1);
  
  result = MathUtility::compareDouble(&val2, &val1);
  EXPECT_EQ(result, 1);
}

TEST_F(MathUtilityTest, CompareDoubleWithNegativeZero) {
  const double val1 = -0.0;
  const double val2 = 0.0;
  int result = MathUtility::compareDouble(&val1, &val2);
  EXPECT_EQ(result, 0); // -0.0 should equal 0.0
}

TEST_F(MathUtilityTest, CompareDoubleWithInfinity) {
  const double val1 = std::numeric_limits<double>::infinity();
  const double val2 = 1.0;
  int result = MathUtility::compareDouble(&val1, &val2);
  EXPECT_EQ(result, 1); // infinity > 1.0
  
  result = MathUtility::compareDouble(&val2, &val1);
  EXPECT_EQ(result, -1);
}

TEST_F(MathUtilityTest, CompareDoubleWithNaN) {
  const double val1 = std::numeric_limits<double>::quiet_NaN();
  const double val2 = 1.0;
  int result = MathUtility::compareDouble(&val1, &val2);
  EXPECT_EQ(result, 0); // NaN comparison should return 0
}

// Performance Tests
TEST_F(MathUtilityTest, CalculateMeanLargeArray) {
  const int size = 10000;
  double* data = new double[size];
  for (int i = 0; i < size; ++i) {
    data[i] = i + 1.0;
  }
  
  double result = MathUtility::calculateMean(data, size);
  EXPECT_DOUBLE_EQ(result, (size + 1.0) / 2.0);
  
  delete[] data;
}

TEST_F(MathUtilityTest, CalculateMedianLargeArray) {
  const int size = 10001; // Odd number
  double* data = new double[size];
  for (int i = 0; i < size; ++i) {
    data[i] = size - i; // Reverse order
  }
  
  double result = MathUtility::calculateMedian(data, size);
  EXPECT_DOUBLE_EQ(result, (size + 1.0) / 2.0);
  
  delete[] data;
}





/**
 * @brief The main function of the test program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the program.
 */
int main(int argc, char **argv) {
#ifdef ENABLE_UTILITY_TEST
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
