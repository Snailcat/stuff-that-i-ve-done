#include <iostream>
#include <string>

//struct Ad {
//	int timesShown{};
//	int percentage{};
//	int money{};
//};
//
//void printStuff(Ad ad)
//{
//	int result;
//	std::cout << ad.timesShown << "\n" <<  ad.percentage << "\n" << ad.timesShown << std::endl;
//	result = ad.money + ad.percentage + ad.timesShown;
//	std::cout << result;
//}
//
//int main()
//{
//	Ad ad { 10,5,10 };
//	printStuff(ad);
//	return 0;
//}

struct Fraction {
	int numerator;;
	int denumerator;
};

Fraction getFraction()
{
	Fraction temp;
	std::cout << "enter numerator: ";
	std::cin >> temp.numerator;
	std::cout << "\n" << "enter denumerator: ";
	std::cin >> temp.denumerator;
	return temp;
}

int multiply(Fraction fraction)
{
	return fraction.denumerator * fraction.numerator;
}

int main()
{
	Fraction fraction{ getFraction() };
	std::cout << multiply(fraction) << std::endl;
	return 0;
}