//#include <iostream>
//#include <string>
//
//void printResult(double a, double b,std::string operation)
//{
//	if (operation == "+")
//		std::cout << a << operation << b << " is " << a + b << std::endl;
//	else if (operation == "-")
//		std::cout << a << operation << b << " is " << a - b << std::endl;
//	else if (operation == "*")
//		std::cout << a << operation << b << " is " << a * b << std::endl;
//	else if (operation == "/")
//		std::cout << a << operation << b << " is " << a / b << std::endl;
//	else
//		std::cout << "Operation is not valid";
//}
//
//void getDoubles(double& a, double& b)
//{
//	std::cout << "Enter a double value ";
//	std::cin >> a;
//	std::cout << "Enter a double value ";
//	std::cin >> b;
//}
//
//void getOperation(std::string &operation)
//{
//	std::cout << "Enter one of the following: +, -, *, or /: ";
//	std::cin >> operation;
//}
//int main()
//{
//	double a, b;
//	std::string operation;
//	getDoubles(a, b);
//	getOperation(operation);
//	printResult(a, b, operation);
//}

#include <iostream>

void getDistance(double& distance)
{
	std::cout << "Enter the height from which the ball is dropped";
	std::cin >> distance;
}

void getTime(double& time, double distance,double constant)
{
	time = sqrt(2 * distance / constant);
}
//
//void printResult(double constant, double distance, double time)
//{
//	for (int a = time; a > 0.f; a--)
//	{
//		std::cout << "At " << a << "seconds, the ball is at height: " << (constant * pow(a, 2)) / 2 << std::endl;
//	}
//}
//
//int main()
//{
//	constexpr double gc = 9.8;
//	double distance = 0;
//	double time;
//	getDistance(distance);
//	getTime(time, distance, gc);
//	printResult(gc, distance, time);
//	return 0;
//}