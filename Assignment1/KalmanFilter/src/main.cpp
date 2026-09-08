#include "kf_helper.hpp"
#include "kf.hpp"

#include <Eigen/Dense>
#include <iostream>

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
    // std::vector<double> true_poses(steps);
    // std::vector<double> observations(steps);

    auto [true_poses, observations] = KF_HELPER::simulate_realworld_neato(config);

    // std::cout << "The observed neato points are:" << observations << std::endl;
    // std::cout << "The simulated neato points are:" << true_poses << std::endl;

    for (const double& x : observations) std::cout << x << " ";
    std::cout << "\n"; 
    for (const double& z : true_poses) std::cout << z << " ";
    std::cout << "\n";



    // Create a kalman filter class
    KF::KalmanFilter kf(config);
    kf.setState();
    auto [x_filter, P_filter] = kf.solve(observations);

    std::cout << "Final state estimate: " << x_filter.back().transpose() << std::endl;
 
    return 0;
}