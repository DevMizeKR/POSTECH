#include <iostream>
#include "fraction.h"

using namespace std;

int main()
{
	Fraction fr1;
	cout << "Original fraction (fr1) : ";
	fr1.print();
	fr1.store(5, 30); //fr1의 값을 변경
	cout << "Changed fraction (fr1) : ";
	fr1.print();
	fr1.simplify(); //fr1을 약분
	cout << "Simplified fraction (fr1) : ";
	fr1.print();
	cout << "\n";

	Fraction fr2(23, 27);
	cout << "Original fraction (fr2) : ";
	fr2.print();
	int fr2_numer = fr2.getNumer();
	cout << "The numerator of fr2 : " << fr2_numer << endl; //fr2의 분자를 받아 출력
	cout << "\n";

	Fraction fr3(5, 7);
	cout << "Original fraction (fr3) : ";
	fr3.print();
	++fr3;
	cout << "++fr3 : ";
	fr3.print(); //전위 증가 연산 실행 후 출력
	fr3++;
	cout << "fr3++ : ";
	fr3.print();
	cout << "\n";

	fr1 += fr3; //이항 증가 연산 실행
	cout << "fr1 += fr3 : ";
	fr1.print();
	cout << "\n";

	Fraction fr4;
	fr1.store(2, 5);
	cout << "Changed fraction (fr1) : ";
	fr1.print();
	fr2.store(-3, 6);
	cout << "Changed fraction (fr2) : ";
	fr2.print();
	
	fr4 = fr1 + fr2; //덧셈
	cout << "fr1 + fr2 : ";
	fr4.print();

	fr4 = fr1 - fr2; //뺄셈
	cout << "fr1 - fr2 : ";
	fr4.print();

	fr4 = fr1 * fr2; //곱셈
	cout << "fr1 * fr2 : ";
	fr4.print();

	fr4 = fr1 / fr2; //나눗셈
	cout << "fr1 / fr2 : ";
	fr4.print();

	fr4 = fr1; //대입 연산
	cout << "Assigned fr1 at fr4 : ";
	fr4.print();
	
	return 0;
}

Fraction::Fraction(int numer, int denom) //Constructor
{
	if (denom == 0) {
		cout << "Denominator can't be zero." << endl;
		exit(101);
	}
	else if (denom < 0) {
		numerator = -numer;
		denominator = -denom;
	}
	else {
		numerator = numer;
		denominator = denom;
	}
}

Fraction::Fraction(const Fraction& copyFrom) //Copy Constructor
{
	numerator = copyFrom.numerator;
	denominator = copyFrom.denominator;
}

Fraction::~Fraction() {} //Destructor

inline void Fraction::print() const //분수를 출력하는 method
{
	cout << numerator << "/" << denominator << endl;
}

void Fraction::store(int numer, int denom) //분수의 값을 변경하는 method
{
	if (denom == 0) {
		cout << "Denominator can't be zero." << endl;
		exit(101);
	}
	else if (denom < 0) {
		numerator = -numer;
		denominator = -denom;
	}
	else {
		numerator = numer;
		denominator = denom;
	}
}

void Fraction::simplify() //분수를 약분하는 method
{
	int temp, a, b;
	a = numerator;
	b = denominator;

	if (a == 0) //분자가 0인 경우 실행할 필요 없음
		return;
	else if (a < 0) //분자가 음수인 경우
		a = -a;
	else
		;
	while (b) { //분자와 분모의 최대공약수 구하기
		temp = a % b;
		a = b;
		b = temp;
	}
	numerator /= a;
	denominator /= a;
}