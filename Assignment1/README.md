# Assignment 1

Vivian Mak

Assignment 1 Description: https://olindsa2026.github.io/assignments/assignment_01.html

<br>

## Identifying Effective Strategies for Learning

1. A moment where learning went really well was with my Discrete homework group. The strategy for a productive group was straightforward and very structured. We were to attempt the questions beforehand, come to the meetings with questions and confusions, and divide the writeup for submission. Being prepared for academic discussion worked well because it led me to feel more confident in my answers and unknowns. Additional factors included having teammates who are as passionate and willing to help others. I also notice detailed feedbacks help me improve.

2. Strategies that don't lead to effective learning more me are getting taught concepts (in an overview way) and immediately having to apply it. The main thing is not having time for me to individually think through the problem. Courses like ISIM where I did not recieve any feedback wasn't productive learning.

3. I agree with the framing. I think AI is a good tutor if used intentionally. With this course, since I am learning a new language, using AI to help learn conventions, syntax, and good coding practices will be useful.

4. To be successful in this course, I aim to be intentional about the code I write and be able to explain the different design decisions I choose. With respect to AI, I want to use this tool after I have figured out the problem and want to find additonal ways to improve.

5. They seem useful. One activity I would propose is a project interview where the professor asks questions about the project and I can ask for specific feedback in return. I think this 1 on 1 time would be effective for my learning.

6. Additional resources for cpp, learning dsa concepts applied to the robotics field.

<br>

## Translating Your Old Code

Choose a piece of code that you’ve written in a programming language other than C++. Translate the code to run in C++. For simplicity, you may want to choose some code that will not require interacting with a lot of external libraries (although the course how-to discusses how to add dependencies to your project) 

> Include a link to a GitHub repo containing your port of the code. Include a writeup that describes the purpose of the code and how you found the process of translating the code to Kotlin (or the language you wind up choosing). Feel free to touch on the good, the bad, and the ugly.



### Kalman Filter: Python → C++
---

- [`include/`](KalmanFilter/include) - contains the headers where the functions are declared
- [`src/`](KalmanFilter/src/) - contains the implementation of the functions
- [`tests/`](tests/test_kf.cpp) - contains the unit tests for kalman filter and [`tests/CMakeLists.txt`](tests/CMakeLists.txt) compiles ONLY the unit tests
- [`CMakeLists.txt`](CMakLists.txt) - compiles the code for kalman filter

**How to run:**

```sh
mkdir build && cd build
cmake ..
make
./main      # to run kalman filter

ctest --output-on-failure   # to run unit tests
```

**Purpose of a Kalman Filter**

The kalman filter, often applied in robotics, aims to fuse the physical world with sensor measurements. This is important because it is hard to 100% trust internal sensors with an unpredictable environment. The filter is divided into two stages: predict and update. In the predict step, we make an estimated position and estimated error matrix (sensor and world). In the update step, we calculate a kalman gain which weights the trust between sensor and world, then update the error based on the new time stamp's reading.

Because we can keep track of the time and assume a constant-velocity model, we can derive the position of the next timestep with _Position = Velocity * Time_.


**Process of Translating to C++**

The only C++ code I've written was for Softsys which teaches C. Through Softsys, I was able to learn the concepts but self-taught the syntax. My final project for that course was a [pose graph optimization](https://github.com/VivianMak/pose_graph_optimization_for_SLAM) implementation for SLAM from scratch. 

This was very long ago, so I had to relearn a lot. Thinking about how to separate the implementation was difficult, but I found that having to write all the types helps me think through difficult math problems.

One thing I would like to get feedback on is the code architecture and how I would make this more modular for integration of other code pieces.

<br>

## Implementing Meeting Scheduler

Implement an algorithm that determines whether a collection of meetings contains a conflict (as we discussed in the [day 1](../in_class/day01) page).

It's up to you how you pass data into your program.  You could read it from a file, hard code a test input into your main function, etc.

* First implement the straightforward algorithm that checks pairs of meetings.
* Develop a second algorithm that sorts the meetings in a useful way so you can check for conflicts more easily.  You should not implement your own search function, but instead use your language's built-in sort function.
* Write unit tests for both implementations, including edge cases such as one meeting ending exactly when another starts. For each algorithm (the straightforward one and the one based sorting), describe how you expect its running time to grow with $n$.  As mentioned on day 1, sorting has runtime $\Theta(n \log n)$.