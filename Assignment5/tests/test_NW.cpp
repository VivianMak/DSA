#include <gtest/gtest.h>

#include "needleman_wunsch.hpp"

TEST(NW, SimpleCase_one_mismatch){

    std::string g1 = "GT";
    std::string g2 = "GAT";

    NW::NeedlemanWunsch nw(g1, g2);
    auto [a1, a2] = nw.find_global_alignment();

    EXPECT_EQ(a1, "G-T");
    EXPECT_EQ(a2, "GAT");
    EXPECT_EQ(nw.score(), 1);
}

TEST(NW, SimpleCase_all_aligned){

    std::string g1 = "GAT";
    std::string g2 = "GAT";

    NW::NeedlemanWunsch nw(g1, g2);
    auto [a1, a2] = nw.find_global_alignment();

    EXPECT_EQ(a1, "GAT");
    EXPECT_EQ(a2, "GAT");
    EXPECT_EQ(nw.score(), 3);
}

TEST(NW, all_mismatch){

    std::string g1 = "TTT";
    std::string g2 = "GGG";

    NW::NeedlemanWunsch nw(g1, g2);
    auto [a1, a2] = nw.find_global_alignment();

    EXPECT_EQ(a1, "TTT");
    EXPECT_EQ(a2, "GGG");
    EXPECT_EQ(nw.score(), -3);
}

TEST(NW, single_char){

    std::string g1 = "T";
    std::string g2 = "G";

    NW::NeedlemanWunsch nw(g1, g2);
    auto [a1, a2] = nw.find_global_alignment();

    EXPECT_EQ(a1, "T");
    EXPECT_EQ(a2, "G");
    EXPECT_EQ(nw.score(), -1);
}

TEST(NW, no_char){

    std::string g1 = "";
    std::string g2 = "";

    NW::NeedlemanWunsch nw(g1, g2);
    auto [a1, a2] = nw.find_global_alignment();

    EXPECT_EQ(a1, "");
    EXPECT_EQ(a2, "");
    EXPECT_EQ(nw.score(), 0);
}