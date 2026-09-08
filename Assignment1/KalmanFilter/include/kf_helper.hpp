#pragma once

#include <Eigen/Dense>
#include <tuple>
#include <array>


namespace KF_HELPER{

struct Kf_Config{
    int dt;
    int steps;
    double robot_vel;
    double sensor_var;
    double process_var;
};

std::tuple<double, double, double> 
covariance_ellipse(
    const Eigen::Matrix2d& covariance_mat,
    double deviations = 1.0 
);


// vector because we don't know dt yet
std::pair<std::vector<double>, std::vector<double>>
simulate_realworld_neato(
    const KF_HELPER::Kf_Config& config
);

}