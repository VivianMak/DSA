#include "kf_helper.hpp"

#include <cmath>
#include <iostream>

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


std::pair<std::array<float, dt>, std::array<float, dt>>
simulate_realworld_neato(
    int sensor_var;
    int process_var;

    float vel;
    int step;
    float dt;
)
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

    // in python
    x = 0.  # initial position
    sensor_std = math.sqrt(sensor_var)  # compute sensor standard deviation from variance
    process_std = math.sqrt (process_var)  # compute process standard deviation from variance
    xs, zs = [] ,[]
    for i in range(step):
        v = vel + (np.random.randn() * process_std)
        x += v * dt  # simple velocity based update
        xs.append(x)
        zs.append(x + np.random.randn() * sensor_std)  # noise corrupted observation
    return np.array(xs), np.array(zs)
}


}  // namespace KF_HELPER