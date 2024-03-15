#pragma once

#include <iostream>
#include <algorithm>
#include<vector>

bool isClique(const std::vector<std::vector<int>>& adjacencyMatrix, const std::vector<int>& C_prime, int sj) ;

std::vector<int> PMC(const std::vector<std::vector<int>>& adjacency_matrix, const std::vector<int>& c_n);