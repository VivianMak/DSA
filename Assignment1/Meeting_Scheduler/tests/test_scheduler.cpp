#include <gtest/gtest.h>
#include <cmath>
 
#include "scheduler.hpp"

// Sorted Scheduler

TEST(SortedDetectConflict, NoConflictCase)
{
    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = Scheduler::find_conflict_sorted(meeting_list);

    EXPECT_EQ(conflict, false);
}

TEST(SortedDetectConflict, YesConflictCase)
{
    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{10, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = Scheduler::find_conflict_sorted(meeting_list);

    EXPECT_EQ(conflict, true);
}

TEST(SortedDetectConflict, NoConflictCaseImmediate)
{
    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 0}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = Scheduler::find_conflict_sorted(meeting_list);

    EXPECT_EQ(conflict, false);
}

// Simple Scheduler

TEST(SimpleDetectConflict, NoConflictCase)
{
    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = Scheduler::find_conflict_simple(meeting_list);

    EXPECT_EQ(conflict, false);
}

TEST(SimpleDetectConflict, YesConflictCase)
{
    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{10, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = Scheduler::find_conflict_simple(meeting_list);

    EXPECT_EQ(conflict, true);
}

TEST(SimpleDetectConflict, NoConflictCaseImmediate)
{
    // Create meeting times
    std::vector<std::pair<Scheduler::HM, Scheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 0}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<Scheduler::Meeting> meeting_list = Scheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = Scheduler::find_conflict_simple(meeting_list);

    EXPECT_EQ(conflict, false);
}