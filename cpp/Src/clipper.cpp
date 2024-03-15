#include"clipper.hpp"



VectorXd clipper(const MatrixXd& A, const VectorXd& u0)
{
    int n = A.rows();
    MatrixXd M = MatrixXd::Identity(n,n) + A;
    
    MatrixXd M_C  = MatrixXd::Ones(n,n) - M ;
    MatrixXd Md (n,n);

double tolu = 1e-8; 
double tolF = 1e-8;  
double sigma = 0.01;
double beta = 0.5;  
int maxlsiters = 99; 
int maxiniters = 200; 
int maxoliters = 1000; 
double epsilon = 1e-9; 
VectorXd deltau(n);
double deltaF;
double d = 2;
double deltad = 0.5;

VectorXd u(n), Mu(n), gradF(n), gradFop(n), unew(n), mcu(n),gradfopnew(n);
VectorXd mu0(n);
mu0 = M * u0;
u = mu0 / mu0.norm();
Md = M - d * M_C; 


int i = 0;
bool outerloop = true;

while(outerloop && i < maxoliters){

 double F = u.transpose() * Md * u;
 double Fnew{};
 double alpha = 1;
 int j = 0;
 bool innerloop = true;
  while(innerloop && j < maxiniters){
     
        gradF = 2 * Md * u; // gradient
        
        gradFop = gradF - gradF.dot(u) * u;; 
         int k = 1;
         bool armijo = false;
         while (!armijo && k < maxlsiters) {
           
         
            unew = u + alpha * gradFop;    // gradient step
            unew = unew/unew.norm(); 
            unew = unew.array().max(0); // Apply element-wise maximum with 
     
            Fnew = unew.transpose() * Md * unew;     //new objective value
            
            gradfopnew = 2 * Md *unew - unew * unew.transpose() * 2 * Md * unew;

             deltau = u - unew;
             deltaF = Fnew - F;
            VectorXd armijo_step = sigma * gradFop * u.transpose() * deltau;
            double norm_armijo_step = armijo_step.norm();
             if (deltaF < norm_armijo_step){
                alpha = alpha * beta;
             }
             else{
                alpha = alpha / sqrt(beta);
                armijo = true;
             }
             k++;
            
         }
         double norm_deltau = deltau.norm();
           if ((norm_deltau < tolu) || (std::abs(deltaF) < tolF)){
                innerloop = false;
          }
         F = Fnew;
         u = unew;
         j++;
  }
     std::set<double> uniqueElements;

    //  Insert elements of the vector into the set (sets automatically store only unique elements)
    for (int i = 0; i < u.size(); ++i) {
        uniqueElements.insert(u[i]);
      }
    if (uniqueElements.size() == 2){
     outerloop = false;
      }
    d = d + deltad;
    Md = M - d * M_C; 

    i++;
}

return u;
   



}