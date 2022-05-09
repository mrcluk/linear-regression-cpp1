// compile with: /EHsc /W4 /MTd
/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#include <iostream>
#include "HousePriceEstimator.h"


int main(int argc, char** argv)
{
	using namespace regression;

	try
	{
		HousePriceEstimator estimator;
		estimator.estimate(HousePriceEstimator::Cholesky);
	}
	catch (const std::exception& e) 
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
