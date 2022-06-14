#include <iostream>
#include <chrono>

using namespace std;

/*
	Для работы функции multiply4 нужно включить
	поддержку OpenMP в настройках проекта Visual Studio.

	Проект -> св-ва проекта -> С/C++ -> язык
*/

//int n = 4;
int n = 2048;

unsigned int prevRandom = 5;
unsigned pseudoRandom() {
	prevRandom = prevRandom * 1537 % 1923455;

	return prevRandom % 100;
}


void fillMatrix(double* M) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			M[i * n + j] = pseudoRandom() % 100 + 0.3;
		}
	}
}

void outputMatrix(double* M) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.1lf ", M[i * n + j]);
		}

		cout << endl;
	}

	cout << endl << endl;
}

// Без оптимизаций
void multiply1(double* A, double* B, double* C) {
	int t;

	for (int i = 0; i < n; i++) {
		t = i * n;

		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				C[t + j] += A[t + k] * B[k * n + j];
			}
		}
	}
}

double* makeTransponatedMatrix(double* M) {
	double* T = new double[n * n];

	double* rowM;

	for (int i = 0; i < n; i++) {
		rowM = M + i * n;

		for (int j = 0; j < n; j++) {
			T[j * n + i] = rowM[j];
		}
	}

	return T;
}

// Только транспонировать
void multiply2(double* A, double* B, double* C) {
	double* T = makeTransponatedMatrix(B);

	double* rowA;
	double* rowT;
	double* rowC;

	for (int i = 0; i < n; i++) {
		rowA = A + i * n;
		rowC = C + i * n;

		for (int j = 0; j < n; j++) {
			rowT = T + j * n;

			for (int k = 0; k < n; k++) {
				rowC[j] += rowA[k] * rowT[k];
			}
		}
	}
}

double multiplyVectors(double* vectorA, double* vectorB) {
	int n2 = (n / 4) * 4;
	double s1 = 0.0, s2 = 0.0, s3 = 0.0, s4 = 0.0;

	for (int i = 0; i < n2; i += 4) { // loop unroll x4
		s1 += vectorA[i] * vectorB[i];
		s2 += vectorA[i + 1] * vectorB[i + 1];
		s3 += vectorA[i + 2] * vectorB[i + 2];
		s4 += vectorA[i + 3] * vectorB[i + 3];
	}

	for (int i = n2; i < n; i++) {
		s1 += vectorA[i] * vectorB[i];
	}

	return (s4 + s3) + (s2 + s1);
}


// Транспонировать, использовать развёртку циклов
void multiply3(double* A, double* B, double* C) {
	double* T = makeTransponatedMatrix(B);

	double* rowA;
	double* rowC;

	for (int i = 0; i < n; i++) {
		rowA = A + i * n;
		rowC = C + i * n;

		for (int j = 0; j < n; j++) {
			rowC[j] = multiplyVectors(rowA, T + j * n);
		}
	}
}

// Транспонировать, использовать развёртку циклов и распараллеливание
void multiply4(double* A, double* B, double* C) {
	double* T = makeTransponatedMatrix(B);

	double* rowA;
	double* rowC;

	// в num_threads поставить число логических или физических ядер процессора
	#pragma omp parallel for num_threads(16)
	for (int i = 0; i < n; i++) {
		rowA = A + i * n;
		rowC = C + i * n;

		for (int j = 0; j < n; j++) {
			rowC[j] = multiplyVectors(rowA, T + j * n);
		}
	}
}


int main() {
	double* A = new double[n * n];
	double* B = new double[n * n];
	double* C = new double[n * n];

	for (int i = 0; i < n * n; i++) {
		C[i] = 0;
	}

	fillMatrix(A);
	fillMatrix(B);

	//outputMatrix(A); // not recommended if matrix is too big
	//outputMatrix(B);

	//outputMatrix(A);
	//outputMatrix(makeTransponatedMatrix(A));

	//multiply1(A, B, C);
	//multiply2(A, B, C);

	typedef chrono::high_resolution_clock Clock;
	auto t1 = Clock::now();

	multiply4(A, B, C);

	auto t2 = Clock::now();
	cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() / 1000.0 << endl;

	

	//outputMatrix(C);

	return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"