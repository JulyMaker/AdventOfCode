// calc_test.cpp
#include <gtest/gtest.h>
#include <days.h>

const std::string year = "2023";
TEST(AdventOfCode2023, advOcodeD_01)
{
  const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
  const std::string day = testName.substr(testName.size() - 2, 2);

  const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
  const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

  std::string fileName = DAY_EXAMPLE_PATH(day);
  std::ifstream inputFile(fileName);

  EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
  EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_02)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_03)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_04)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_05)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_06)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_07)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_08)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

    std::string fileName = DAY_EXAMPLE_PATH(day);
    std::ifstream inputFile(fileName);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_09)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    const std::string day = testName.substr(testName.size() - 2, 2);

    const std::string FUNCTIONNAME1 = "adventDay" + day + "P1" + year;
    const std::string FUNCTIONNAME2 = "adventDay" + day + "P2" + year;

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