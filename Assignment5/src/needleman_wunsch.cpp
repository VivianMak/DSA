#include "needleman_wunsch.hpp"
#include <string>
#include <algorithm>
#include <limits>
#include <stdexcept>

namespace NW{

    // using Mat = Matrix::Matrix<int>;

    // Marks a dp cell that has not been computed yet rather than 0
    constexpr int UNSET = std::numeric_limits<int>::min();

    NeedlemanWunsch::NeedlemanWunsch(
        const std::string genome1,
        const std::string genome2
    ):
        g1(genome1), // rows
        g2(genome2), // cols
        dp(genome1.length() + 1, genome2.length() + 1, UNSET)
    { }

    /**
     * Initialize data table
     */
    void NeedlemanWunsch::table_init(){

        // Set 0,0 to 0
        dp(0,0) = 0;

        // Init 0th column (g1 is rows)
        for (std::size_t i = 1; i <= g1.length(); i++){
            dp(i, 0) = gap_ * static_cast<int>(i);
        }

        // Init 0th row (g2 is cols)
        for (std::size_t j = 1; j <= g2.length(); j++){
            dp(0, j) = gap_ * static_cast<int>(j);
        }

    }

    constexpr int val(Score s) { return static_cast<int>(s); }

    /**
     * Main loop. Globally align genome 1 with genome 2
     */
    std::pair<std::string, std::string> 
    NeedlemanWunsch::find_global_alignment(){

        // Initalize table
        table_init();

        // Get rows and cols
        const std::size_t rows = g1.length();
        const std::size_t cols = g2.length();

        // Build dp table
        for (int i = 1; i <= rows; i++){
            for (int j = 1; j <= cols; j++){

                // Check if letters match
                int sub;
                if (g1[i-1] == g2[j-1]){
                    sub = val(Score::MATCH);
                }else{
                    sub = val(Score::MIS_MATCH);
                }

                // int sub = (g1[i-1] == g2[j-1]) ? val(Score::MATCH) : val(Score::MIS_MATCH);

                int top = dp(i-1, j) + gap_;
                int left = dp(i, j-1) + gap_;
                int top_left = dp(i-1, j-1) + sub; // diagonal: match/mismatch

                dp(i, j) = std::max ({top, left, top_left});
            }
        }

        // Every cell should have been written by now
        for (std::size_t i = 0; i <= rows; i++){
            for (std::size_t j = 0; j <= cols; j++){
                if (dp(i, j) == UNSET){
                    throw std::logic_error("dp table has an unfilled cell");
                }
            }
        }

        score_ = dp(rows, cols);

        // Back trace to get optimal path

        // set new empty strings
        std::string a1, a2;

        // pre allocate for worst case scenario
        a1.reserve(rows + cols);
        a2.reserve(rows + cols);

        std::size_t i=rows, j=cols;

        // Back trace for optimal path until 0,0
        while(i > 0 || j> 0){

            // Diagonal Case
            if (i > 0 && j > 0){

                // Check if letters match
                int sub;
                if (g1[i-1] == g2[j-1]){
                    sub = val(Score::MATCH);
                }else{
                    sub = val(Score::MIS_MATCH);
                }

                // Check if diagonal is the optimal path
                if (dp(i,j) == dp(i-1, j-1) + sub){

                    // Copy real character from g1, g2
                    a1.push_back(g1[i - 1]);   
                    a2.push_back(g2[j - 1]);

                    i--;
                    j--;
                    continue;
                }
            }

            // Up Case
            if (i > 0 && dp(i, j) == dp(i - 1, j) + gap_){

                // Copy real character from g1 and - for g2
                a1.push_back(g1[i - 1]);  
                a2.push_back('-');  

                i--;
                continue;
            }

            // Left Case
            a1.push_back('-');  
            a2.push_back(g2[j - 1]);

            j--;
        }

        // Reverse the strings
        std::reverse(a1.begin(), a1.end());
        std::reverse(a2.begin(), a2.end());

        return {a1, a2};


        

    }

} // namespace NW