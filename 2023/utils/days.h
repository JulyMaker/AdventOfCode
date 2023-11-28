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

// Funtions map
static std::map<std::string, std::function<uint64_t(std::ifstream&)>> launchProblem =
{
     {"adventDay01P12023", adventDay01P12023}, {"adventDay01P22023", adventDay01P22023}
    ,{"adventDay02P12023", adventDay02P12023}, {"adventDay02P22023", adventDay02P22023}
    ,{"adventDay03P12023", adventDay03P12023}, {"adventDay03P22023", adventDay03P22023}
    ,{"adventDay04P12023", adventDay04P12023}, {"adventDay04P22023", adventDay04P22023}
    ,{"adventDay05P12023", adventDay05P12023}, {"adventDay05P22023", adventDay05P22023}
    ,{"adventDay06P12023", adventDay06P12023}, {"adventDay06P22023", adventDay06P22023}
    ,{"adventDay07P12023", adventDay07P12023}, {"adventDay07P22023", adventDay07P22023}
    ,{"adventDay08P12023", adventDay08P12023}, {"adventDay08P22023", adventDay08P22023}
    ,{"adventDay09P12023", adventDay09P12023}, {"adventDay09P22023", adventDay09P22023}
    ,{"adventDay10P12023", adventDay10P12023}, {"adventDay10P22023", adventDay10P22023}
    ,{"adventDay11P12023", adventDay11P12023}, {"adventDay11P22023", adventDay11P22023}
    ,{"adventDay12P12023", adventDay12P12023}, {"adventDay12P22023", adventDay12P22023}
    ,{"adventDay13P12023", adventDay13P12023}, {"adventDay13P22023", adventDay13P22023}
    ,{"adventDay14P12023", adventDay14P12023}, {"adventDay14P22023", adventDay14P22023}
    ,{"adventDay15P12023", adventDay15P12023}, {"adventDay15P22023", adventDay15P22023}
    ,{"adventDay16P12023", adventDay16P12023}, {"adventDay16P22023", adventDay16P22023}
    ,{"adventDay17P12023", adventDay17P12023}, {"adventDay17P22023", adventDay17P22023}
    ,{"adventDay18P12023", adventDay18P12023}, {"adventDay18P22023", adventDay18P22023}
    ,{"adventDay19P12023", adventDay19P12023}, {"adventDay19P22023", adventDay19P22023}
    ,{"adventDay20P12023", adventDay20P12023}, {"adventDay20P22023", adventDay20P22023}
    ,{"adventDay21P12023", adventDay21P12023}, {"adventDay21P22023", adventDay21P22023}
    ,{"adventDay22P12023", adventDay22P12023}, {"adventDay22P22023", adventDay22P22023}
    ,{"adventDay23P12023", adventDay23P12023}, {"adventDay23P22023", adventDay23P22023}
    ,{"adventDay24P12023", adventDay24P12023}, {"adventDay24P22023", adventDay24P22023}
    ,{"adventDay25P12023", adventDay25P12023}, {"adventDay25P22023", adventDay25P22023}
};