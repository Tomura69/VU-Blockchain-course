#include "Headers.h"

Transaction::Transaction(double a, std::string sender, std::string receiver, time_t time){
	amount = a;
	senderKey = sender;
	receiverKey = receiver;
	timeStamp = time;
}

Block::Block(int idx, Transaction t, size_t pHash){
	index = idx;
	data = t;
	prevHash = pHash;
	blockHash = hashGenerator();
}

size_t Block::hashGenerator(){
	std::string toHash = std::to_string(data.amount) + data.senderKey + data.receiverKey + std::to_string(data.timeStamp);
	int hashvalue = 0;
	size_t hashFinal = 0;

	for (int i = 0; i < toHash.size(); i++){
		hashvalue = hashvalue + int(toHash[i]) + i;
		hashvalue += (hashvalue << 10);
		hashvalue ^= (hashvalue >> 6);
	}
	hashvalue = hashvalue + toHash.size() * toHash[0] - toHash[1];

	hashvalue = hashvalue * 5478;
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
	return hashFinal;
}

size_t Block::getHash(){
	return blockHash;
}

size_t Block::getPrevHash(){
	return prevHash;
}

size_t Block::getIndex(){
	return index;
}

bool Block::isHash(){
	return hashGenerator() == blockHash;
}

BlockChain::BlockChain()
{
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

std::vector<Block> BlockChain::getChain() {
    return chain;
}

Block BlockChain::createGenesisBlock()
{
    std::time_t current;
    Transaction d(0, "Genesis", "Genesis", time(&current));
    Block genesis(0, d, 0);
    return genesis;
}

Block BlockChain::getLatestBlock()
{
    return chain.back();
}

void BlockChain::addBlock(Transaction d)
{
    int index = (int)chain.size();
    std::size_t previousHash = (int)chain.size() > 0 ? getLatestBlock().getHash() : 0;
    Block newBlock(index, d, previousHash);
    chain.push_back(newBlock);
}

bool BlockChain::isChainValid()
{
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        if (!currentBlock.isHash())
        {
            return false;
        }
        
        if (it != chain.begin())
        {
            Block previousBlock = *(it - 1);
            if (currentBlock.getPrevHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
    
    return true;
}

void BlockChain::printChain() {
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\n\nBlock ===================================");
        printf("\nIndex: %d", currentBlock.getIndex());
        printf("\nAmount: %f", currentBlock.data.amount);
        printf("\nSenderKey: %s", currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s", currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld", currentBlock.data.timeStamp);
        printf("\nHash: %zu", currentBlock.getHash());
        printf("\nPrevious Hash: %zu", currentBlock.getPrevHash());
        printf("\nIs Block Valid?: %d", currentBlock.isHash());
    }
}
