// calc_test.cpp
#include <gtest/gtest.h>
#include <days.h>


std::ifstream& getData(const std::string& testName, std::string& funcName1, std::string& funcName2)
{
   const std::string year = "2023";
   const std::string day = testName.substr(testName.size() - 2, 2);

   funcName1 = "adventDay" + day + "P1" + year;
   funcName2 = "adventDay" + day + "P2" + year;

   std::string fileName = DAY_EXAMPLE_PATH(day);
   std::ifstream inputFile(fileName);

   return inputFile;
}
TEST(AdventOfCode2023, advOcodeD_01)
{
  const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
  std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

  std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

  EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
  EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_02)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_03)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_04)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_05)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_06)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_07)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_08)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_09)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_10)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_11)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_12)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_13)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_14)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_15)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_16)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_17)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_18)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_19)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_20)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_21)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_22)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_23)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_24)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

TEST(AdventOfCode2023, advOcodeD_25)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;

    std::ifstream& inputFile = getData(testName, FUNCTIONNAME1, FUNCTIONNAME2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile));
}

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}