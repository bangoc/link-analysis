#include <iostream>
#include <Eigen/Dense>
using Eigen::MatrixXd;
int main()
{
  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);

  MatrixXd n(1, 2);
  n << 0.5, 0.5;
  std::cout << n << std::endl;
  std::cout << m << std::endl;
  std::cout << n * m << std::endl;

  MatrixXd z(10, 10);
  z << MatrixXd::Zero(10, 10);
  std::cout << z << std::endl;
}