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
#include <chrono>
#include <algorithm>
#include <iterator> 

using std::cout;
using std::endl;

void Hash (long long hashvalue, std::string & hashFinal);
void Skaitymas (long long & hashvalue);

int main(int argc, char const *argv[]){
	std::string input, hashFinal;
	int choice;
	long long hashvalue = 0;

	while (true){
		cout << "Jei norite skaityti duomenis is failu spauskite 1, jei norite ivesti spauskite 2" << endl;
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

	Hash(hashvalue, hashFinal);

	cout << "HASH_VALUE: " << hashFinal << endl;
	return 0;
}

void Skaitymas (long long & hashvalue){
	int uzduotis;

	while (true) {
		cout << "Pasirinkite, kuri faila nuskaityti:" << endl;
		cout << "1-as - Vienas simbolis" << endl;
		cout << "2-as - Vienas simbolis, bet skirtingas" << endl;
		cout << "3-as - 100000 symboliu tekstas" << endl;
		cout << "4-as - Daugiau nei 100000 symboliu tekstas" << endl;
		cout << "5-as - Tekstas" << endl;
		cout << "6-as - Tekstas, su vienu skirtingu simboliu" << endl;
		cout << "7-as - Tuscias failas" << endl;
		cout << "8-as - Konstitucijos eiluciu hashinimas" << endl;
		std::cin >> uzduotis;
		if (uzduotis >= 1 && uzduotis <= 8) break;
		else cout << "Blogai pasirinkote faila" << endl;
	}

    if (uzduotis == 8){
    	std::ifstream fd("konstitucija.md");
		std::string input, hashFinal;
		std::vector<int> hashas;
		hashvalue = 0;

		if (!fd) {
	    cout << "Failas neegzistuoja" << endl;
	    exit(1);
		}
		double suma = 0;
		std::cin.ignore();
		while (!fd.eof()){
			getline(fd, input);
			for (int i = 0; i < input.size(); i++){
				hashvalue = hashvalue + int(input[i]);
			}

			auto startas = std::chrono::system_clock::now();
			Hash(hashvalue, hashFinal);
			auto pabaiga = std::chrono::system_clock::now();
    		auto uztruko = std::chrono::duration_cast<
    		std::chrono::duration<double> >(pabaiga - startas).count();
    		suma = suma + uztruko;
		}
		cout << "Konstitucijos eiluciu hashavimas uztruko: " << suma << " sekundziu" << endl;
		fd.close();
    }

    else{
		std::string s = std::to_string(uzduotis);
		std::ifstream fd("test" + s + ".md");
		std::string input;

		if (!fd) {
	    cout << "Failas neegzistuoja" << endl;
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
}

void Hash (long long hashvalue, std::string & hashFinal){
	//Paverti kiekviena simboli i skaiciu, tuos skaicius sudedi, padaugini is kazko, kad gauti kosmosa,
	//padalint i dalis, kad gaut 64 simbolius
	//char kodai (skaiciai ir raides) nuo 48 iki 122
	hashvalue = hashvalue * 5468;
	hashFinal = "";
	if (hashvalue % 10 == 0) hashvalue++;
	long long tarp;
	int tarp2;
	int apkeistas;
	int betkas;
	std::vector<int> hashas;
	for (int i = 0; i < 32; i++){
		tarp = (i + 1) * 57;
		apkeistas = (hashvalue * tarp) % 100;
		tarp2 = (apkeistas % 10) * 10 + (apkeistas / 10);
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