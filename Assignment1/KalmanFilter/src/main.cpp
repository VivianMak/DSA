#include "kf_helper.hpp"
#include "kf.hpp"

#include <Eigen/Dense>
#include <iostream>
#include <cmath>

int main(){

    // Configs for the kalman filter
    int dt = 1;
    int steps = 50;
    double robot_vel = 2.0;
    double sensor_var = 100.0;
    double process_var = 0.1;
    
    // Create struct
    const KF_HELPER::Kf_Config config = {
        dt, steps, robot_vel, sensor_var, process_var
    };


    // // Simulate the positions
    std::vector<double> true_poses(steps);
    std::vector<double> observations(steps);

    std::tie(true_poses, observations) = KF_HELPER::simulate_realworld_neato(config);


    std::cout << "The simulated neato points:" << std::endl;
    std::cout << observations.size() << " Observed Positions" << std::endl; 
    std::cout << true_poses.size() << " Real Poses" << std::endl; 


    // Create a kalman filter class
    KF::KalmanFilter kf(config);

    Eigen::Vector2d x0;
    x0 << 10.0, 4.5;

    std::vector<Eigen::Vector2d> x_filter;
    std::vector<Eigen::Matrix2d> P_filter;
    
    kf.setState(x0);
    std::tie(x_filter, P_filter) = kf.solve(observations);

    // Print debugging
    std::cout << "\nInitial state estimate: " << x0.transpose() << std::endl;
    std::cout << "Final state estimate: " << x_filter.back().transpose() << std::endl;


    // --- Accuracy check: estimate vs. ground truth ---
    double estimated_final_pos = x_filter.back().x();   // x_filter.back() is (position, velocity)
    double estimated_final_vel = x_filter.back().y();
    double true_final_pos = true_poses.back();

    double position_error = estimated_final_pos - true_final_pos;
    double velocity_error = estimated_final_vel - robot_vel;

    std::cout << "\n--- Final Accuracy ---" << std::endl;
    std::cout << "True final position:      " << true_final_pos << std::endl;
    std::cout << "Estimated final position: " << estimated_final_pos << std::endl;
    std::cout << "Position error:           " << position_error
            << " (" << std::abs(position_error / true_final_pos) * 100.0 << "%)" << std::endl;

    std::cout << "\nTrue velocity:            " << robot_vel << std::endl;
    std::cout << "Estimated final velocity: " << estimated_final_vel << std::endl;
    std::cout << "Velocity error:           " << velocity_error << std::endl;

    // --- RMSE across the whole trajectory, not just the last point ---
    double sum_squared_error = 0.0;
    for (size_t i = 0; i < x_filter.size(); ++i) {
        double err = x_filter[i].x() - true_poses[i];
        sum_squared_error += err * err;
    }
    double rmse = std::sqrt(sum_squared_error / x_filter.size());
    std::cout << "\nRMSE (position, over all " << steps << " steps): " << rmse << std::endl;
 
    return 0;
}