# ABOUT THIS PROGRAM #

This application solves a multiple regression problems using solely the std::vector container. To demonstrate it's usage, a solution to a problem found on [hackerrank.com](https://www.hackerrank.com/challenges/predicting-house-prices) has been implemented.  

The problem this application solves, can be generally described as follows: 

There is a set of independent features X, that produce result Y. Given another set of features, estimate the result for them. 
As the task description on [hackerrank.com](https://www.hackerrank.com/challenges/predicting-house-prices) states, a multiple linear regression should be to used solve it. 

A matrix formulation of the multiple regression model can written as: 

**Y = X * B + error** 

What we need to be able to estimate result given some features is a vector B, containing the estimates of the regressions' function parameters.

**B = (X' * X)^-1 * X'*Y**

Where X' is a transposed X.

Our application needs to implement following three matrix operations:

1) Matrix transposition

2) Matrix multiplication

3) Matrix inversion

The first two operations are trivial. The third operation – matrix inversion makes this problem slightly trickier.

I've implemented two popular matrix inversion algorithms:

1) Brute force solution using adjoint method (see AdjointMatrixInverter.h).

   * This method, although easy to implement, fails on this problem, due to matrix size of up to 10 features, which is too heavy for this method.

2) [Cholesky decomposition](https://en.wikipedia.org/wiki/Cholesky_decomposition) (see DecompositionInverter.h)

   * In this particular problem, a matrix to be inverted is equal to X' * X. The result of this multiplication will be a symmetric matrix.  Moreover assuming that X is a nonsingular matrix, the result is also positive definite. In such case, the numerical stable, iterative Cholesky decomposition method can be used to decompose matrix. Furthermore by using the forward decomposition, the inverse matrix (X'*X)^-1 can be determined.