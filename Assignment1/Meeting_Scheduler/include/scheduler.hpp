#pragma once

#include <chrono>
#include <vector>


namespace Scheduler{

// Shared
using HM = std::pair<int, int>;

struct Meeting{
    int meeting_id;
    std::chrono::minutes start_time;
    std::chrono::minutes end_time;
};

std::vector<Meeting> time_to_meetings(const std::vector<std::pair<HM, HM>>& raw_times);
// std::pair<HM, HM> extract_time(const Meeting& m);

// Simple Scheduler
bool find_conflict_simple(const std::vector<Meeting>& meetings);


// Sorted Scheduler
void sort_start_time(std::vector<Meeting>& meetings);
bool find_conflict_sorted(const std::vector<Meeting>& meetings);


}