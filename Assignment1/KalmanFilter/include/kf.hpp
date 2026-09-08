#pragma once
#include <functional>
#include <iostream>
#include <memory>
#include <Eigen/Dense>
#include <Eigen/Sparse>

namespace KF{

class KalmanFilter{
    public:
        KalmanFilter(
            const int dt,
            const int steps,
            const double robot_vel,
            const double sensor_var,
            const double process_var
        )

        Eigen::Matrix2d
        get_Q(
            double dt,
            double var
        )

        std::pair<std::double, std::double>
        predict(
            const x;
            const P;
            const F; 
            const Q; 
        )

        void update(double z, const Eigen::RowVector2d& H, double R);

        // Accessors - avoid copying
        int steps() const { return steps_; }
        double dt() const { return dt_; }
        const Eigen::Vector2d& robot_vel() const { return robot_vel_; }
        const Eigen::Vector2d& state() const { return x_; }
        const Eigen::Matrix2d& covariance() const { return P_; }

    private:
        int dt_;
        int steps_;
        double robot_vel_;
        double sensor_var_;
        double process_var;

    };
}
#endif // KF