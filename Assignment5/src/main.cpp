#include <iostream>
#include <string>

#include "genome.hpp"
#include "matrix.hpp"
#include "needleman_wunsch.hpp"

int main()
{   
    // // name
    // using Matrix::Matrix;
    // Matrix<int> M(2, 3, 7);
    // std::cout << M;
    // return 0;

    NW::NeedlemanWunsch nw(
        std::string(GenomeData::genomeSnippet), // g1
        std::string(GenomeData::testAgainst)    // g2
    );

    auto [a1, a2] = nw.find_global_alignment();

    std::cout << "Score: " << nw.score() << '\n';
    std::cout << a1 << '\n';
    std::cout << a2 << '\n';

    return 0;
}
