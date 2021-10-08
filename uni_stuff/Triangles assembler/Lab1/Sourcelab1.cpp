#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <cmath>

class Triangle {
public:
    Triangle(int &a, int &b, int &c);

    float getArea();
private:
    float a, b, c;
};

Triangle::Triangle(int &a, int &b, int &c) : a(a), b(b), c(c)
{

}

float  Triangle::getArea() {
    float p = (a + b + c) / 2;
    float s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}

bool operator==(Triangle& lhs, Triangle& rhs)
{
    return lhs.getArea() == rhs.getArea();
}

int main() {
    std::vector<int> sides{ 4, 7, 3, 9 };
    std::vector<Triangle> triangles;
    while (std::next_permutation(sides.begin(), sides.end()))
        if ((sides[0] < sides[1] + sides[2]) and (sides[1]<sides[0]+sides[2]) and (sides[2]<sides[1]+sides[0]))
            triangles.emplace_back(sides[0], sides[1], sides[2]);
    std::sort(triangles.begin(), triangles.end(), [](Triangle a, Triangle b) {return a.getArea() > b.getArea(); });
    triangles.erase(std::unique(triangles.begin(), triangles.end()),triangles.end());
    for (auto& triangle : triangles)
        std::cout << triangle.getArea() << std::endl;
    return 0;
}
