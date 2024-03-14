#include<vector>
#include <iostream>
#include<Eigen/Dense>
#include <cmath>

using Eigen::MatrixXd;
using Eigen::VectorXd;

std::vector<int> clipper(const MatrixXd& A, const std::vector<double>& u0);