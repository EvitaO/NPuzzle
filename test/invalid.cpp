#include "gtest/gtest.h"
#include "../Puzzle.hpp"

TEST(controlSolvability, InvalidPuzzles3){
    Node n(3);
    std::vector<int> puzzle(3*3);
    puzzle[0] = 5;
    puzzle[1] = 8;
    puzzle[2] = 6;
    puzzle[3] = 1;
    puzzle[4] = 0;
    puzzle[5] = 4;
    puzzle[6] = 3;
    puzzle[7] = 7;
    puzzle[8] = 2;
    n.setPuzzle(puzzle);

    Puzzle  p(3, '0');
    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);

    puzzle[0] = 8;
    puzzle[1] = 7;
    puzzle[2] = 1;
    puzzle[3] = 2;
    puzzle[4] = 0;
    puzzle[5] = 5;
    puzzle[6] = 4;
    puzzle[7] = 3;
    puzzle[8] = 6;
    n.setPuzzle(puzzle);

    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);

    puzzle[0] = 8;
    puzzle[1] = 7;
    puzzle[2] = 2;
    puzzle[3] = 4;
    puzzle[4] = 0;
    puzzle[5] = 6;
    puzzle[6] = 1;
    puzzle[7] = 5;
    puzzle[8] = 3;
    n.setPuzzle(puzzle);

    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);
}

TEST(controlSolvability, InvalidPuzzles4){
    Node n(4);
    std::vector<int> puzzle(4*4);
    puzzle[0] = 15;
    puzzle[1] = 1;
    puzzle[2] = 13;
    puzzle[3] = 9;
    puzzle[4] = 2;
    puzzle[5] = 8;
    puzzle[6] = 6;
    puzzle[7] = 10;
    puzzle[8] = 7;
    puzzle[9] = 11;
    puzzle[10] = 4;
    puzzle[11] = 0;
    puzzle[12] = 14;
    puzzle[13] = 3;
    puzzle[14] = 5;
    puzzle[15] = 12;
    n.setPuzzle(puzzle);

    Puzzle  p(4, '0');
    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);

    puzzle[0] = 12;
    puzzle[1] = 3;
    puzzle[2] = 6;
    puzzle[3] = 2;
    puzzle[4] = 9;
    puzzle[5] = 5;
    puzzle[6] = 11;
    puzzle[7] = 10;
    puzzle[8] = 13;
    puzzle[9] = 4;
    puzzle[10] = 14;
    puzzle[11] = 0;
    puzzle[12] = 15;
    puzzle[13] = 7;
    puzzle[14] = 1;
    puzzle[15] = 8;
    n.setPuzzle(puzzle);

    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);

    puzzle[0] = 5;
    puzzle[1] = 15;
    puzzle[2] = 13;
    puzzle[3] = 4;
    puzzle[4] = 2;
    puzzle[5] = 8;
    puzzle[6] = 9;
    puzzle[7] = 3;
    puzzle[8] = 7;
    puzzle[9] = 0;
    puzzle[10] = 14;
    puzzle[11] = 11;
    puzzle[12] = 6;
    puzzle[13] = 10;
    puzzle[14] = 12;
    puzzle[15] = 1;
    n.setPuzzle(puzzle);

    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);
}

TEST(controlSolvability, InvalidPuzzles5){
    Node n(5);
    std::vector<int> puzzle(5*5);
    puzzle[0] = 21;
    puzzle[1] = 18;
    puzzle[2] = 14;
    puzzle[3] = 22;
    puzzle[4] = 10;
    puzzle[5] = 20;
    puzzle[6] = 11;
    puzzle[7] = 12;
    puzzle[8] = 7;
    puzzle[9] = 24;
    puzzle[10] = 2;
    puzzle[11] = 19;
    puzzle[12] = 8;
    puzzle[13] = 1;
    puzzle[14] = 0;
    puzzle[15] = 9;
    puzzle[16] = 15;
    puzzle[17] = 16;
    puzzle[18] = 4;
    puzzle[19] = 17;
    puzzle[20] = 5;
    puzzle[21] = 6;
    puzzle[22] = 3;
    puzzle[23] = 23;
    puzzle[24] = 13;
    n.setPuzzle(puzzle);

    Puzzle  p(5, '0');
    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);

    puzzle[0] = 7;
    puzzle[1] = 14;
    puzzle[2] = 20;
    puzzle[3] = 16;
    puzzle[4] = 3;
    puzzle[5] = 4;
    puzzle[6] = 5;
    puzzle[7] = 12;
    puzzle[8] = 19;
    puzzle[9] = 8;
    puzzle[10] = 6;
    puzzle[11] = 10;
    puzzle[12] = 13;
    puzzle[13] = 24;
    puzzle[14] = 0;
    puzzle[15] = 17;
    puzzle[16] = 18;
    puzzle[17] = 21;
    puzzle[18] = 11;
    puzzle[19] = 2;
    puzzle[20] = 23;
    puzzle[21] = 1;
    puzzle[22] = 22;
    puzzle[23] = 15;
    puzzle[24] = 9;
    n.setPuzzle(puzzle);

    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);

    puzzle[0] = 3;
    puzzle[1] = 15;
    puzzle[2] = 11;
    puzzle[3] = 23;
    puzzle[4] = 4;
    puzzle[5] = 22;
    puzzle[6] = 13;
    puzzle[7] = 24;
    puzzle[8] = 5;
    puzzle[9] = 7;
    puzzle[10] = 1;
    puzzle[11] = 16;
    puzzle[12] = 0;
    puzzle[13] = 2;
    puzzle[14] = 10;
    puzzle[15] = 17;
    puzzle[16] = 18;
    puzzle[17] = 12;
    puzzle[18] = 14;
    puzzle[19] = 21;
    puzzle[20] = 9;
    puzzle[21] = 8;
    puzzle[22] = 6;
    puzzle[23] = 19;
    puzzle[24] = 20;
    n.setPuzzle(puzzle);

    EXPECT_THROW(p.controlSolvability(n), std::runtime_error);
}
