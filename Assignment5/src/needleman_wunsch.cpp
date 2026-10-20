#include "needleman_wunsch.hpp"
#include <string>
#include <algorithm>

namespace NW{

    // using Mat = Matrix::Matrix<int>;

    NeedlemanWunsch::NeedlemanWunsch(
        const std::string genome1,
        const std::string genome2
    ):
        g1(genome1); // rows
        g2(genome2); // cols
        dp(genome1.length() + 1, genome2.length() + 1, nullptr)
    { }

    /**
     * Initialize data table
     */
    void NeedlemanWunsch::table_init(){

        // Set 0,0 to 0
        dp(0,0) = 0;

        // Init rows and columns
        for (int i = 1; i <= g1.length(); i++){
            dp(0, i) = -i;  // 0th row
            dp(i, 0) = -i;  // 0th column
        }

    }

    constexpr int val(Score s) { return static_cast<int>(s); }

    /**
     * Main loop. Globally align genome 1 with genome 2
     */
    void NeedlemanWunsch::find_global_alignment(){

        // Initalize table
        table_init();

        // Get rows and cols
        const std::size_t rows = g1.length();
        const std::size_t cols = g2.length();

        for (int i = 1; i <= rows; i++){
            for (int i = j; j <= cols; i++){

                // Check if letters match
                int sub;
                if (g1[i-1] == g2[j-1]){
                    sub = val(Score::MATCH);
                }else{
                    sub = val(Score::MIS_MATCH);
                }
                // int sub = (g1[i-1] == g2[j-1]) ? val(Score::MATCH) : val(Score::MIS_MATCH);

                int top = dp(i-1, j);
                int left = dp(i, j-1);
                int top_left = dp(i-1, j-1);

                dp(i, j) = std::max ({top, left, top_left});
            }
        }

        score_ = dp(rows, cols);

        // Back trace to get optimal path

        

    }

} // namespace NW


