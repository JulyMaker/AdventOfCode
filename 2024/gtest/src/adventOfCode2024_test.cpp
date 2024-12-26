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

    EXPECT_EQ(6, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(6, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_09)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(114, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(2, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_10)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(8, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(10, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_11)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(374, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(82000210, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_12)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(21, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(525152, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_13)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(405, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(400, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_14)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(136, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(64, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_15)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(1320, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(145, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_16)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(46, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(51, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_17)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(102, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(94, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_18)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(62, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(952408144115, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_19)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(19114, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(167409079868000, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_20)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(11687500, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(220366255099387, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_21)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(42, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(394693535848011, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_22)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(5, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(7, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_23)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(94, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(154, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_24)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(0, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(47, launchProblem[FUNCTIONNAME2](inputFile2));
}

TEST(AdventOfCode2024, advOcodeD_25)
{
    const std::string testName = testing::UnitTest::GetInstance()->current_test_info()->name();
    std::string FUNCTIONNAME1; std::string FUNCTIONNAME2;
    std::ifstream inputFile1, inputFile2;

    getData(testName, FUNCTIONNAME1, FUNCTIONNAME2, inputFile1, inputFile2);

    EXPECT_EQ(54, launchProblem[FUNCTIONNAME1](inputFile1));
    EXPECT_EQ(0, launchProblem[FUNCTIONNAME2](inputFile2));
}

int main(int argc, char **argv) 
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}