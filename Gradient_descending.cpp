#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

#define PI 3.141592
using namespace std;


// Sprint 2
float fxy(float x, float y) { return sin(2 * PI * x) * sin(4 * PI * y); } // f0=1, f1=2
float dfxfx(float x, float y, float dx) { return (fxy(x + dx, y) - fxy(x, y)) / dx; } // fxy(x,y)를 x로 미분.
float dfxfy(float x, float y, float dy) { return (fxy(x, y + dy) - fxy(x, y)) / dy; } // fxy(x,y)를 y로 미분.
float EE(float x0, float x1, float y0, float y1) { return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)); } // 길이


int main() {

	float x, y; // 0<x<1, 0<y<1
	float dx = 0.05, dy = 0.05;

	float dx1 = 0.005, dy1 = 0.005;
	// gd.cpp()
	float psi = 0.001, eta = 0.00001; // psi = step_size, eta= acu

	float xi1 = 0.5, yi1 = 0.79; // 시작지점. 
	float xi0 = 1, yi0 = 1; // 초기값. 편의상 이 값들을 고정. 
	int iteration = 0;


	//ofstream을 이용해 txt file에 값을 집어넣기.
	ofstream file("sinfunc.txt");

	if (!file) {
		cout << "txt파일을 열 수 없습니다.\n";
		return -1;
	}

	//이중 for문을 이용해 값을 출력. 
	//3.20(일), 이중for문 x,y변수 순서 수정. 
	for (y = 0; y < 1; y += dy) {
		for (x = 0; x < 1; x += dx) {
			cout << "f(" << x << ", " << y << ") : " << fxy(x, y) << endl;
			file << fxy(x, y) << " ";
		}
		file << endl;
	}

	//Sprint1. 최고점 4개, 최저점 4개 결과값 표시.

	//최대값 4개
	cout << "-----------------------\n";
	cout << "최대값1 : " << "fxy(1/4,1/8) : " << fxy(1. / 4., 1. / 8.) << endl;
	cout << "최대값2 : " << "fxy(1/4,5/8) : " << fxy(1. / 4., 5. / 8.) << endl;
	cout << "최대값3 : " << "fxy(3/4,3/8) : " << fxy(3. / 4., 3. / 8.) << endl;
	cout << "최대값4 : " << "fxy(3/4,7/8) : " << fxy(3. / 4., 7. / 8.) << endl;

	//최솟값 4개
	cout << "-----------------------\n";
	cout << "최솟값1 : " << "f(1/4,3/8) : " << fxy(1. / 4., 3. / 8.) << endl;
	cout << "최솟값2 : " << "f(1/4,7/8) : " << fxy(1. / 4., 7. / 8.) << endl;
	cout << "최솟값3 : " << "f(3/4,1/8) : " << fxy(3. / 4., 1. / 8.) << endl;
	cout << "최솟값4 : " << "f(3/4,5/8) : " << fxy(3. / 4., 5. / 8.) << endl;

	//경사하강법 적용
	cout << "-----------------------\n";
	while (EE(xi0, xi1, yi0, yi1) > eta) { // (xi0,yi0)=기존좌표, (xi1,yi1)=새 좌표
		xi0 = xi1; // old <- new
		yi0 = yi1; // old <- new 

		xi1 -= psi * dfxfx(xi0, yi0, dx1); //x변수 경사하강법
		yi1 -= psi * dfxfy(xi0, yi0, dy1); //y변수 경사하강법

		cout << "(";
		cout << iteration << "번째)";
		cout << "xi0 : " << xi0 << ", " << "yi0 : " << yi0 << ", fxy(" << xi0 << ", " << yi0 << ") : " << fxy(xi0, yi0) << endl;
		iteration++;

		if (iteration > 200) {
			break;
		}
	}


	// getchar();

	file.close();

	return 0;


}
