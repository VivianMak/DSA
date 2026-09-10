#include "simple_scheduler.hpp"

#include <chrono>
#include <vector>
#include <utility>
#include <iostream> //print
#include <ranges> // view

namespace SimpleScheduler{

    // Returns start time hh_mm and end time hh_mm
    std::pair<HM, HM>
    extract_time(const SimpleScheduler::Meeting& m){

        std::chrono::minutes start_time = m.start_time;
        std::chrono::minutes end_time = m.end_time;

        std::chrono::hh_mm_ss start{start_time};
        std::chrono::hh_mm_ss end{end_time};

        // Extract the individual components
        int h1 = start.hours().count();
        int m1 = start.minutes().count();

        int h2 = end.hours().count();
        int m2 = end.minutes().count();

        return {{h1,m1},{h2,m2}};
    }

    bool find_conflict(const std::vector<SimpleScheduler::Meeting>& meetings){ // acoids copying

        for (int i = 0; i < meetings.size(); i++){
            
            for (int j = i+1; j < meetings.size(); j++)
            {
                if ((meetings[i].start_time < meetings[j].end_time) && (meetings[j].start_time < meetings[i].end_time))
                {
                    return true;    // find conflict
                }
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

} // namespace SimpleScheduler