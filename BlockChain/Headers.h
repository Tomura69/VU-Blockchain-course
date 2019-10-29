#include <ctime>
#include <vector>
#include <random>
#include <iostream>

using std::cout;
using std::endl;

class Transaction {
public:
	double amount;
	std::string senderKey;
	std::string receiverKey;
	std::time_t timeStamp;
	Transaction(double a, std::string sender, std::string receiver, time_t time);
	Transaction(){}
	~Transaction(){}
};

class Block {
private:
	int index;
	int hashKey = 0;
	std::string blockHash;
	std::string prevHash;
	std::string hashGenerator();
public:
	Block(int idx, Transaction t, std::string pHash);
	void mineBlock(int target);
	std::string getHash();
	int getIndex();
	std::string getPrevHash();
	Transaction data;
	bool isHash();
	~Block(){}
};

class BlockChain {
private:
	Block createGenesisBlock();
	std::vector<Block> chain;
public:
	BlockChain();
	std::vector<Block> getChain();
	void addBlock(Transaction data);
	bool isChainValid();
	Block getLatestBlock();
	void printChain();
	~BlockChain(){}
};