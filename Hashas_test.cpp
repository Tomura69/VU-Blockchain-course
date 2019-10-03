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

	Hash(hashvalue, hashFinal);

	cout << "HASH_VALUE: " << hashFinal << endl;
	return 0;
}

void Hash (long long hashvalue, std::string & hashFinal){
	//Paverti kiekviena simboli i skaiciu, tuos skaicius sudedi, padaugini is kazko, kad gauti kosmosa,
	//padalint i dalis, kad gaut 64 simbolius
	//char kodai (skaiciai ir raides) nuo 48 iki 122
	hashvalue = hashvalue * 5468;
	if (hashvalue % 10 == 0) hashvalue++;
	long long tarp;
	int tarp2;
	int apkeistas;
	int betkas;
	std::vector<int> hashas;
	hashFinal = "";
	for (int i = 0; i < 32; i++){
		tarp = (i + 1) * 57;
		apkeistas = (hashvalue * tarp) % 100;
		tarp2 = (apkeistas % 10) * 10 + (apkeistas / 10);
		if (tarp2 == 1 || tarp2 == 2){
			hashas.push_back((double)tarp2 * 53);
			continue;
		}
		if (tarp2 > 2 && tarp2 <= 7){
			hashas.push_back((double)tarp2 * 17);
			continue;
		}
		if (tarp2 < 19 && tarp2 > 7){
			hashas.push_back((double)tarp2 * 6.8);
			continue;
		}
		if (tarp2 < 48 && tarp2 >= 19){
			betkas = (double)tarp2 * 2.6;
			hashas.push_back(betkas);
			continue;
		}
		if (tarp2 >= 48){
			hashas.push_back(tarp2);
			continue;
		}
	}
	for (int i = 0; i < hashas.size(); i++){
		if (hashas[i] > 57 && hashas[i] <= 67){
			hashas[i] = hashas[i] - 10;
			continue;
		}
		if (hashas[i] > 67 && hashas[i] <= 77){
			hashas[i] = hashas[i] - 20;
			continue;
		}
		if (hashas[i] > 77 && hashas[i] <= 87){
			hashas[i] = hashas[i] - 30;
			continue;
		}
		if (hashas[i] > 87 && hashas[i] <= 92){
			hashas[i] = hashas[i] + 10;
			continue;
		}
		if (hashas[i] > 92 && hashas[i] < 97){
			hashas[i] = hashas[i] + 6;
			continue;
		}
		if (hashas[i] > 102 && hashas[i] <= 108){
			hashas[i] = hashas[i] - 6;
			continue;
		}
		if (hashas[i] > 108 && hashas[i] <= 114){
			hashas[i] = hashas[i] - 12;
			continue;
		}
		if (hashas[i] > 114 && hashas[i] <= 122){
			hashas[i] = hashas[i]/2 - 6;
			continue;
		}
	}
	char c;
	for (int i = 0; i < hashas.size(); i++){
		c = hashas[i];
		hashFinal = hashFinal + c;
	}
}