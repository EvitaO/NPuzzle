#include "utils.hpp"

int     calculateInversions(std::vector<int> vec, int size){
    int inversions = 0;
    for (int i = 0; i < vec.size(); i++){
        int tmp = 0;
        for (int x = i + 1; x < vec.size(); x++){
            if ((vec[i] > vec[x] && vec[x] != 0) || (vec[i] == 0))
                tmp++;
            if (tmp == vec[i] - 1 && vec[i] != 0)
                break;
        }
        inversions += tmp;
    }
    return inversions;
}