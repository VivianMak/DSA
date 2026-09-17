#include "scheduler.hpp"

#include <iostream> //print
#include <ranges> // view
#include <vector>
// #include <pair>


int main(){

    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Simple Scheduler
    std::cout << "TESTING FIND CONFLICT SIMPLE: " << std::endl;

    if (Scheduler::find_conflict_simple(meeting_list)){
        std::cout << "There are conflicts." << std::endl;
    } else {
        std::cout << "There are no conflicts." << std::endl;
    }

    // Sorted Scheduler
    std::cout << "TESTING FIND CONFLICT SORTED: " << std::endl;
    
    if (Scheduler::find_conflict_sorted(meeting_list)){
        std::cout << "There are conflicts." << std::endl;
    } else {
        std::cout << "There are no conflicts." << std::endl;
    }

    return 0;
}