#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

#define PI 3.141592
using namespace std;


// https://himbopsa.tistory.com/6?category=891084
class linearFn {
public:
	linearFn() { // 바꾸고자 하는 변수. 
		N = 4;
		x = new float[N];
		y = new float[N];
		x[0] = 0.1; y[0] = 1.1;
		x[1] = -0.1; y[1] = 0.9;
		x[2] = 1.1; y[2] = 2.1;
		x[3] = 0.9; y[3] = 1.9;
	};

	linearFn(char*); // 1번 
	int N;
	float* x, * y;
	float LossFn(float a, float b); // 3번 
	float dfabda(float a, float b, float da); //4-1번
	float dfabdb(float a, float b, float db); //4-2번

	float distance(float, float, float, float); // 2번

};

// 1. N개의 점을 생성하는 코드. 
linearFn::linearFn(char* xx) {
	ifstream dataFile(xx); // file을 읽어들인다. 
	if (!dataFile)	exit(666);
	dataFile >> N;
	//N = 4;// debug
	x = new float[N];
	y = new float[N];
	for (int i = 0; i < N; i++) dataFile >> x[i] >> y[i];
	for (int i = 0; i < N; i++)
		cout << " data " << x[i] << " " << y[i] << endl;
}

// 2. 각 점(xi,yi)와 직선 y=ax+b사이 최소 거리를 반환하는 함수. 
float linearFn::distance(float a, float b, float xx, float yy) {
	float p;
	p = (xx + a * yy - a * b) / (1 + a * a);
	return (xx - p) * (xx - p) + (yy - b - p * a) * (yy - b - p * a);
}

//3. 최소 거리값 총합을 구하는 함수.
float linearFn::LossFn(float a, float b) {
	float sum = 0.0;
	for (int i = 0; i < N; i++) {
		sum += distance(a, b, x[i], y[i]);
	}
	return sum;
}

//4-1. fa(a,b)
float linearFn::dfabda(float a, float b, float da) {
	cout << "dfabda(fa(a,b)) : " << LossFn(a + da, b) << endl;
	cout << "dfabda(fa(a,b)) : " << LossFn(a, b) << endl;
	return (LossFn(a + da, b) - LossFn(a, b)) / da;
}

//4-2. fb(a,b)
float linearFn::dfabdb(float a, float b, float db) {
	cout << "dfabdb(fb(a,b)) : " << LossFn(a, b + db) << endl;
	cout << "dfabdb(fb(a,b)) : " << LossFn(a, b) << endl;
	return (LossFn(a, b + db) - LossFn(a, b)) / db;
}

//5. EE함수
float EE(float x0, float y0, float x1, float y1) { return sqrt((x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1)); }

int main() {
	linearFn ab;

	float psi = 0.1;
	float eta = 0.0000001;
	// float psi=0.001, eta=0.0001;

	float da = 0.01, db = 0.01;
	float a0 = -2, b0 = 2;
	float a1 = 2.1, b1 = -0.8;
	//float a1=1.1, b1=80.0; // answer(a,b)=(1.2,100)

	int iteration = 0;


	while (EE(a0, b0, a1, b1) > eta && iteration < 1000) {
		a0 = a1;
		b0 = b1;
		a1 -= psi * ab.dfabda(a0, b0, da);
		b1 -= psi * ab.dfabdb(a0, b0, db);

		cout << "---------------\n";
		cout << "(";
		cout << iteration << "번째)";
		cout << "a0 : " << a0 << ", b0 : " << b0 << "   ->   " << "a1 : " << a1 << ", b1 : " << b1 << endl;
		iteration++;
	}
	cout << iteration << "번째  E = " << EE(a0, b0, a1, b1) << endl;

	// getchar();
	return 1;

}
