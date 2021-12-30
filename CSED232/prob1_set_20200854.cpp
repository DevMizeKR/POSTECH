#include "prob1_set_20200854.h"
MySet::MySet() {
	MySet::setsize = 0;
	MySet::setElem = NULL;
	MySet::name = "MySet";
}

MySet::MySet(int size, int* setElem, int* elem_list, string name) {
	MySet::setsize = size;
	MySet::name = name;
	MySet::setElem = new int[size];
	for (int i = 0; i < size; i++) {
		MySet::setElem[i] = elem_list[i];
	}
}

MySet::~MySet() {
	delete[] setElem;
}

MySet MySet::operator+(const MySet& S2) {
	MySet* temp;
	for (int i = 0; i < setsize ; i++)
		temp->setElem[i] = setElem[i];
	for (int j = 0; j < S2.setsize; j++) {
		for (int i = 0; i < setsize; i++) {
			if (S2.setElem[j] == setElem[i])
				break;
			if (i == 4) {
				temp->setElem[k] = S2.setElem[j];
			}
		}
	}
	
}
