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

void Hash (long long hashvalue, std::vector<int> &hashas);
void Skaitymas (long long & hashvalue);

int main(int argc, char const *argv[]){
	std::string input;
	int choice;
	std::vector<int> hashas;
	long long hashvalue = 0;

	while (true){
		cout << "Jei norite skaityti duomenis is failo spauskite 1, jei norite ivesti spauskite 2" << endl;
		std::cin >> choice;
		if (choice == 1 || choice == 2){
			break;
		} 
	}
	if (choice == 2){
		cout << "Iveskite norima simboliu eilute" << endl;
		std::cin.ignore();
		getline(std::cin, input);
		for (int i = 0; i < input.size(); i++){
			hashvalue = hashvalue + int(input[i]);
		}
	}
	if (choice == 1){
		Skaitymas(hashvalue);
	}
	Hash(hashvalue, hashas);
	// nuo 58 iki 64 istrinti ir nuo 91 iki 96
	for (int i = 0; i < hashas.size(); i++){
		if (hashas[i] > 57 && hashas[i] < 65){
			hashas[i] = hashas[i] - 9;
		}
		if (hashas[i] > 90 && hashas[i] < 97){
			hashas[i] = hashas[i] + 9;
		}
	}

	char c;
	cout << "HASH_VALUE: ";
	for (int i = 0; i < hashas.size(); i++){
		c = hashas[i];
		cout << c;
	}
	cout << endl;
	return 0;
}

void Skaitymas (long long & hashvalue){
	std::ifstream fd("text.md");
	std::string input;

	if (!fd) {
    cout << "Failas neegzistuoja";
    exit(1);
	}

	std::cin.ignore();
	while (!fd.eof()){
		getline(fd, input);
		for (int i = 0; i < input.size(); i++){
			hashvalue = hashvalue + int(input[i]);
		}
	}
	fd.close();
}

void Hash (long long hashvalue, std::vector<int> &hashas){
	//Paverti kiekviena simboli i skaiciu, tuos skaicius sudedi, padaugini is kazko, kad gauti kosmosa,
	//padalint i dalis, kad gaut 64 simbolius
	//char kodai (skaiciai ir raides) nuo 48 iki 122
	hashvalue = hashvalue * 5468;
	if (hashvalue % 10 == 0) hashvalue++;
	long long tarp;
	int tarp2;
	int betkas;
	for (int i = 0; i < 32; i++){
		tarp = (i + 1) * 57;
		tarp2 = (hashvalue * tarp) % 100;
		if (tarp2 == 1 || tarp2 == 2){
			hashas.push_back((double)tarp2 * 53);
			continue;
		}
		if (tarp2 > 0 && tarp2 <= 7){
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
}