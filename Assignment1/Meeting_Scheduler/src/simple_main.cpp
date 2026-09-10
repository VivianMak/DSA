#include "simple_scheduler.hpp"
#include <iostream> //print
#include <ranges> // view

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