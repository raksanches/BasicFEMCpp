#ifndef DENSE_EIGEN
#define DENSE_EIGEN

#include <cmath>
#include <stdio.h>
#include <vector>
#include <functional>
#include <Eigen/Dense>

using namespace Eigen;

typedef Eigen::MatrixXd MatDouble;
typedef Eigen::MatrixXi MatInt;

typedef Eigen::Matrix<int64_t, Dynamic, 1> VecInt;
typedef Eigen::VectorXd VecDouble;

#endif