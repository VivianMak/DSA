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
    std::vector<SimpleScheduler::Meeting> meeting_list = SimpleScheduler::time_to_meetings(raw_times);

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