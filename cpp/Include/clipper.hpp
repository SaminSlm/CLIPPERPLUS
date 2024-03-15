#pragma once

#include<vector>
#include<set>
#include <iostream>
#include<Eigen/Dense>
#include <cmath>

using Eigen::MatrixXd;
using Eigen::VectorXd;

VectorXd clipper(const MatrixXd& A, const VectorXd& u0);