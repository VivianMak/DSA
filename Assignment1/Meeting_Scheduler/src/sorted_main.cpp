#include "sorted_scheduler.hpp"
#include <iostream> //print
#include <ranges> // view

int main(){

    // Create meeting times
    std::vector<std::pair<SortedScheduler::HM, SortedScheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{10, 30}, {11, 45}},
    };

    

    // Turn the raw times into meeting objects
    std::vector<SortedScheduler::Meeting> meeting_list = SortedScheduler::time_to_meetings(raw_times);

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