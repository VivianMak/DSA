#pragma once

#include <chrono>
#include <vector>


namespace SimpleScheduler{

using HM = std::pair<int, int>;

struct Meeting{
    int meeting_id;
    std::chrono::minutes start_time;
    std::chrono::minutes end_time;
};

std::pair<HM, HM>
extract_time(const SimpleScheduler::Meeting& m);

bool find_conflict(const std::vector<SimpleScheduler::Meeting>& meetings);

}