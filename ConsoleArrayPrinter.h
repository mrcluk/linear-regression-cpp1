/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include "ArrayPrinter.h"
namespace regression {
	template<typename Ty>
	class ConsoleArrayPrinter : public ArrayPrinter<Ty> {
	public:
		void virtual print_matrix(matrix_t<Ty> matrix) const {
			if (matrix.size() == 0) {
				std::cout << "Matrix is empty." << std::endl;
			}
			else {
				for (auto i = matrix.cbegin(); i != matrix.cend(); ++i) {
					for (auto j = (*i).cbegin(); j != (*i).cend(); ++j) {
						std::cout << (*j) << "\t";
					}
					std::cout << std::endl;
				}
			}
		}
	};
}