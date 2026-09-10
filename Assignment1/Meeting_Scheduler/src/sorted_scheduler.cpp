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

        for (auto [i, m] : sorted_meetings | std::views::enumerate | std::views::drop_last(1)){
            if (m.end_time > sorted_meetings[i].start_time){
                return true;
            }
        }
        return false;
    }

} // namespace SortedScheduler


using SortedScheduler::find_conflict;

int main(){

    // Create meeting times
    std::vector<std::pair<SortedScheduler::HM, SortedScheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<SortedScheduler::Meeting> meeting_list;
    
    for (auto [i, times] : raw_times | std::views::enumerate) {
        // Data strucutre: 
        // meeting_list = [[start_time, end_time], [start_time, end_time], ...]
        
        auto[start_hm, end_hm] = times;

        std::chrono::minutes start_time = std::chrono::hours(std::get<0>(start_hm)) + std::chrono::minutes(std::get<1>(start_hm));
        std::chrono::minutes end_time = std::chrono::hours(std::get<0>(end_hm)) + std::chrono::minutes(std::get<1>(end_hm));

        meeting_list.push_back(SortedScheduler::Meeting{
            static_cast<int>(i), start_time, end_time
        });
    }

    bool conflict = SortedScheduler::find_conflict(meeting_list);

    std::string c;
    if (conflict==1){
        c = "True";
    }else{
        c = "False";
    };


    std::cout << "Are there conflicts? " << c  << std::endl;

    return 0;
}