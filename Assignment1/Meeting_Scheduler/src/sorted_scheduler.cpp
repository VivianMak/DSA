#include "sorted_scheduler.hpp"

#include <chrono>
#include <vector>
#include <utility>
#include <iostream> //print
#include <ranges> // view
#include <algorithm>

namespace SortedScheduler{

    // sorts the meeting
    void sort_start_time(std::vector<Meeting>& meetings){
        std::sort(meetings.begin(), meetings.end(), 
            [](const SortedScheduler::Meeting& m1, const SortedScheduler::Meeting& m2){
                return m1.start_time < m2.start_time;
            });
    }

    bool find_conflict(const std::vector<SortedScheduler::Meeting>& meetings){ // acoids copying

        // sort meetings by start time first
        std::vector<Meeting> sorted_meetings = meetings;
        sort_start_time(sorted_meetings);

        for (std::size_t i = 0; i + 1 < sorted_meetings.size(); i++){
            if (sorted_meetings[i].end_time > sorted_meetings[i+1].start_time){
                return true;
            }
        }
        return false;
    }

    std::vector<Meeting> time_to_meetings(const std::vector<std::pair<HM, HM>>& raw_times){
        std::vector<Meeting> meeting_list;

        for (auto [i, times] : raw_times | std::views::enumerate) {
            auto [start_hm, end_hm] = times;

            std::chrono::minutes start_time =
                std::chrono::hours(std::get<0>(start_hm)) + std::chrono::minutes(std::get<1>(start_hm));
            std::chrono::minutes end_time =
                std::chrono::hours(std::get<0>(end_hm)) + std::chrono::minutes(std::get<1>(end_hm));

            meeting_list.push_back(Meeting{
                static_cast<int>(i), start_time, end_time
            });
        }

        return meeting_list;
    }

} // namespace SortedScheduler
