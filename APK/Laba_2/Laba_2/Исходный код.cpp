#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string>
using namespace std;

int main(){
	int i, j;
	short cnt;
	short mt1[8][8], mt2[8][8], mt[8][8], mtAsm[8][8], mtMMX[8][8];
	int cl1 = 0, cl2 = 0, cl3 = 0;
	unsigned int start;
	unsigned int finish;
	unsigned int result;
	for (int k = 0; k < 1000000; k++){
		srand(time(NULL));
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				mt1[i][j] = rand() % 100;
				mt2[i][j] = rand() % 100;
			}
		}
		start = clock();
		//C++ solution
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				mt[i][j] = mt1[i][j] + mt2[i][j];
			}
		}
		finish = clock();
		result = finish - start;
		cl1 += result;
		cnt = 64;
		short k = 0;

		//Assembler solution
		start = clock();
		_asm{
			pusha
				xor esi, esi
			loop1 :
			xor cx, cx
				mov ax, mt1[esi]
				mov bx, mt2[esi]
				add ax, bx
				add cx, ax
				mov mtAsm[esi], cx
				add esi, 2
				sub cnt, 1
				jnz loop1
				popa
		}
		finish = clock();
		result = finish - start;
		cl2 += result;
		cnt = 16;

		//MMX solution
		start = clock();
		_asm{
			pusha
				xor esi, esi
			loop2 :
			pxor MM7, MM7
				movq MM0, mt1[esi]
				movq MM1, mt2[esi]
				paddw MM0, MM1
				movq  mtMMX[esi], MM0
				add esi, 8
				sub cnt, 1
				jnz loop2
				emms
				popa
		}
		finish = clock();
		result = finish - start;
		cl3 += result;
	}
	cout << "C solution answer: " << endl;
	cout << "Time: "<< cl1 << endl;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			cout << mt[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "Assembler solution answer: " << endl;
	cout << "Time: " << cl2 << endl;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			cout << mtAsm[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "MMX solution answer: " << endl;
	cout << "Time: " << cl3 << endl;
	for (i = 0; i < 8; i++){
		for (j = 0; j < 8; j++){
			cout << mtMMX[i][j] << " ";
		}
		cout << endl;
	}
	_getch();
	return 0;
}