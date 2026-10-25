#include <gtest/gtest.h>

#include "needleman_wunsch.hpp"

TEST(NW, SimpleCase){

    std::string g1 = "GT";
    std::string g2 = "GAT";

    NW::NeedlemanWunsch nw(g1, g2);
    auto [a1, a2] = nw.find_global_alignment();

    EXPECT_EQ(a1, "G-T");
    EXPECT_EQ(a2, "GAT");
    EXPECT_EQ(nw.score(), 1);
}