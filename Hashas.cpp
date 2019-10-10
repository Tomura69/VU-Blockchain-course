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
#include <random>
#include <iterator> 
#include <map>

using std::cout;
using std::endl;

void Hash (long long hashvalue, std::string & hashFinal);
void Skaitymas (long long & hashvalue);
void Generuoti ();
void Test_Konstitucija (long long & hashvalue);
void Test_Paprastas (int uzduotis, long long & hashvalue);

int main(int argc, char const *argv[]){
	std::string input, hashFinal;
	std::string choice;
	long long hashvalue = 0;
	

	while (true){
		cout << "Jei norite skaityti duomenis is failu spauskite 1, jei norite ivesti spauskite 2" << endl;
		std::cin >> choice;
		if (int(choice[0]) == 49 || int(choice[0]) == 50){
			break;
		} 
	}
	if (int(choice[0]) == 50){
		cout << "Iveskite norima simboliu eilute" << endl;
		std::cin.ignore();
		getline(std::cin, input);
		for (int i = 0; i < input.size(); i++){
			hashvalue = hashvalue + int(input[i]);
		}
		hashvalue = hashvalue + input.size() * input[0] - input[1];
		Hash(hashvalue, hashFinal);
		cout << "HASH_VALUE: " << hashFinal << endl;
	}
	if (int(choice[0]) == 49){
		Skaitymas(hashvalue);
	}
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
		cout << "8-as - Konstitucijos hashavimas" << endl;
		cout << "9-as - Collision testas" << endl;
		std::cin >> uzduotis;
		if (uzduotis >= 1 && uzduotis <= 9) break;
		else cout << "Blogai pasirinkote faila" << endl;
	}

	std::string hashFinal;
    if (uzduotis == 8){
    	Test_Konstitucija (hashvalue);

		Hash(hashvalue, hashFinal);
		cout << "HASH_VALUE: " << hashFinal << endl;
    }
    else if (uzduotis == 9){
    	Generuoti();
		std::ifstream fd("generuoti_stringai.md");
		std::ofstream fr("hashai.md");
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
			hashvalue = hashvalue + input.size() * input[0] - input[1];
			if (fr.is_open()){
        		Hash(hashvalue, hashFinal);
        		fr << hashFinal << endl;
            }
            else {
        		cout << "Negalima sukurti failo" << endl;
    		}
        }
    	fd.close();
		fr.close();
		std::map<std::string, unsigned int> hasher;
	    std::ifstream fd1("hashai.md");
	    std::string z;

	    for (int i = 0; i < 100000; i++) {
	        fd1 >> z;
	        hasher.insert(std::pair<std::string, unsigned int>(z, 1));
	    }
	    std::cout << "Nesutapusiu hashu skaicius: " << hasher.size() << " is " << 100000 << endl;
	    fd1.close();
	}
    else{
		Test_Paprastas (uzduotis, hashvalue);

		Hash(hashvalue, hashFinal);
		cout << "HASH_VALUE: " << hashFinal << endl;
	}
}

void Test_Konstitucija (long long & hashvalue){
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
		hashvalue = hashvalue + input.size() * input[0] - input[1];
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

void Test_Paprastas (int uzduotis, long long & hashvalue){
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
	hashvalue = hashvalue + input.size() * input[0]  - input[1];
	fd.close();
}

void Generuoti (){
	// nuo 33 - 126
	std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> range(33, 126);
    std::ofstream fr("generuoti_stringai.md");
    char rand;
    if (fr.is_open()){
        for (int i = 1; i < 100000; i++){
            for (int y = 0; y < 5; y++){
            	rand = range(mt);
                fr << rand;
            }
            fr << ", ";
            for (int u = 0; u < 5; u++){
            	rand = range(mt);
            	fr << rand;
            }
            fr << endl;
        }
    }
    else {
        cout << "Negalima sukurti failo" << endl;
    }
    fr.close();
}

void Hash (long long hashvalue, std::string & hashFinal){
	
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
}