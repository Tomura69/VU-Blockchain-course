#include <ctime>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <cstdint>
#include <typeinfo>  

using std::cout;
using std::endl;

class User {
private:
	std::string name;
	std::string lastName;
	int asmensKodas;
	std::string key;
	//Padaryti kad tikrintu balanca (turbut ten kai jau deda tranzakcijas i bloka iskviecia funkcija)
	double balance;
public:
	User(std::string namee, std::string lastNamee, int asmensKodass, double balancee);
	std::string getKey();
	double getBalance();
};

class Transaction {
public:
	double amount;
	std::string senderKey;
	std::string receiverKey;
	std::string transactionHash;
	std::uint64_t timeStamp;
	Transaction(double a, User sender, User receiver, uint64_t time);
	Transaction(){}
	~Transaction(){}
};

class Block {
private:
	int index;
	int nonce = 0;
	std::string blockHash;
	std::string prevHash;
	std::string merkelRoot;
	std::uint64_t timeStamp;
	int target = 4;
	bool full = false;
	std::vector<Transaction> transactions;
	void setMerkel(Block & block, std::vector<std::string> tarp);
	friend class BlockChain;
public:
	Block(int idx, std::string pHash);
	std::string mineBlock(int target);
	std::string getHash();
	std::string getPrevHash();
	std::string getMerkel();
	std::vector<Transaction> getTransactions();
	int getIndex();
	bool getFull ();
	bool isBlock();
	~Block(){}
};

class BlockChain {
private:
	Block createGenesisBlock();
	std::vector<Block> chain;
public:
	BlockChain();
	std::vector<Block> getChain();
	void addTransaction(std::vector<Transaction> data);
	bool isChainValid();
	Block getLatestBlock();
	void printChain();
	~BlockChain(){}
};

std::string hashGenerator(std::string toHash);