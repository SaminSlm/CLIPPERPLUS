#include "pmc.hpp"
#include <vector>
#include <algorithm>


bool compareCoreNumbers(const int& a, const int& b) {
    return a > b; // Sort in descending order
}
std::vector<int> sortedbycorenumber(std::vector<int> c_n){
    std::vector<int> sorted_indices(c_n.size());
    for (size_t i{}; i < c_n.size(); ++i) {
        sorted_indices[i] = i; // Initialize with original indices
    }

    // Sort the indices based on core numbers
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&](int a, int b) {
        return compareCoreNumbers(c_n[a], c_n[b]);
    });
    

    // Output the sorted vertices
    std::vector<int> sorted_vertices(c_n.size());
    for (size_t i{}; i < sorted_indices.size(); ++i) {
        sorted_vertices[i] = sorted_indices[i];
    }
    return sorted_vertices;
}


std::vector<int> pmc(const std::vector<std::vector<int>>& adjacency_matrix, const std::vector<int>& c_n){

int n = adjacency_matrix.size();
std::vector<int> C;
std::vector<int> S;

int cmax{};
 
 std::vector<int> sorted_vertices = sortedbycorenumber(c_n);

    // Loop over sorted vertices
    for(size_t i{}; i < sorted_vertices.size(); ++i){
       
        int v = sorted_vertices[i];

        if (c_n[v] >= cmax){
             for (size_t j{}; j < adjacency_matrix.size(); ++j) {
                if (adjacency_matrix[v][j] == 1 && c_n[j] >= cmax) {
                    S.push_back(j);
                }
                 sort(S.begin(), S.end(), [&](int a, int b) {
                return c_n[a] >= c_n[b];
            });
            std::vector<int> C_prime;
            // Loop through vertices in sorted S
            for (int j = 0; j < S.size(); ++j) {
                bool isClique = true;
                for (int ci : C_prime) {
                    if (adjacency_matrix[ci][S[j]] == 1) {
                          C_prime.push_back(S[j]);
                        
                    }
                    
           if (C_prime.size() > cmax) {
                C = C_prime;
                cmax = C_prime.size();
            }
        }
    }
    return C;
        }
    } 
        }
        


    }
