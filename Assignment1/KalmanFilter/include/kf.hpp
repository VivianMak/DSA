#pragma once

#include "kf_helper.hpp"
#include <Eigen/Dense>
#include <utility>
#include <vector>


namespace KF{

class KalmanFilter{
    public:
        KalmanFilter(
            const KF_HELPER::Kf_Config& config
        );

        // Sets the initial state and covariance before running predict/update.
        void setState(
            const Eigen::Vector2d& x0 = Eigen::Vector2d(10.0, 4.5),
            const Eigen::Matrix2d& P0 = (Eigen::Matrix2d() << 500.0, 0.0,
                                                                0.0, 49.0).finished(),
            const Eigen::RowVector2d& H = Eigen::RowVector2d(1.0, 0.0),
            std::optional<double> R = std::nullopt
        );

        // Returns a white noise model Q according to dt and var
        Eigen::Matrix2d
        get_Q(
            int dt,
            double var
        );

        std::pair<Eigen::Vector2d, Eigen::Matrix2d> predict();

        void update(double z);

        std::pair<std::vector<Eigen::Vector2d>, std::vector<Eigen::Matrix2d>>
        solve(
            const std::vector<double>& observations
        );

        // Accessors - avoid copying
        int steps() const { return steps_; }
        int dt() const { return dt_; }
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
        Eigen::Matrix2d F_ = Eigen::Matrix2d::Identity();
        Eigen::Matrix2d Q_ = Eigen::Matrix2d::Zero();
        Eigen::RowVector2d H_ = Eigen::RowVector2d::Zero();
        double R_ = 0.0;

    };
}   // namespace KF