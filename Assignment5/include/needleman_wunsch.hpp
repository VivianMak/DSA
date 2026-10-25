#pragma once

#include "matrix.hpp"
#include <string>

namespace NW{

using Mat = Matrix::Matrix<int>;
enum class Score : int {
    MATCH = 1,
    MIS_MATCH = -1,
    INDEL = -1
};

class NeedlemanWunsch {
    public:
        NeedlemanWunsch(
            const std::string genome1,
            const std::string genome2
        );

        void table_init();

        std::pair<std::string, std::string>
        find_global_alignment();

        int score() const { return score_; }


    private:
        std::string g1;
        std::string g2;

        Mat dp;
        int score_ = 0;
        int gap_ = -1;
        std::pair<std::string, std::string> aligned_;

 };
} // namespace NW