#pragma once
class Fraction
{
private:
	int numerator;
	int denominator;
public:
	Fraction(int numer = 0, int denom = 1); //Constructor
	Fraction(const Fraction& copyFrom); //Copy Constructor
	~Fraction(); //Destructor

	//Basic Functions
	void print() const;
	void store(int numer, int denom);
	void simplify();

	//Getter
	int getNumer() { return numerator; }
	int getDenom() { return denominator; }

	//Setter
	void setNumer(int numer) { this->numerator = numer; }
	void setDenom(int denom) { this->denominator = denom; }

	//Operation Overloading
	Fraction& operator++() { //ÀüÀ§ Áõ°¡
		numerator += denominator;
		return *this;
	}
	Fraction operator++(int) { //ÈÄÀ§ Áõ°¡
		Fraction temp(numerator, denominator);
		numerator += denominator;
		return temp;
	}
	Fraction& operator+=(const Fraction& fr) { //ÀÌÇ× Áõ°¡
		int a = denominator;
		a *= fr.denominator;
		numerator = numerator * fr.denominator + denominator * fr.numerator;
		denominator = a;
		simplify();
		return *this;
	}
	Fraction& operator=(const Fraction& fr) { //´ëÀÔ ¿¬»êÀÚ
		numerator = fr.numerator;
		denominator = fr.denominator;
		return *this;
	}
	Fraction operator+(const Fraction& fr) const { //µ¡¼À
		int a = denominator, b=numerator;
		a *= fr.denominator;
		b = b * fr.denominator + denominator * fr.numerator;
		Fraction new_fr(b, a);
		new_fr.simplify();
		return new_fr;
	}
	Fraction operator-(const Fraction& fr) const { //–E¼À
		int a = denominator, b=numerator;
		a *= fr.denominator;
		b = b * fr.denominator - denominator * fr.numerator;
		Fraction new_fr(b, a);
		new_fr.simplify();
		return new_fr;
	}
	Fraction operator*(const Fraction& fr) const { //°ö¼À
		int a = denominator, b = numerator;
		a *= fr.denominator;
		b *= fr.numerator;
		Fraction new_fr(b, a);
		new_fr.simplify();
		return new_fr;
	}
	Fraction operator/(const Fraction& fr) const { //³ª´°¼À
		int a = denominator, b = numerator;
		a *= fr.numerator;
		b *= fr.denominator;
		if (a == 0)
			return Fraction(b, a);
		Fraction new_fr(b, a);
		new_fr.simplify();
		return new_fr;
	}
};