#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "quick_select.hpp"

using Point2D = std::array<double, 2>;

// The pivot is random, so the exact array layout changes between runs.
// Check what must always be true instead: the median lands at the middle,
// everything left of it is <= and everything right of it is >= (in dim).
void expect_partitioned(const std::vector<Point2D>& pts, int index, int dim){
    for (int i = 0; i < index; i++)
        EXPECT_LE(pts[i][dim], pts[index][dim]);
    for (int i = index + 1; i < (int)pts.size(); i++)
        EXPECT_GE(pts[i][dim], pts[index][dim]);
}

TEST(QuickSelect, Simple_2D_Case_dim0){

    std::vector<Point2D> pts = {{2.5, 9}, {1.0, 3}, {2.7, 1}, {7, 4}, {4, 8}};

    // x values sorted: 1.0, 2.5, 2.7, 4, 7 -> median is 2.7
    int index = QS::quick_select(pts, 0, 4, 3, 0);

    EXPECT_EQ(index, 2);
    EXPECT_EQ(pts[index], (Point2D{2.7, 1}));
    expect_partitioned(pts, index, 0);
}

TEST(QuickSelect, Simple_2D_Case_dim1){

    std::vector<Point2D> pts = {{2.5, 9}, {1.0, 3}, {2.7, 1}, {7, 4}, {4, 8}};

    // y values sorted: 1, 3, 4, 8, 9 -> median is 4
    int index = QS::quick_select(pts, 0, 4, 3, 1);

    EXPECT_EQ(index, 2);
    EXPECT_EQ(pts[index], (Point2D{7, 4}));
    expect_partitioned(pts, index, 1);
}
