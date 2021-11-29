#include "gtest/gtest.h"
#include "../Puzzle.hpp"

TEST(controlSolvability, ValidPuzzles3){
    Node n(3);
    std::vector<int> puzzle(3*3);
    puzzle[0] = 8;
    puzzle[1] = 7;
    puzzle[2] = 4;
    puzzle[3] = 2;
    puzzle[4] = 6;
    puzzle[5] = 1;
    puzzle[6] = 5;
    puzzle[7] = 3;
    puzzle[8] = 0;
    n.setPuzzle(puzzle);

    Puzzle  p(3, '0');
    EXPECT_NO_THROW(p.controlSolvability(n));

    puzzle[0] = 6;
    puzzle[1] = 3;
    puzzle[2] = 8;
    puzzle[3] = 7;
    puzzle[4] = 4;
    puzzle[5] = 1;
    puzzle[6] = 5;
    puzzle[7] = 2;
    puzzle[8] = 0;
    n.setPuzzle(puzzle);

    EXPECT_NO_THROW(p.controlSolvability(n));

    puzzle[0] = 2;
    puzzle[1] = 6;
    puzzle[2] = 3;
    puzzle[3] = 4;
    puzzle[4] = 7;
    puzzle[5] = 1;
    puzzle[6] = 5;
    puzzle[7] = 8;
    puzzle[8] = 0;
    n.setPuzzle(puzzle);

    EXPECT_NO_THROW(p.controlSolvability(n));
}

TEST(controlSolvability, ValidPuzzles4){
    Node n(4);
    std::vector<int> puzzle(4*4);
    puzzle[0] = 6;
    puzzle[1] = 15;
    puzzle[2] = 4;
    puzzle[3] = 3;
    puzzle[4] = 2;
    puzzle[5] = 10;
    puzzle[6] = 9;
    puzzle[7] = 13;
    puzzle[8] = 11;
    puzzle[9] = 0;
    puzzle[10] = 1;
    puzzle[11] = 5;
    puzzle[12] = 7;
    puzzle[13] = 8;
    puzzle[14] = 12;
    puzzle[15] = 14;
    n.setPuzzle(puzzle);

    Puzzle  p(4, '0');
    EXPECT_NO_THROW(p.controlSolvability(n));

    puzzle[0] = 9;
    puzzle[1] = 5;
    puzzle[2] = 14;
    puzzle[3] = 13;
    puzzle[4] = 4;
    puzzle[5] = 3;
    puzzle[6] = 1;
    puzzle[7] = 2;
    puzzle[8] = 7;
    puzzle[9] = 6;
    puzzle[10] = 15;
    puzzle[11] = 0;
    puzzle[12] = 12;
    puzzle[13] = 11;
    puzzle[14] = 10;
    puzzle[15] = 8;
    n.setPuzzle(puzzle);

    EXPECT_NO_THROW(p.controlSolvability(n));

    puzzle[0] = 8;
    puzzle[1] = 12;
    puzzle[2] = 14;
    puzzle[3] = 9;
    puzzle[4] = 0;
    puzzle[5] = 2;
    puzzle[6] = 1;
    puzzle[7] = 15;
    puzzle[8] = 13;
    puzzle[9] = 5;
    puzzle[10] = 7;
    puzzle[11] = 11;
    puzzle[12] = 10;
    puzzle[13] = 4;
    puzzle[14] = 3;
    puzzle[15] = 6;
    n.setPuzzle(puzzle);

    EXPECT_NO_THROW(p.controlSolvability(n));
}

TEST(controlSolvability, ValidPuzzles5){
    Node n(5);
    std::vector<int> puzzle(5*5);
    puzzle[0] = 17;
    puzzle[1] = 22;
    puzzle[2] = 21;
    puzzle[3] = 18;
    puzzle[4] = 7;
    puzzle[5] = 6;
    puzzle[6] = 3;
    puzzle[7] = 4;
    puzzle[8] = 19;
    puzzle[9] = 12;
    puzzle[10] = 24;
    puzzle[11] = 23;
    puzzle[12] = 11;
    puzzle[13] = 1;
    puzzle[14] = 13;
    puzzle[15] = 10;
    puzzle[16] = 8;
    puzzle[17] = 20;
    puzzle[18] = 15;
    puzzle[19] = 16;
    puzzle[20] = 0;
    puzzle[21] = 2;
    puzzle[22] = 14;
    puzzle[23] = 5;
    puzzle[24] = 9;
    n.setPuzzle(puzzle);

    Puzzle  p(5, '0');
    EXPECT_NO_THROW(p.controlSolvability(n));

    puzzle[0] = 7;
    puzzle[1] = 16;
    puzzle[2] = 0;
    puzzle[3] = 9;
    puzzle[4] = 8;
    puzzle[5] = 10;
    puzzle[6] = 2;
    puzzle[7] = 23;
    puzzle[8] = 14;
    puzzle[9] = 19;
    puzzle[10] = 24;
    puzzle[11] = 20;
    puzzle[12] = 4;
    puzzle[13] = 3;
    puzzle[14] = 21;
    puzzle[15] = 17;
    puzzle[16] = 13;
    puzzle[17] = 5;
    puzzle[18] = 18;
    puzzle[19] = 1;
    puzzle[20] = 15;
    puzzle[21] = 6;
    puzzle[22] = 12;
    puzzle[23] = 22;
    puzzle[24] = 11;
    n.setPuzzle(puzzle);

    EXPECT_NO_THROW(p.controlSolvability(n));

    puzzle[0] = 17;
    puzzle[1] = 19;
    puzzle[2] = 8;
    puzzle[3] = 13;
    puzzle[4] = 21;
    puzzle[5] = 12;
    puzzle[6] = 10;
    puzzle[7] = 7;
    puzzle[8] = 22;
    puzzle[9] = 2;
    puzzle[10] = 3;
    puzzle[11] = 20;
    puzzle[12] = 15;
    puzzle[13] = 1;
    puzzle[14] = 11;
    puzzle[15] = 23;
    puzzle[16] = 0;
    puzzle[17] = 9;
    puzzle[18] = 18;
    puzzle[19] = 6;
    puzzle[20] = 5;
    puzzle[21] = 16;
    puzzle[22] = 14;
    puzzle[23] = 24;
    puzzle[24] = 4;
    n.setPuzzle(puzzle);

    EXPECT_NO_THROW(p.controlSolvability(n));
}