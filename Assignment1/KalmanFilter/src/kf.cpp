#include "kf.hpp"
#include <iostream>

namespace KF{

    KalmanFilter::KalmanFilter(
        const KF_HELPER::Kf_Config& config
    ): 
        dt_(config.dt), 
        steps_(config.steps),
        robot_vel_(config.robot_vel),
        sensor_var_(config.sensor_var),
        process_var_(config.process_var)

    {   
    
    }
        /*
        Set initial state of the kalman filter
        */
        void KalmanFilter::setState()
        {

            // Initial guess of state
            x_ = Eigen::Vector2d(10.0, 4.5);

            // Initial variance of state var
            P_ << 500.0, 0.0,
                  0.0,  49.0;

            // Process model
            F_ << 1.0, dt_,
                 0.0, 1.0;

            // Process noise
            Q_ = get_Q(dt_, process_var_);

            // Measurement model
            H_ << 1.0, 0.0;
            
            // Measurement variance
            R_ = sensor_var_;
        }

        /*
        Returns a white noise model Q according to dt and var
        */
        Eigen::Matrix2d 
        KalmanFilter::get_Q(int dt, double var)
        {
            const double q01 = 0.5 * var * dt * dt;
            const double q00 = q01 * q01;
            const double q11 = var * dt * dt;

            Eigen::Matrix2d Q;
            Q << q00, q01,
                q01, q11;
            
        return Q;
        }

        /*
        Returns a prediction update for pose and pose covariance according to the process model
        */
        std::pair<Eigen::Vector2d, Eigen::Matrix2d>
        KalmanFilter::predict()
        {
            // edit the pose and covariance directly
            x_ = F_ * x_;
            P_ = F_ * P_ * F_.transpose() + Q_;
            ++steps_;

            return {x_, P_};
        }
        
        /*
        Performs an update to x, P given observation z according to measurement model H and measurement noise R
        */
        void KalmanFilter::update(double z)
        {
            // Innovation covariance: S = H P H^T + R   (1x1, extracted as scalar)
            double S = (H_ * P_ * H_.transpose())(0, 0) + R_;

            // Kalman gain: K = P H^T S^-1   (2x1)
            Eigen::Vector2d K = (P_ * H_.transpose()) / S;

            // Innovation (measurement residual): y = z - H x   (scalar)
            double y = z - (H_ * x_)(0, 0);

            // Update state estimate and covariance
            x_ += K * y;
            P_ = P_ - K * H_ * P_;
        }

        std::pair<std::vector<Eigen::Vector2d>, std::vector<Eigen::Matrix2d>>
        KalmanFilter::solve(const std::vector<double>& observations)
        {
            std::cout << "Solving the global optimization..." << std::endl;

            std::vector<Eigen::Vector2d> x_filter;
            std::vector<Eigen::Matrix2d> P_filter;

            // Pre allocate size
            x_filter.reserve(observations.size());
            P_filter.reserve(observations.size());

            for (double z : observations)
            {
                predict();
                update(z);
                x_filter.push_back(x_);
                P_filter.push_back(P_);
            }
            
            return {x_filter, P_filter};
        }

} // namespace KF