#pragma once

#include "kf_helper.hpp"
#include <Eigen/Dense>
#include <utility>

namespace KF{

class KalmanFilter{
    public:
        KalmanFilter(
            const KF_HELPER::Kf_Config& config
        );

        // Sets the initial state and covariance before running predict/update.
        void setState();

        // Returns a white noise model Q according to dt and var
        Eigen::Matrix2d
        get_Q(
            double dt,
            double var
        );

        std::pair<Eigen::Vector2d, Eigen::Matrix2d>
        predict(
            const Eigen::Matrix2d& F,
            const Eigen::Matrix2d& Q
        );

        void update(
            double z, 
            const Eigen::RowVector2d& H, 
            double R
        );

        std::pair<std::vector<double>, std::vector<double>>
        solve(
            const std::vector<double> &observations
        );

        // Accessors - avoid copying
        int steps() const { return steps_; }
        double dt() const { return dt_; }
        double robot_vel() const { return robot_vel_; }
        const Eigen::Vector2d& state() const { return x_; }
        const Eigen::Matrix2d& covariance() const { return P_; }

    private:
        int dt_;
        int steps_;
        double robot_vel_;
        double sensor_var_;
        double process_var_;

        Eigen::Vector2d x_ = Eigen::Vector2d::Zero();
        Eigen::Matrix2d P_ = Eigen::Matrix2d::Identity();

    };
}   // namespace KF