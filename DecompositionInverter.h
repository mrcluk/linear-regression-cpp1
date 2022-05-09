/**
Copyright (C) Lukasz Marzec. All rights reserved.
Licensed under the MIT license. See LICENSE.txt file in the project root for full license information.

*/
#pragma once
#include <functional>
#include <cmath>
#include "MatrixInverter.h"
#include "MatrixTransposer.h"

/**
 * https://en.wikipedia.org/wiki/Cholesky_decomposition
 */
namespace regression {
	/// <summary>
	/// Matrix inversion using the Cholesky decomposition.
	/// </summary>
	template <typename Ty>
	class DecompositionInverter final : public MatrixInverter<Ty> {
	public:
		DecompositionInverter() = default;
		virtual ~DecompositionInverter() = default;

		/// <summary>
		/// Inverts matrix using the Cholesky decomposition.
		/// </summary>
		/// <param name="data">Matrix to be inverted.</param>
		/// <returns>Inverted matrix provided by the data parameter.</returns>		
		matrix_t<Ty> virtual invert_matrix(matrix_t<Ty>);
	private:
		void decompose();
		matrix_t<Ty> get_inverted_L();

		matrix_t<Ty> data;
	};

	template <typename Ty>
	matrix_t<Ty> DecompositionInverter<Ty>::invert_matrix(matrix_t<Ty> data) {
		this->data = data;
		//
		// A^-1 = (L^-1)T * (L^-1)
		//
		// decompose matrix stored in this->data to a L-matrix
		decompose();

		// 
		// inverse using forward decomposition method
		// AX = I
		//
		matrix_t<Ty> invertedL = get_inverted_L();
		MatrixTransposer<Ty> transposer(invertedL);
		matrix_t<Ty> transposed_invL = transposer.get_transposed();

		auto inverted = transposed_invL * invertedL;

		return inverted;
	}

	template <typename Ty>
	void DecompositionInverter<Ty>::decompose() {
		auto size = data.size();
		auto square_sum =
			[&](const row_t<Ty>& row, unsigned row_index) {
			Ty sum = 0;
			int sum_to_n = row_index;
			for (auto k = 0; k < sum_to_n; ++k) {
				sum += row[k] * row[k];
			}

			return sum;
		};

		auto square_ij_sum =
			[&](const matrix_t<Ty>& smatrix, unsigned row_index, unsigned col_index) {
			Ty sum = 0;
			int sum_to_n = col_index;
			for (auto k = 0; k < sum_to_n; ++k) {
				sum += smatrix[row_index][k] * smatrix[col_index][k];
			}
			return sum;
		};


		for (int w = 0; w < size; ++w) {
			for (int c = 0; c < size; ++c) {
				if (w == c) {
					this->data[w][c] = sqrtf(this->data[w][c] - square_sum(this->data[w], w));
				}
				else if (w > c) {
					this->data[w][c] = (Ty)1 / this->data[c][c] * (this->data[w][c] - square_ij_sum(this->data, w, c));
				}
				else {
					this->data[w][c] = 0;
				}
			}
		}
	}

	template <typename Ty>
	matrix_t<Ty> DecompositionInverter<Ty>::get_inverted_L() {
		auto result(this->data);

		auto I(this->data);
		for (auto r = 0; r < I.size(); ++r) {
			for (auto c = 0; c < I[r].size(); ++c) {
				I[r][c] = (Ty)(r == c ? 1 : 0);
			}
		}

		auto square_sum = [&](const auto& L_matrix, auto m, auto c) {
			Ty sum = 0;
			for (auto i = 0; i < m; ++i) {
				sum += L_matrix[m][i] * result[i][c];
			}
			return sum;
		};

		auto matrix_size = this->data.size();

		for (auto c = 0; c < matrix_size; ++c) {
			for (auto r = 0; r < matrix_size; ++r) {
				if (r < c) {
					result[r][c] = 0;
				}
				else {
					result[r][c] = (Ty)(I[r][c] - square_sum(this->data, r, c)) / this->data[r][r];
				}
			}
		}

		return result;
	}
}