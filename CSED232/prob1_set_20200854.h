#pragma once

#include <string>
using namespace std;

class MySet
{
private:
	int setsize;
	int* setElem;
	string name;
public:
	MySet();
	MySet(int size, int* setElem, int* elem_list, string name);
	~MySet();
	MySet operator+(const MySet& S2);
	MySet operator+(const int E1);
	MySet operator-(const MySet& S2);
	MySet operator-(const int E1);
	MySet operator*(const MySet& S2);
	MySet operator=(const MySet& S2);
	bool operator==(const MySet& S2);
	bool contains(const MySet& S2);
	bool contains(const int E1);
	bool isEmpty();
	int getSize();
	string toString();
};