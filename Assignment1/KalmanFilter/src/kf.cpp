#include "kf.hpp"

namespace KF{

    KalmanFilter::KalmanFilter(
        const int dt,
        const int steps,
        const double robot_vel,
        const double sensor_var,
        const double process_var
    ): 
        dt_(dt), 
        steps_(steps),
        robot_vel_(robot_vel),
        sensor_var_(sensor_var),
        process_var_(process_var)

    Eigen::Matrix2d get_Q(
        double dt,
        double var,
    ){
        const double q01 = 0.5 * var * dt * dt;
        const double q00 = q01 * q01;
        const double q11 = var * dt * dt;

        Eigen::Matrix2d Q;
        Q << q00, q01,
             q01, q11;
        
    return Q;
    }

    void KalmanFilter::update(double z, const Eigen::RowVector2d& H, double R)
    {
        // Innovation covariance: S = H P H^T + R   (1x1, extracted as scalar)
        double S = (H * P_ * H.transpose())(0, 0) + R;

        // Kalman gain: K = P H^T S^-1   (2x1)
        Eigen::Vector2d K = (P_ * H.transpose()) / S;

        // Innovation (measurement residual): y = z - H x   (scalar)
        double y = z - (H * x_)(0, 0);

        // Update state estimate and covariance
        x_ += K * y;
        P_ = P_ - K * H * P_;
    }
}