#ifndef CITIES_H
#define CITIES_H
#include <string>

using namespace std;

class city {
public:
	city(string nameP, int costP) {
		name = nameP;
		cost = costP;
	};
	string name;
	int cost;
};

class CityNode {
public:
	CityNode() {};
	CityNode(string nameP) {
		name = nameP;
	}
	string name;
	int disatnce;
	bool isVisited;
};

#endif 