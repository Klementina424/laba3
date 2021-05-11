#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
#include "someFunction.h"
#include "Cities.h"
#define bigNumber INT_MAX

using namespace std;

int main() {

	cout << "Welcome to the ticketing terminal.\nWe cooperate with such air carriers as \"Airlines\", \nas well as \"LetiAvialinii\". \nYou shouldn't trust us!\n\n";

	fstream file;
	file.open("in.txt");
	int countString = 0;
	string tempString;
	while (!file.eof()){
		getline(file, tempString);
		countString++;
	}
	file.close();
	file.open("in.txt");
	string** inputInfo = new string*[countString];
	for (int i = 0; i < countString; i++) {
		inputInfo[i] = new string[4];
		for (int j = 0; j < 3; j++) {
			getline(file, tempString, ';');
			if (tempString != "N/A")
				inputInfo[i][j] = tempString;
			else
				inputInfo[i][j] = "";
		}
		getline(file, tempString);
		if (tempString != "N/A")
			inputInfo[i][3] = tempString;
		else
			inputInfo[i][3] = "";
	}
	file.close();
	List<string> cities;
	for (int i = 0; i < countString; i++) {
		if (!setFunction(cities, inputInfo[i][0])) cities.push(inputInfo[i][0]);
		if (!setFunction(cities, inputInfo[i][1])) cities.push(inputInfo[i][1]);
	}
	List<city>** contiguityList = new List<city>*[cities.getSize()];
	for (int i = 0; i < cities.getSize(); i++) {
		city* bufUno = new city(cities[i], 0);
		List<city>* bufTvino = new List<city>;
		bufTvino->push(*bufUno);
		contiguityList[i] = bufTvino;
	}
	for (int i = 0; i < countString; i++) {
		int j = 0;
		if (inputInfo[i][2] != "") {
			while (inputInfo[i][0] != (*contiguityList[j])[0].name)
				j++;
			city* temp = new city(inputInfo[i][1], stoi(inputInfo[i][2]));
			(*contiguityList[j]).push(*temp);
		}
		j = 0;
		if (inputInfo[i][3] != "") {
			while (inputInfo[i][1] != (*contiguityList[j])[0].name)
				j++;
			city* temp = new city(inputInfo[i][0], stoi(inputInfo[i][3]));
			(*contiguityList[j]).push(*temp);
		}
	}
	for (int i = 0; i < cities.getSize(); i++) {
		(*contiguityList[i]).sort();
	}
	string main, destination;
	cout << "Enter the starting point: ";
	cin >> main;
	cout << "\nEnter destination: ";
	cin >> destination;
	CityNode* cityNode = new CityNode[cities.getSize()];
	string* indices = new string[cities.getSize()];
	for (int i = 0; i < cities.getSize(); i++) {
		indices[i] = (*contiguityList[i])[0].name;
		cityNode[i].name = (*contiguityList[i])[0].name;
		cityNode[i].isVisited = false;
		cityNode[i].disatnce = bigNumber;
		if ((*contiguityList[i])[0].name == main)
			cityNode[i].disatnce = 0;
	}
	while (!isAllVisited(cityNode, cities.getSize())) {
		int curNodeIndex = minimalPath(cityNode, cities.getSize());

		for (int i = 1; i < (*contiguityList[curNodeIndex]).getSize(); i++ )
			if (cityNode[getIndex(indices, (*contiguityList[curNodeIndex])[i].name)].isVisited == false && cityNode[curNodeIndex].disatnce + (*contiguityList[curNodeIndex])[i].cost < cityNode[getIndex(indices, (*contiguityList[curNodeIndex])[i].name)].disatnce) 
				cityNode[getIndex(indices, (*contiguityList[curNodeIndex])[i].name)].disatnce = cityNode[curNodeIndex].disatnce + (*contiguityList[curNodeIndex])[i].cost;
			else
				continue;
		cityNode[curNodeIndex].isVisited = true;
	}
	int* ver = new int[cities.getSize()]; 
	int end = getIndex(indices, destination);
	int start = getIndex(indices, main);
	ver[0] = end;
	int k = 1; 
	int weight = cityNode[end].disatnce;
	while (end != start)
		for (int i = 0; i < cities.getSize(); i++)
			if (isJoin(indices, contiguityList, i, end) != -1) {
				int temp = weight - isJoin(indices, contiguityList, i, end);
				if (temp == cityNode[i].disatnce) {
					weight = temp;
					end = i;
					ver[k] = i;
					k++;
				}
			}
	cout << "\nYour most profitable route passes through the following cities: \n";
	int countDown = 1;
	for (int i = k - 1; i >= 0; i--) {
		cout << countDown << ". " << indices[ver[i]] << "\n";
		countDown++;
	}
	end = getIndex(indices, destination);
	cout << "\nFlight cost: " << cityNode[end].disatnce;
	cout << "\nSoft landing!\n";
}