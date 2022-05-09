/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include <functional>
#include "MatrixInverter.h"
#include "Types.h"
#include "MatrixTransposer.h"

namespace regression {
	/// <summary>
	/// Matrix inversion using the adjoint method.
	/// </summary>
	template <typename Ty>
	class AdjointMatrixInverter final : public MatrixInverter<Ty> {
	public:
		AdjointMatrixInverter() = default;
		virtual ~AdjointMatrixInverter() = default;

		/// <summary>
		/// Inverts matrix using the adjoint method.
		/// </summary>
		/// <param name="data">Matrix to be inverted.</param>
		/// <returns>Inverted matrix provided by the data parameter.</returns>
		matrix_t<Ty> virtual invert_matrix(matrix_t<Ty> data);
	private:
		Ty determinant(matrix_t<Ty>&) const;
		matrix_t<Ty> submatrix(matrix_t<Ty>, int, int) const;

		matrix_t<Ty> cofactor_matrix(matrix_t<Ty>) const;

		std::function<int(unsigned, unsigned)> element_sign =
			[](unsigned row_index, unsigned col_index) {
			// returns (-1)^(row_index + col_index)
			// indexes are 0-based, add 2 to converts them to 1-based	
			return ((row_index + col_index + 2) % 2 == 0 ? 1 : -1);
		};
	};

	template <typename Ty>
	matrix_t<Ty> AdjointMatrixInverter<Ty>::invert_matrix(matrix_t<Ty> data) {
		auto det = determinant(data);
		auto cofactorMatrix = cofactor_matrix(data);

		matrix_t<Ty> ivertedMatrix;
		if (det != 0) {
			MatrixTransposer<Ty> transposer(cofactorMatrix);
			auto adjointMatrix = transposer.get_transposed();
			Ty det_inv = (Ty)(1 / det);
			ivertedMatrix = det_inv * adjointMatrix;
		}
		else {
			std::cout << "Determinant == 0" << std::endl;
		}
		return ivertedMatrix;
	}

	template <typename Ty>
	Ty AdjointMatrixInverter<Ty>::determinant(matrix_t<Ty>& matrix) const {
		if (matrix.size() == 2) {
			return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
		}
		else {
			Ty sum = 0;
			const unsigned ROW_INDEX = 0;
			for (std::size_t i = 0; i < matrix[ROW_INDEX].size(); ++i) {
				sum += matrix[0][i] * element_sign(ROW_INDEX, i) * determinant(submatrix(matrix, 0, i));
			}
			return sum;
		}
	}

	template <typename Ty>
	matrix_t<Ty> AdjointMatrixInverter<Ty>::submatrix(matrix_t<Ty> matrix, int r, int c) const {
		const std::size_t matrix_size = matrix.size();
		const std::size_t reduced_size = matrix_size - 1;
		matrix_t<Ty> result;
		result.reserve(reduced_size);

		for (std::size_t i = 0; i < matrix_size; ++i) {
			if (i != r) {
				row_t<Ty> row;
				row.reserve(reduced_size);

				for (std::size_t j = 0; j < matrix_size; ++j) {
					if (j != c) {
						row.push_back(matrix[i][j]);
					}
				}
				result.push_back(row);
			}
		}

		return result;
	}

	template <typename Ty>
	matrix_t<Ty> AdjointMatrixInverter<Ty>::cofactor_matrix(matrix_t<Ty> matrix) const {
		const std::size_t matrix_size = matrix.size();
		matrix_t<Ty> result;
		result.reserve(matrix_size);

		for (auto row_index = 0; row_index < matrix_size; ++row_index) {
			row_t<Ty> row;
			row.reserve(matrix_size);
			for (auto col_index = 0; col_index < matrix_size; ++col_index) {
				row.push_back(element_sign(row_index, col_index) * determinant(submatrix(matrix, row_index, col_index)));
			}
			result.push_back(row);
		}

		return result;
	}
}