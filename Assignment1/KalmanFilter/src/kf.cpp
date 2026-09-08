#include "kf.hpp"

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
            Eigen::RowVector2d x(10.0, 4.5)
            // Initial variance of state var
            Eigen::Matrix2d P << 500.0, 0,
                                 0,  49.0;

            // Process model
            Eigen::Matrix2d F << 1, dt_,
                                 0, 1;

            // Process noise
            Eigen::Matrix2d Q = KalmanFilter::get_Q(dt_, process_var_);

            // Measurement model
            std::array<double, 2> H(1.0, 0.0);
            
            // Measurement variance
            std::array<double, 1> R(sensor_var_);
        }

        /*
        Returns a white noise model Q according to dt and var
        */
        Eigen::Matrix2d 
        KalmanFilter::get_Q(double dt, double var)
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
        KalmanFilter::predict(const Eigen::Matrix2d& F, const Eigen::Matrix2d& Q)
        {
            // edit the pose and covariance directly
            x_ = F * x_;
            P_ = F * P_ * F.transpose() + Q;
            ++steps_;

            return {x_, P_}
        }
        
        /*
        Performs an update to x, P given observation z according to measurement model H and measurement noise R
        */
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

        std::pair<std::vector<double>, std::vector<double>>
        KalmanFilter::solve(const std::vector<double> &observations)
        {
            std::cout << "Solving the global optimization..." << std::endl;

            std::vector<double> x_filter;
            std::vector<double> P_filter;

            for (z = 0; z < observations; z++)
            {
                x_predict, P_predict = KalmanFilter::predict(x, P, F, Q);
                x, P = KalmanFilter::update(&x_predict, &P_predict, z, H, R);
                x_filter.push_back(x);
                P_filter.push_back(P);
            }
            
            return {x_filter, P_filter};
        }

} // namespace KF