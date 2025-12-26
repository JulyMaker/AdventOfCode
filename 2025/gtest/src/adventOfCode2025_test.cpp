#include <gtest/gtest.h>
#include <days.h>


void getData(const std::string& testName, std::string& funcName1, std::string& funcName2, std::ifstream& inputFile1, std::ifstream& inputFile2)
{
   const std::string year = "2025";
   const std::string day = testName.substr(testName.size() - 2, 2);

   funcName1 = "adventDay" + day + "P1" + year;
   funcName2 = "adventDay" + day + "P2" + year;

   inputFile1 = std::ifstream(DAY_EXAMPLE_PATH(day, "1"));
   inputFile2 = std::ifstream(DAY_EXAMPLE_PATH(day, "2"));
}
TEST(AdventOfCode2025, advOcodeD_01)
{
  const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
  std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
  std::ifstream inputFile1, inputFile2;

  getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

  EXPECT_EQ(3, launchProblem[FUNCTIONNAME1](inputFile1));
  EXPECT_EQ(6, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_02)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(1227775554, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(4174379265, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_03)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(357, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(3121910778619, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_04)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(13, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(43, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_05)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_06)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_07)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_08)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_09)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_10)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_11)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_12)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_13)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_14)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_15)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_16)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_17)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_18)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_19)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_20)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_21)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_22)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_23)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_24)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2025, advOcodeD_25)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}