#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <map>

using matrix = std::vector<std::vector<std::size_t>>;
auto constexpr inf = std::numeric_limits<unsigned int>::max();

template <typename storage, typename element>
bool in(const storage& st, const element& elem)
{
    return std::find(st.begin(), st.end(), elem) != st.end();
}

template <typename storage, typename element, typename... elements>
bool in(const storage& st, const element& elem, const elements... elems)
{
    return in(st, elem) and in(st, elems...);
}

matrix mt = {
    {0,6,0,0,3,0,0,4},
    {6,0,1,7,0,0,3,0},
    {0,1,0,0,0,0,0,0},
    {0,7,0,0,1,0,0,3},
    {3,0,0,1,0,1,0,0},
    {0,0,0,0,1,0,11,3},
    {0,3,0,0,0,11,0,1},
    {4,0,0,3,0,3,1,0}
};

int main(int, char**)
{
    auto origin_matrix = mt;

    for (std::size_t a = 0; a < mt.size(); ++a)
    {
        for (std::size_t b = 0; b < mt.size(); ++b)
        {
            if (not mt[a][b])
            {
                mt[a][b] = inf;
            }
        }
    }
    for (std::size_t a = 0; a < mt.size(); ++a)
    {
        for (std::size_t b = 0; b < mt.size(); ++b)
        {
            for (std::size_t c = 0; c < mt.size(); ++c)
            {
                mt[b][c] = std::min(mt[b][c], mt[b][a] + mt[a][c]);
            }
        }
    }
    for (std::size_t i = 0; i < mt.size(); ++i)
    {
        for (std::size_t k = 0; k < mt.size(); ++k)
        {
            if (i == k)
            {
                continue;
            }
            std::cout << "Shortest path from vertex " << i + 1 << " to vertex " << k + 1 << ": ";
            std::size_t distanceToSecondVertex = mt[i][k];
            std::vector<std::size_t> path{ i, k };
            bool isLinked = false;
            while (not isLinked)
            {
                isLinked = true;
                auto lastElement = path[path.size() - 1];
                auto penUltimate = path[path.size() - 2];
                for (std::size_t currentElemIdx = 0; currentElemIdx < mt.size(); ++currentElemIdx)
                {
                    if (mt[i][currentElemIdx] + mt[k][currentElemIdx] == distanceToSecondVertex)
                    {
                        if (not origin_matrix[path[path.size() - 2]][currentElemIdx]) {
                            continue;
                        }
                        if (not in(path, currentElemIdx))
                        {
                            path.emplace(path.end() - 1, currentElemIdx);
                            isLinked = true;
                            for (std::size_t currentVertexIdx = 0; currentVertexIdx < path.size(); ++currentVertexIdx)
                            {
                                if (currentVertexIdx + 1 == path.size())
                                {
                                    break;
                                }
                                if (not origin_matrix[path[currentVertexIdx]][path[currentVertexIdx + 1]])
                                {
                                    isLinked = false;
                                }
                            }
                            if (isLinked) {
                                break;
                            }
                        }
                    }
                }
            }
            for (const auto& vertex : path)
            {
                std::cout << vertex + 1 << " ";
            }
            std::cout << '\n';
        }
    }
}
