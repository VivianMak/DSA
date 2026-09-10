#pragma once

#include <chrono>
#include <vector>


namespace SortedScheduler{

using HM = std::pair<int, int>;

struct Meeting{
    int meeting_id;
    std::chrono::minutes start_time;
    std::chrono::minutes end_time;
};

void sort_start_time(std::vector<Meeting>& meetings);

bool find_conflict(const std::vector<SortedScheduler::Meeting>& meetings);

}