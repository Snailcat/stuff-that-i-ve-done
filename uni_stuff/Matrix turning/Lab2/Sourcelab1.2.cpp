#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <utility>

void sort(std::vector<int>& column, bool isreversed)
{
	if (isreversed)
		for (int i = 0; i < column.size(); i++)
			std::sort(column.begin(), column.end(), [](int a, int b) {return a > b; });
	if (not isreversed)
		for (int i = 0; i < column.size(); i++)
			std::sort(column.begin(), column.end());
}

void rollByPiHalfClockwise(std::vector<std::vector<int>> &matrix)
{
	for (int i = 0; i < matrix.size(); i++)
		for (int j = i; j < matrix.size(); j++)
			std::swap(matrix[i][j], matrix[j][i]);
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix.size(); j++)
			std::swap(matrix[i][j], matrix[i][matrix.size() - j - 1]);
}

void rollByPiHalfCClockwise(std::vector<std::vector<int>>& matrix)
{
	for (int i = 0; i < matrix.size(); i++)
		for (int j = i; j < matrix.size(); j++)
			std::swap(matrix[i][j], matrix[j][i]);
	for (int i = 0; i < matrix.size(); i++)
		for (int j = 0; j < matrix.size(); j++)
			std::swap(matrix[i][matrix.size()-i-1], matrix[i][j]);
}

int main() {
	int N;
	std::cout << "Enter matrix's size" << std::endl;
	std::cin >> N;
	std::vector <std::vector<int>> matrix(N + 15);
	for (auto& column : matrix)
		column.resize(N + 15);

	std::random_device rd;
	std::mt19937 end(rd());
	std::uniform_int_distribution<> distr(-N - 15, N + 15);
	for (int i = 0; i < N + 15; i++)
		for (int j = 0; j < N + 15; j++)
			matrix[i][j] = distr(end);
	
	rollByPiHalfClockwise(matrix);
	for (int i = 0; i < N + 15; i++)
	{
		if (i bitand 1)
			sort(matrix[i], true);
		else
			sort(matrix[i], false);
	}
	rollByPiHalfCClockwise(matrix);
	for (auto const& row : matrix) {
		for (auto const& elem : row)
			std::cout << elem << "\t";
		std::cout << "\n";
	}
	return 0;
}