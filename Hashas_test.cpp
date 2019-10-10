#include <iomanip>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iterator> 
#include <random>

using std::cout;
using std::endl;

void Hash (long long hashvalue, std::string & hashFinal);

int main(int argc, char** argv){
	std::string input, hashFinal;
	int choice;
	long long hashvalue = 0;

	input = argv[1];
	for (int i = 0; i < input.size(); i++){
		hashvalue = hashvalue + int(input[i]);
	}
	hashvalue = hashvalue + input.size() * input[0] - input[1];
	Hash(hashvalue, hashFinal);

	cout << hashFinal << endl;
	return 0;
}

void Hash (long long hashvalue, std::string & hashFinal){
	//Paverti kiekviena simboli i skaiciu, tuos skaicius sudedi, padaugini is kazko, kad gauti kosmosa,
	//padalint i dalis, kad gaut 64 simbolius
	//char kodai (skaiciai ir raides) nuo 48 iki 122
	hashvalue = hashvalue * 54768;
	hashFinal = "";
	std::mt19937 generator;
    std::uniform_int_distribution<int> uni(1, 2);
    std::uniform_int_distribution<int> uniNumber(48, 57);
    std::uniform_int_distribution<int> uniLetter(97, 102);
    generator.seed(hashvalue);

	if (hashvalue % 10 == 0) hashvalue++;
	int rand;
	std::vector<int> hashas;
	for (int i = 0; i < 32; i++){
		rand = uni(generator);
		if (rand == 1){
			hashas.push_back(uniNumber(generator));
			continue;
		}

		if (rand == 2){
			hashas.push_back(uniLetter(generator));
			continue;
		}
	}
		char c;
		for (int i = 0; i < hashas.size(); i++){
			c = hashas[i];
			hashFinal = hashFinal + c;
		}
		hashas.clear();
}