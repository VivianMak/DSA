#include <gtest/gtest.h>
#include <cmath>
 
#include "kf.hpp"
#include "kf_helper.hpp"

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

TEST(SimulateRealworldNeato, ReturnsEqualLengthPositionAndObservationVectors)
{
    int steps = 50;
    const KF_HELPER::Kf_Config config{
        /*dt=*/1,
        /*steps=*/steps,
        /*robot_vel=*/2.0,
        /*sensor_var=*/100.0,
        /*process_var=*/0.1
    };

    std::vector<double> true_poses(steps);
    std::vector<double> observations(steps);
 
    std::tie(true_poses, observations) = KF_HELPER::simulate_realworld_neato(config);
 
    EXPECT_EQ(true_poses.size(), config.steps);
    EXPECT_EQ(observations.size(), config.steps);
    EXPECT_EQ(true_poses.size(), observations.size());
}