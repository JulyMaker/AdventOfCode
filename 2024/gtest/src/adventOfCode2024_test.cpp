#include <gtest/gtest.h>
#include <days.h>


void getData(const std::string& testName, std::string& funcName1, std::string& funcName2, std::ifstream& inputFile1, std::ifstream& inputFile2)
{
   const std::string year = "2024";
   const std::string day = testName.substr(testName.size() - 2, 2);

   funcName1 = "adventDay" + day + "P1" + year;
   funcName2 = "adventDay" + day + "P2" + year;

   inputFile1 = std::ifstream(DAY_EXAMPLE_PATH(day, "1"));
   inputFile2 = std::ifstream(DAY_EXAMPLE_PATH(day, "2"));
}
TEST(AdventOfCode2024, advOcodeD_01)
{
  const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
  std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
  std::ifstream inputFile1, inputFile2;

  getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

  EXPECT_EQ(11, launchProblem[FUNCTIONNAME1](inputFile1));
  EXPECT_EQ(31, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_02)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(2, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(4, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_03)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(161, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(48, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_04)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(18, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(9, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_05)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(143, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(123, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_06)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(41, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(6, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_07)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(3749, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(11387, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_08)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(14, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(34, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_09)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(1928, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(2858, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_10)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(36, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(81, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_11)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(55312, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(65601038650482, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_12)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(1930, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(1206, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_13)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(480, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(875318608908, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_14)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(12, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(19, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_15)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(10092, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(9021, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_16)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(7036, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(45, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_17)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(117440, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_18)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(22, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(20, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_19)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(6, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(16, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_20)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_21)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(126384, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(154115708116294, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_22)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(37327623, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(23, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_23)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(7, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_24)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(2024, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(9, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_25)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(3, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}