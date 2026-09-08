#pragma once

#include <Eigen/Dense>
#include <tuple>
#include <array

namespace KF_HELPER{

using Mat2d = Eigen::Matrix2d

std::tuple<double, double, double> 
covariance_ellipse(
    const Eigen::Matrix2d& covariance_mat,
    double deviations = 1.0 
);


std::pair<std::array<float, dt>, std::array<float, dt>>
simulate_realworld_neato(
    int sensor_var;
    int process_var;

    float vel;
    int step;
    float dt;
);



}