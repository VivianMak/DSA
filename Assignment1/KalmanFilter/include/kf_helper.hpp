#pragma once

#include <Eigen/Dense>
#include <tuple>
#include <array>
#include <optional>


namespace KF_HELPER{

struct Kf_Config{
    int dt;
    int steps;
    double robot_vel;
    double sensor_var;
    double process_var;
};



// Simulates the movement of a Neato and measurement in the world.
std::pair<std::vector<double>, std::vector<double>>
simulate_realworld_neato(
    const KF_HELPER::Kf_Config& config
);


// 2D covariance matrix as an ellipse
std::tuple<double, double, double> 
covariance_ellipse(
    const Eigen::Matrix2d& covariance_mat,
    double deviations = 1.0 
);

// Convienence function for plotting
std::vector<double> _std_tuple_of(
    std::optional<std::vector<double>> var = std::nullopt,
    std::optional<std::vector<double>> std = std::nullopt,
    std::optional<std::vector<double>> interval = std::nullopt
);

// Plotting function
void plot_covariance();



}