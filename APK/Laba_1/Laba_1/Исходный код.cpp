#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#include<ctime>
#include<conio.h>
#include<iostream>
using namespace std;

int main(){
	unsigned int start;
	unsigned int finish;
	unsigned int result;
	double x = 0;
	int a = 0, b = 0, d = 0;
	int cont = 0;
	double res = 0, res1 = 0;
	while (1){
		cout << "Entert three parameters: " << endl;
		cin >> a;
		while (!cin.good()){
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Reenter first parameter: " << endl;
			cin >> a;
		}
		cin >> b;
		while (!cin.good()){
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Reenter Second parameter: " << endl;
			cin >> b;
		}
		cin >> d;
		while (!cin.good()){
			cin.clear();
			cin.ignore(255, '\n');
			cout << "Reenter third parameter: " << endl;
			cin >> d;
		}
		start = clock();
		for (x = a; x < b; x += d){
			res = (x - ((x*x)*cos(x)));
		}
		finish = clock();
		result = finish - start;
		printf("%lf\n%d\n", res, result);
		start = clock();
		_asm finit
		for (x = a; x < b; x += d){			
			_asm{
				FLD x
				FLD x
				FCOS
				FLD x
				FLD x
				FMUL
				FMUL
				FSUB

				FSTP res1
			}			
		}
		_asm fwait
		finish = clock();
		result = finish - start;
		printf("%lf\n%d\n", res1, result);
		cout << "If you want to continue, press 1: " << endl;
		cin >> cont;
		if (cont != 1)
			break;
	}
	_getch();
	return 0;
}
