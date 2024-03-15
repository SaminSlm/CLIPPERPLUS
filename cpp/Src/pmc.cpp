#include "pmc.hpp"


bool isClique(const std::vector<std::vector<int>>& adjacencyMatrix, const std::vector<int>& C_prime, int sj) {
    return std::all_of(C_prime.begin(), C_prime.end(), [&](int vertex) {
        return adjacencyMatrix[vertex][sj];
    });
}

std::vector<int> PMC(const std::vector<std::vector<int>>& adjacency_matrix, const std::vector<int>& c_n){

int n = adjacency_matrix.size();
std::vector<int> S{};
std::vector<int> C_prime;
std::vector<int> C{};

std::vector<int> sorted_vertices;

 for (size_t i{}; i < c_n.size(); ++i) {
        sorted_vertices.push_back(i);
    }
sort(sorted_vertices.begin(), sorted_vertices.end(), [&](int a, int b){
     return c_n[a] >= c_n[b];
    });
     

int cmax{};

    // Loop over sorted vertices
    for(size_t i{}; i < sorted_vertices.size(); ++i){
       
        int v = sorted_vertices[i];

        S = {};

        

        if (c_n[v] >= cmax){
             for (size_t j{}; j < adjacency_matrix.size(); ++j) {
                if (adjacency_matrix[v][j] == 1 && c_n[j] >= cmax) {
                    S.push_back(j);
                }}
              
                 sort(S.begin(), S.end(), [&](int a, int b){
                return c_n[a] >= c_n[b];
            });
           

            C_prime = {v};
            
            
            // Loop through vertices in sorted S
            for (size_t k{}; k < S.size(); ++k) {
            
        
                
                

                    if (isClique(adjacency_matrix, C_prime, S[k])) {
                          C_prime.push_back(S[k]);
                        
                    }

                  
           if (C_prime.size() > cmax) {
                C = C_prime;
                cmax = C_prime.size() - 1;
            }
        }
    }
    
        
    }
        
        
         return C; 
    }
