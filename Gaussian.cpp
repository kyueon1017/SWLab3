
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>


#define PI 3.141592
using namespace std;

float gaussian(float x, float y, float mux, float muy, float sigx, float sigy, float peak) {
	return(peak * exp(-pow((x - mux) / sigx, 2.0) - pow((y - muy) / sigy, 2.0)));
}

float fxy(float x, float y) {
	return(gaussian(x, y, 1., 1., 1., 2., 4) + gaussian(x, y, -1, -1., 1., 1., 2));
}

float dfxfx(float x, float y, float dx) { return (fxy(x + dx, y) - fxy(x, y)) / dx; } // fxy(x,y)를 x로 미분.
float dfxfy(float x, float y, float dy) { return (fxy(x, y + dy) - fxy(x, y)) / dy; } // fxy(x,y)를 y로 미분.
float EE(float x0, float x1, float y0, float y1) { return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)); } // 길이


int main() {
	float x, y; // -3<x<3, -3<y<3
	float dx = 1, dy = 1; // 0.1 -> 0.001

	float dx1 = 0.005, dy1 = 0.005;
	// gd.cpp()
	float psi = 0.001, eta = 0.00001; // psi = step_size, eta= acu

	float xi1 = 0.5, yi1 = 0.79; // 시작지점. 
	float xi0 = 1, yi0 = 1; // 초기값. 편의상 이 값들을 고정. 
	int iteration = 0;

	ofstream file("gaussian.txt");
	if (!file) {
		cout << "txt파일을 열 수 없습니다.\n";
		return -1;
	}

	for (y = -3; y < 3; y += dy) {
		for (x = -3; x < 3; x += dx) {
			cout << "f(" << x << ", " << y << ") : " << fxy(x, y) << endl;
			file << fxy(x, y) << " ";
		}
		file << endl;
	}

	//경사하강법 적용
	cout << "-----------------------\n";
	while (EE(xi0, xi1, yi0, yi1) > eta) { // (xi0,yi0)=기존좌표, (xi1,yi1)=새 좌표
		xi0 = xi1; // old <- new
		yi0 = yi1; // old <- new 

		xi1 += psi * dfxfx(xi0, yi0, dx1); //x변수 경사상승법
		yi1 += psi * dfxfy(xi0, yi0, dy1); //y변수 경사상승법

		cout << "(";
		cout << iteration << "번째)";
		cout << "xi0 : " << xi0 << ", " << "yi0 : " << yi0 << ", fxy(" << xi0 << ", " << yi0 << ") : " << fxy(xi0, yi0) << endl;
		iteration++;

		if (iteration > 500) {
			break;
		}
	}

	file.close();
	return 0;

}




