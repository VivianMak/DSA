#include "kf_helper.hpp"

#include <cmath>
#include <iostream>
#include <random>
#include <fstream>

namespace KF_HELPER
{

    std::tuple<double, double, double> 
    covariance_ellipse(
        const Eigen::Matrix2d& covariance_mat,
        double deviations
    )
    {
        Eigen::JacobiSVD<Eigen::Matrix2d> svd(covariance_mat, Eigen::ComputeFullU);
        const Eigen::Matrix2d& U = svd.matrixU();
        const Eigen::Vector2d& s = svd.singularValues();

        double angleRad = std::atan2(U(1, 0), U(0, 0));
        double widthRadius = deviations * std::sqrt(s(0));
        double heightRadius = deviations * std::sqrt(s(1));

        if (heightRadius > widthRadius) {
            std::cout << "width must be greater than height" << std::endl;
            // throw std::invalid_argument("width must be greater than height");
        }

        return {angleRad, widthRadius, heightRadius};
    }


    std::pair<std::vector<double>, std::vector<double>>
    simulate_realworld_neato(const KF_HELPER::Kf_Config& config)
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
            xs.push_back(x);
            zs.push_back(x + randn(gen) * std::sqrt(config.sensor_var));
        }
            
        return {xs, zs};
    }
}  // namespace KF_HELPER