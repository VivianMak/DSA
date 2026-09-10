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

} // namespace SimpleScheduler


using SimpleScheduler::find_conflict;

int main(){

    // Create meeting times
    std::vector<std::pair<SimpleScheduler::HM, SimpleScheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<SimpleScheduler::Meeting> meeting_list;
    
    for (auto [i, times] : raw_times | std::views::enumerate) {
        // Data strucutre: 
        // meeting_list = [[start_time, end_time], [start_time, end_time], ...]
        
        auto[start_hm, end_hm] = times;

        std::chrono::minutes start_time = std::chrono::hours(std::get<0>(start_hm)) + std::chrono::minutes(std::get<1>(start_hm));
        std::chrono::minutes end_time = std::chrono::hours(std::get<0>(end_hm)) + std::chrono::minutes(std::get<1>(end_hm));

        meeting_list.push_back(SimpleScheduler::Meeting{
            static_cast<int>(i), start_time, end_time
        });
    }

    bool conflict = SimpleScheduler::find_conflict(meeting_list);

    std::string c;
    if (conflict==1){
        c = "True";
    }else{
        c = "False";
    };


    std::cout << "Are there conflicts? " << c  << std::endl;

    return 0;
}