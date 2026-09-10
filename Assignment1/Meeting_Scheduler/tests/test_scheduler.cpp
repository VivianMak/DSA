#include <gtest/gtest.h>
#include <cmath>
 
#include "simple_scheduler.hpp"
#include "sorted_scheduler.hpp"

// // TEST(TestSuiteName, TestName)
// TEST(AdditionTest, HandlesPositiveNumbers) {
//     // Arrange & Act
//     int result = Add(2, 3);
    
//     // Assert
//     EXPECT_EQ(result, 5); 
// }

// TEST(AdditionTest, HandlesNegativeNumbers) {
//     EXPECT_EQ(Add(-1, -1), -2);
//     EXPECT_EQ(Add(-1, 5), 4);
// }

TEST(DetectConflict, NoConflictCase)
{
    // Create meeting times
    std::vector<std::pair<SimpleScheduler::HM, SimpleScheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<SortedScheduler::Meeting> meeting_list = SortedScheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = SortedScheduler::find_conflict(meeting_list);

    EXPECT_EQ(conflict, false);
}

TEST(DetectConflict, YesConflictCase)
{
    // Create meeting times
    std::vector<std::pair<SimpleScheduler::HM, SimpleScheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{10, 30}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<SortedScheduler::Meeting> meeting_list = SortedScheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = SortedScheduler::find_conflict(meeting_list);

    EXPECT_EQ(conflict, true);
}

TEST(DetectConflict, NoConflictCaseImmediate)
{
    // Create meeting times
    std::vector<std::pair<SimpleScheduler::HM, SimpleScheduler::HM>>
    raw_times = {
        {{10, 0},  {11, 0}},
        {{13, 0}, {14, 0}},
        {{11, 0}, {11, 45}},
    };

    // Turn the raw times into meeting objects
    std::vector<SortedScheduler::Meeting> meeting_list = SortedScheduler::time_to_meetings(raw_times);

    // Check for conflicts
    bool conflict = SortedScheduler::find_conflict(meeting_list);

    EXPECT_EQ(conflict, false);
}