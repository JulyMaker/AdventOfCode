#pragma once

#include<day01_.h>
#include<day02_.h>
#include<day03_.h>
#include<day04_.h>
#include<day05_.h>
#include<day06_.h>
#include<day07_.h>
#include<day08_.h>
#include<day09_.h>
#include<day10_.h>
#include<day11_.h>
#include<day12_.h>
#include<day13_.h>
#include<day14_.h>
#include<day15_.h>
#include<day16_.h>
#include<day17_.h>
#include<day18_.h>
#include<day19_.h>
#include<day20_.h>
#include<day21_.h>
#include<day22_.h>
#include<day23_.h>
#include<day24_.h>
#include<day25_.h>

#define DEFINE_PROBLEM(day, year) \
    {"adventDay" #day "P1" #year, adventDay##day##P1##year}, \
    {"adventDay" #day "P2" #year, adventDay##day##P2##year}

// Funtions map
static std::map<std::string, std::function<uint64_t(std::ifstream&)>> launchProblem =
{
    DEFINE_PROBLEM(01, 2024),
    DEFINE_PROBLEM(02, 2024),
    DEFINE_PROBLEM(03, 2024),
    DEFINE_PROBLEM(04, 2024),
    DEFINE_PROBLEM(05, 2024),
    DEFINE_PROBLEM(06, 2024),
    DEFINE_PROBLEM(07, 2024),
    DEFINE_PROBLEM(08, 2024),
    DEFINE_PROBLEM(09, 2024),
    DEFINE_PROBLEM(10, 2024),
    DEFINE_PROBLEM(11, 2024),
    DEFINE_PROBLEM(12, 2024),
    DEFINE_PROBLEM(13, 2024),
    DEFINE_PROBLEM(14, 2024),
    DEFINE_PROBLEM(15, 2024),
    DEFINE_PROBLEM(16, 2024),
    DEFINE_PROBLEM(17, 2024),
    DEFINE_PROBLEM(18, 2024),
    DEFINE_PROBLEM(19, 2024),
    DEFINE_PROBLEM(20, 2024),
    DEFINE_PROBLEM(21, 2024),
    DEFINE_PROBLEM(22, 2024),
    DEFINE_PROBLEM(23, 2024),
    DEFINE_PROBLEM(24, 2024),
    DEFINE_PROBLEM(25, 2024)
};

// Funtions map
//static std::map<std::string, std::function<uint64_t(std::ifstream&)>> launchProblem =
//{
//     {"adventDay01P12024", adventDay01P12024}, {"adventDay01P22024", adventDay01P22024}
//    ,{"adventDay02P12024", adventDay02P12024}, {"adventDay02P22024", adventDay02P22024}
//    ,{"adventDay03P12024", adventDay03P12024}, {"adventDay03P22024", adventDay03P22024}
//    ,{"adventDay04P12024", adventDay04P12024}, {"adventDay04P22024", adventDay04P22024}
//    ,{"adventDay05P12024", adventDay05P12024}, {"adventDay05P22024", adventDay05P22024}
//    ,{"adventDay06P12024", adventDay06P12024}, {"adventDay06P22024", adventDay06P22024}
//    ,{"adventDay07P12024", adventDay07P12024}, {"adventDay07P22024", adventDay07P22024}
//    ,{"adventDay08P12024", adventDay08P12024}, {"adventDay08P22024", adventDay08P22024}
//    ,{"adventDay09P12024", adventDay09P12024}, {"adventDay09P22024", adventDay09P22024}
//    ,{"adventDay10P12024", adventDay10P12024}, {"adventDay10P22024", adventDay10P22024}
//    ,{"adventDay11P12024", adventDay11P12024}, {"adventDay11P22024", adventDay11P22024}
//    ,{"adventDay12P12024", adventDay12P12024}, {"adventDay12P22024", adventDay12P22024}
//    ,{"adventDay13P12024", adventDay13P12024}, {"adventDay13P22024", adventDay13P22024}
//    ,{"adventDay14P12024", adventDay14P12024}, {"adventDay14P22024", adventDay14P22024}
//    ,{"adventDay15P12024", adventDay15P12024}, {"adventDay15P22024", adventDay15P22024}
//    ,{"adventDay16P12024", adventDay16P12024}, {"adventDay16P22024", adventDay16P22024}
//    ,{"adventDay17P12024", adventDay17P12024}, {"adventDay17P22024", adventDay17P22024}
//    ,{"adventDay18P12024", adventDay18P12024}, {"adventDay18P22024", adventDay18P22024}
//    ,{"adventDay19P12024", adventDay19P12024}, {"adventDay19P22024", adventDay19P22024}
//    ,{"adventDay20P12024", adventDay20P12024}, {"adventDay20P22024", adventDay20P22024}
//    ,{"adventDay21P12024", adventDay21P12024}, {"adventDay21P22024", adventDay21P22024}
//    ,{"adventDay22P12024", adventDay22P12024}, {"adventDay22P22024", adventDay22P22024}
//    ,{"adventDay23P12024", adventDay23P12024}, {"adventDay23P22024", adventDay23P22024}
//    ,{"adventDay24P12024", adventDay24P12024}, {"adventDay24P22024", adventDay24P22024}
//    ,{"adventDay25P12024", adventDay25P12024}, {"adventDay25P22024", adventDay25P22024}
//};