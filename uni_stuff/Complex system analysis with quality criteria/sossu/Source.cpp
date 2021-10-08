#include <iostream>
#include <ctime>
#include <windows.h>
#include <numeric>
#include <random>
using namespace std;

//Характеристики системы

double yj1min = 0.4;
double yj1max = 0.9;

double yj2min = 0.1;
double yj2max = 0.3;

//Границы области адекватности

double y1min = 0.5;
double y1max = 0.8;

double y2min = 0.1;
double y2max = 0.4;

//Оптимальные значения характеристик

double y1opt = 0.6;
double y2opt = 0.2;


double random(double min, double max)
{
	random_device rd;
	mt19937 gen{ rd() };
	uniform_real_distribution<> dis(min, max);
	return dis(rd);
}

int main(int argc, char* argv[])
{

	while (true) {

		cout.width(10);
		cout.precision(4);
		srand(time(0));

		float a[10][2];

		for (int i = 0; i < 10; i++) {
			//Генерация дести случайных систем
			a[i][0] = random(yj1min, yj1max);
			a[i][1] = random(yj2min, yj2max);
		}

		int k = 1;


		cout << endl << "Sys.\\ Char.    |      y1     |      y2      |" << endl;

		for (int i = 0; i < 10; i++) {
			//Вывод случайно сгенерированных систем
			cout << "System " << k << "    ";
			k++;
				cout <<"(" <<a[i][0] << "," << a[i][1]<<")"<<endl ;
		}

		cout << endl << "Applicable systems" << endl << endl;

		for (int i = 0; i < 10; i++) {
			//Проверка на пригодную систему 
			if ((a[i][0] > y1min && a[i][0] < y1max) && (a[i][1] > y2min && a[i][1] < y2max)) {

				cout << "System "<<i+1<<" ";
				cout << "(" << a[i][0] << "," << a[i][1] << ")" << endl;

			}
		}

		cout << endl << "Optimal System:" << endl << endl;

		for (int i = 0; i < 10; i++) {
			//Проверка на оптимальную систему
			if (((a[i][0] > y1opt - 0.05 && a[i][0] < y1opt + 0.05) || (a[i][1] > y2opt - 0.05 && a[i][1] < y2opt + 0.05)) &&
				(a[i][0] > y1min && a[i][0] < y1max) && (a[i][1] > y2min && a[i][1] < y2max)) {

				cout << "System " << i + 1 << " ";
				cout << "(" << a[i][0] << "," << a[i][1] << ")" << endl;
			}
		}

		cout << endl << "Excellent system:" << endl << endl;

		for (int i = 0; i < 10; i++) {
			//Проверка на превосходную систему
			if (((a[i][0] > y1opt - 0.05 && a[i][0] < y1opt + 0.05) && (a[i][1] > y2opt - 0.05 && a[i][1] < y2opt + 0.05)) &&
				(a[i][0] > y1min && a[i][0] < y1max) && (a[i][1] > y2min && a[i][1] < y2max)) {

				cout << "System " << i + 1 << " ";
				cout << "(" << a[i][0] << "," << a[i][1] << ")" << endl;
			}
		}
		cout << endl;
		system("pause");
	}
	return 0;
}
