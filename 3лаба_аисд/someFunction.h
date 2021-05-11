#ifndef SOMEFUNCTION_H
#define SOMEFUNCTION_H
#include <string>
#include "List.h"
#include "Cities.h"

using namespace std;

bool setFunction(List<string>& arr, string str) {
	for (int i = 0; i < arr.getSize(); i++) {
		string a = arr[i];
		if (arr[i] == str)
			return true;
	}
	return false;
}

bool isAllVisited(CityNode* pcity, int count) {
	for (int i = 0; i < count; i++) {
		if (pcity[i].isVisited == false)
			return false;
	}
	return true;
}

int minimalPath(CityNode* pcity, int count) {
	int index = -1;
	int min = INT_MAX;
	for (int i = 0; i < count; i++) {
		if (pcity[i].disatnce < min && pcity[i].isVisited == false) {
			min = pcity[i].disatnce;
			index = i;
		}
	}
	return index;
}

int getIndex(string* arr, string str) {
	for (int i = 0; i < arr->size(); i++) {
		if (arr[i] == str)
			return i;
	}
	return -1;
}

int isJoin(string* indices, List<city>** contiguityList, int begin, int end) {
	for (int i = 0; i < contiguityList[begin]->getSize(); i++)
		if (getIndex(indices, (*contiguityList[begin])[i].name) == end)
			return (*contiguityList[begin])[i].cost;
	return -1;
}

#endif 