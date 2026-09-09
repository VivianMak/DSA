#include "kf_helper.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <fstream>

namespace KF_HELPER
{
    
    /*
    * Simulates the movement of a Neato and measurement in the world.
    *
    * @param sensor_var  (int): random sensor variance
    * @param process_var (int): process noise varaince
    * @param vel (float): velocity of neato
    * @param step (int): number of simulation snapshots
    * @param dt (float): time delta between simulation snapshots
    * 
    * @return xs (array(float)): real positions
    * @return zs (array(float)): observed positions
    */

    std::pair<std::vector<double>, std::vector<double>>
    simulate_realworld_neato(const KF_HELPER::Kf_Config& config)
    {
        double x = 0;

        std::vector<double> xs(config.steps);
        std::vector<double> zs(config.steps);

        // Generate a random value
        // 1. Initialize a random device to seed the generator
        std::random_device rd;
        // 2. Initialize the Mersenne Twister engine with the seed
        std::mt19937 gen(rd());
        // 3. Define a standard normal distribution (mean = 0.0, std_dev = 1.0)
        std::normal_distribution<double> randn(0.0, 1.0);

        for (int i = 0; i < config.steps; i++)
        {
            // Make a list of real and observed positions
            float v = config.robot_vel + (randn(gen) * std::sqrt(config.process_var));
            x += v * config.dt;
            xs[i] = x;
            zs[i] = x + randn(gen) * std::sqrt(config.sensor_var);
        }
            
        return {xs, zs};
    }


    // Temp plotting functions
    
    std::tuple<double, double, double> covariance_ellipse(
        const Eigen::Matrix2d& covariance_mat,
        double deviations
    )
    {
        return {0.0, 0.0, 0.0};
    }

    std::vector<double> _std_tuple_of(
        std::optional<std::vector<double>> var,
        std::optional<std::vector<double>> std_dev,
        std::optional<std::vector<double>> interval
    )
    {
        return {};
    }

    void plot_covariance(){}

}  // namespace KF_HELPER