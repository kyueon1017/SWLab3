#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

#define PI 3.141592
using namespace std;


// Sprint 2
float fxy(float x, float y) { return sin(2 * PI * x) * sin(4 * PI * y); } // f0=1, f1=2
float dfxfx(float x, float y, float dx) { return (fxy(x + dx, y) - fxy(x, y)) / dx; } // fxy(x,y)�� x�� �̺�.
float dfxfy(float x, float y, float dy) { return (fxy(x, y + dy) - fxy(x, y)) / dy; } // fxy(x,y)�� y�� �̺�.
float EE(float x0, float x1, float y0, float y1) { return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)); } // ����


int main() {

	float x, y; // 0<x<1, 0<y<1
	float dx = 0.05, dy = 0.05;

	float dx1 = 0.005, dy1 = 0.005;
	// gd.cpp()
	float psi = 0.001, eta = 0.00001; // psi = step_size, eta= acu

	float xi1 = 0.5, yi1 = 0.79; // ��������. 
	float xi0 = 1, yi0 = 1; // �ʱⰪ. ���ǻ� �� ������ ����. 
	int iteration = 0;


	//ofstream�� �̿��� txt file�� ���� ����ֱ�.
	ofstream file("sinfunc.txt");

	if (!file) {
		cout << "txt������ �� �� �����ϴ�.\n";
		return -1;
	}

	//���� for���� �̿��� ���� ���. 
	//3.20(��), ����for�� x,y���� ���� ����. 
	for (y = 0; y < 1; y += dy) {
		for (x = 0; x < 1; x += dx) {
			cout << "f(" << x << ", " << y << ") : " << fxy(x, y) << endl;
			file << fxy(x, y) << " ";
		}
		file << endl;
	}

	//Sprint1. �ְ��� 4��, ������ 4�� ����� ǥ��.

	//�ִ밪 4��
	cout << "-----------------------\n";
	cout << "�ִ밪1 : " << "fxy(1/4,1/8) : " << fxy(1. / 4., 1. / 8.) << endl;
	cout << "�ִ밪2 : " << "fxy(1/4,5/8) : " << fxy(1. / 4., 5. / 8.) << endl;
	cout << "�ִ밪3 : " << "fxy(3/4,3/8) : " << fxy(3. / 4., 3. / 8.) << endl;
	cout << "�ִ밪4 : " << "fxy(3/4,7/8) : " << fxy(3. / 4., 7. / 8.) << endl;

	//�ּڰ� 4��
	cout << "-----------------------\n";
	cout << "�ּڰ�1 : " << "f(1/4,3/8) : " << fxy(1. / 4., 3. / 8.) << endl;
	cout << "�ּڰ�2 : " << "f(1/4,7/8) : " << fxy(1. / 4., 7. / 8.) << endl;
	cout << "�ּڰ�3 : " << "f(3/4,1/8) : " << fxy(3. / 4., 1. / 8.) << endl;
	cout << "�ּڰ�4 : " << "f(3/4,5/8) : " << fxy(3. / 4., 5. / 8.) << endl;

	//����ϰ��� ����
	cout << "-----------------------\n";
	while (EE(xi0, xi1, yi0, yi1) > eta) { // (xi0,yi0)=������ǥ, (xi1,yi1)=�� ��ǥ
		xi0 = xi1; // old <- new
		yi0 = yi1; // old <- new 

		xi1 -= psi * dfxfx(xi0, yi0, dx1); //x���� ����ϰ���
		yi1 -= psi * dfxfy(xi0, yi0, dy1); //y���� ����ϰ���

		cout << "(";
		cout << iteration << "��°)";
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
