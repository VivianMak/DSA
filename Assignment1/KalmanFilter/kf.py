import numpy as np
import scipy as sp
import math
import matplotlib.pyplot as plt

# Helper code adapted from filterpy and https://github.com/rlabbe/Kalman-and-Bayesian-Filters-in-Python/blob/master/kf_book/mkf_internal.py

def covariance_ellipse(P, deviations=1):
    """
    Returns a tuple defining the ellipse representing the 2 dimensional
    covariance matrix P.

    Parameters
    ----------

    P : nd.array shape (2,2)
       covariance matrix

    deviations : int (optional, default = 1)
       # of standard deviations. Default is 1.

    Returns (angle_radians, width_radius, height_radius)
    """

    U, s, _ = sp.linalg.svd(P)
    orientation = math.atan2(U[1, 0], U[0, 0])
    width = deviations * math.sqrt(s[0])
    height = deviations * math.sqrt(s[1])

    if height > width:
        raise ValueError('width must be greater than height')

    return (orientation, width, height)

def _std_tuple_of(var=None, std=None, interval=None):
    """
    Convienence function for plotting. Given one of var, standard
    deviation, or interval, return the std. Any of the three can be an
    iterable list.

    Examples
    --------
    >>>_std_tuple_of(var=[1, 3, 9])
    (1, 2, 3)

    """

    if std is not None:
        if np.isscalar(std):
            std = (std,)
        return std


    if interval is not None:
        if np.isscalar(interval):
            interval = (interval,)

        return np.norm.interval(interval)[1]

    if var is None:
        raise ValueError("no inputs were provided")

    if np.isscalar(var):
        var = (var,)
    return np.sqrt(var)

def plot_covariance(
        mean, cov=None, variance=1.0, std=None, interval=None,
        ellipse=None, title=None, axis_equal=True,
        show_semiaxis=False, show_center=True,
        facecolor=None, edgecolor=None,
        fc='none', ec='#004080',
        alpha=1.0, xlim=None, ylim=None,
        ls='solid'):
    from matplotlib.patches import Ellipse
    import matplotlib.pyplot as plt

    if cov is not None and ellipse is not None:
        raise ValueError('You cannot specify both cov and ellipse')

    if cov is None and ellipse is None:
        raise ValueError('Specify one of cov or ellipse')

    if facecolor is None:
        facecolor = fc

    if edgecolor is None:
        edgecolor = ec

    if cov is not None:
        ellipse = covariance_ellipse(cov)

    if axis_equal:
        plt.axis('equal')

    if title is not None:
        plt.title(title)

    ax = plt.gca()

    angle = np.degrees(ellipse[0])
    width = ellipse[1] * 2.
    height = ellipse[2] * 2.

    std = _std_tuple_of(variance, std, interval)
    for sd in std:
        e = Ellipse(xy=mean, width=sd*width, height=sd*height, angle=angle,
                    facecolor=facecolor,
                    edgecolor=edgecolor,
                    alpha=alpha,
                    lw=2, ls=ls)
        ax.add_patch(e)
    x, y = mean
    if show_center:
        plt.scatter(x, y, marker='+', color=edgecolor, label="Filter Guess")

    if xlim is not None:
        ax.set_xlim(xlim)

    if ylim is not None:
        ax.set_ylim(ylim)

    if show_semiaxis:
        a = ellipse[0]
        h, w = height/4, width/4
        plt.plot([x, x+ h*np.cos(a+np.pi/2)], [y, y + h*np.sin(a+np.pi/2)])
        plt.plot([x, x+ w*np.cos(a)], [y, y + w*np.sin(a)])


def plot_track_ellipses(ps, cov, title):
    plt.title(title)

    for i,p in enumerate(cov):
        plot_covariance(
              (i, ps[i]), cov=p, variance=1,
               axis_equal=False, ec='g', alpha=0.5)



def simulate_realworld_neato(sensor_var, process_var, vel=1.0, step=1, dt=1.):
    """Simulates the movement of a Neato and measurement in the world.
    Input: 
        sensor_var
        process_var
        vel (float): velocity of the bot
        step (int): number of simulation snapshots
        dt (float): time delta between simulation snapshots
    Return:
        xs (array(float)): real positions
        zs (array(float)): observed positions
    """
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

xs, zs = simulate_realworld_neato(0.2, 0.1, vel=1., step=10, dt=0.5)
plt.plot(xs, marker=".", ms=10, label="Real Path")
plt.plot(zs, linestyle="--", marker="*", ms=10, label="Observations")
plt.title("Simulate Neato Position")
plt.legend()
plt.show()

def get_Q(dt, var):
    """Returns a white noise model Q according to dt and var"""
    Q = np.array([[(0.5*var*dt**2)**2, 0.5*var*dt**2],[0.5*var*dt**2, var*dt**2]])
    print("Q", Q.dtype, Q)
    return Q

def predict(x, P, F, Q):
    """Returns a prediction update for pose and pose covariance according to the process model"""
    xt = F @ x
    Pt = F @ P @ F.T + Q
    # print("Predict functoin types:")
    # print("xt", xt.dtype)
    # print("Pt", Pt.dtype)
    return xt, Pt

# # test your prediction on a quick sample case
# dt = 1.
# x = np.array([1., 0.5]).T
# P = np.array([[500, 0],
#               [0, 49]])
# F = np.array([[1, dt],
#               [0, 1]])
# Q = get_Q(dt, 1.)

# xt_sol = np.array([1.5, 0.5]).T
# Pt_sol = np.array([[549.25, 49.5],[49.5, 50.]])

# x1, P1 = predict(x, P, F, Q)
# print(x1[0] == xt_sol[0] and x1[1] == xt_sol[1])
# print(P1[0][0] == Pt_sol[0][0] and P1[1][0] == Pt_sol[1][0] and P1[0][1] == Pt_sol[0][1] and P1[1][1] == Pt_sol[1][1])


def update(x, P, z, H, R, counter):
    """Performs an update to x, P given observation z according to measurement model H and measurement noise R"""
    # if counter == 1:
    #     print("x", x.dtype, x)
    #     print("P", P.dtype, P)
    #     print("z", z.dtype, z)
    #     print("H", H.dtype, H)
    #     print("R", R.dtype, R)

    # counter += 1

    S = H @ P @ H.T + R
    K = P @ H.T @ sp.linalg.inv(S)
    y = z - H @ x
    x += K @ y
    P = P - K @ H @ P

    return x, P

# # test your update with a simple test case
# dt = 1.
# x = np.array([1., 0.5]).T
# z = np.array([1.])  # the exact measurement of the real world...should reduce our uncertainty in position
# P = np.array([[500, 0],
#               [0, 49]])
# F = np.array([[1, dt],
#               [0, 1]])
# Q = get_Q(dt, 1.)
# H = np.array([[1., 0.]])
# R = np.array([[10]])

# xt_sol = np.array([1., 0.5]).T
# Pt_sol = np.array([[9.80392157, 0.],[0, 49.]])

# x1, P1 = update(x, P, z, H, R)

# print(x1[0] == xt_sol[0] and x1[1] == xt_sol[1])
# print(P1[0][0]-Pt_sol[0][0] < 0.0001 and P1[1][0] == Pt_sol[1][0] and P1[0][1] == Pt_sol[0][1] and P1[1][1] == Pt_sol[1][1])


# Set up our models
steps = 50
dt = 1
robot_vel = 2.0
sensor_var = 100.
process_var = 0.1

x = np.array([10., 4.5]).T  # initial guess of state
P = np.diag([500., 49.])  # initial variance on state variables
F = np.array([[1, dt],
              [0, 1]])  # process model
Q = get_Q(dt, var=0.01)#process_var)  # process noise
H = np.array([[1., 0.]])  # measurement model
R = np.array([[10.]])#sensor_var]])  # measurement variance

true_poses, observations = simulate_realworld_neato(sensor_var, process_var, vel=robot_vel, step=steps, dt=dt)
x_filter = []
P_filter = []


# Iterate through observations
for z in observations:
    x_predict, P_predict = predict(x, P, F, Q)
    x, P = update(x_predict, P_predict, z, H, R, counter=1)
    x_filter.append(x)
    P_filter.append(P)


# # Plot the results
# fig = plt.figure()
# xf, Pf = np.array(x_filter), np.array(P_filter)
# plt.plot(true_poses, marker=".", ms=10, label="True Path")
# plt.plot(observations, marker="*", ms=10, lw=0, label="Observations")
# plt.plot(xf[:,0], lw=1, label="Filter Estimate")
# plot_track_ellipses(xf[:,0], Pf, title="track")
# plt.legend(["True Path", "Observations", "Filter Guess"])
# plt.gcf().set_size_inches(12, 6)
# plt.show()

# # Examine the velocity estimate
# fig = plt.figure()
# plt.plot(np.ones_like(xf[:,1])*robot_vel, label="True Velocity")
# plt.plot(xf[:,1], lw=5, label="Filter Estimate Velocity")
# plt.legend()
# plt.gcf().set_size_inches(12, 6)
# plt.show()

# # Examine the covariance over time
# fig, ax = plt.subplots(1,2)
# ax[0].plot(Pf[:,0,0], lw=5, label="Position Variance")
# ax[0].set_title("Position Variance")
# ax[1].plot(Pf[:,1,1], lw=5, label="Velocity Variance")
# ax[1].set_title("Velocity Variance")
# fig.set_size_inches(12, 6)
# plt.show()