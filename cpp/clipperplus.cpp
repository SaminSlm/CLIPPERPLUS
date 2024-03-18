
// This C++ program takes the adjacency matrix of a graph and the core numbers of each vertex.
// It identifies the vertices that form a maximal clique in the graph and prints them using cout.

#include"clipper.hpp"
#include"pmc.hpp"
#include"set"



int main(){
  std::vector<std::vector<int>> A;
     
 A ={{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0},
     {1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
     {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
     {1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
     {0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1},
     {1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1},
     {0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
     {1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1},
     {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
     {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1},
     {0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0}}; // adjacency matrix
  int n = A.size();
  std::vector<int> k; // core numbers
  k = {4,4,4,4,4,4,4,4,4,4,4};
   
    std::vector<int> C;
    C = PMC(A, k) ;

    std::vector<int> L;
   
    std::cout << std::endl;
    for (int i = 0; i < n; ++i) {
        if (k[i] >= C.size()) {
            L.push_back(i);
        }}
        
        if(!L.empty()){
      
    }
      MatrixXd pruned_A(L.size(),L.size());
      



    for (int i = 0; i < L.size(); ++i) {
        for (int j = 0; j < L.size(); ++j) {
             pruned_A(i, j) = A[L[i]][L[j]];
        }
    }
VectorXd u0 = VectorXd::Ones(L.size());

std::set<int> C_set(C.begin(), C.end());

for (int i = 0; i < L.size();++i){
    if(C_set.count(L[i])> 0){
       u0[i] = 0;
    }
 }
  
  std::vector<int> C_prime; 

   VectorXd u(pruned_A.rows());
   
   u = clipper (pruned_A , u0);
   
    for (int j = 0; j < u.size(); ++j) {
       if(u[j] > 0 ){C_prime.push_back(L[j]);}

  }
if (C_prime.size() >= C.size() ){
  C = C_prime;
}


for (auto ci : C){
  std::cout << ci << " ";
}
std::cout << std::endl;}