// calc_test.cpp
#include <gtest/gtest.h>
#include <days.h>

TEST(AdventOfCode2023, advOcodeD012023)
{
  const std::string day = "01";
  const bool EXAMPLE = false;
  const std::string FUNCTIONNAME1 = "adventDay" + day + "P12023";
  const std::string FUNCTIONNAME2 = "adventDay" + day + "P22023";

  std::string fileName = DAY_EXAMPLE_PATH(day);
  std::ifstream inputFile(fileName);

  EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
  EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD022023)
{
    const std::string day = "02";
    const bool EXAMPLE = false;
    const std::string FUNCTIONNAME1 = "adventDay" + day + "P12023";
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P22023";

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}