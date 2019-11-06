#include "Headers.h"

User::User(std::string namee, std::string lastNamee, int asmensKodass, double balancee){
    name = namee;
    lastName = lastNamee;
    asmensKodas = asmensKodass;
    balance = balancee;
    std::string toHash = std::to_string(asmensKodas) + name + lastName;
    key = hashGenerator(toHash);
}

std::string User::getKey(){
    return key;
}

Transaction::Transaction(double a, User sender, User receiver, uint64_t time){
	amount = a;
	senderKey = sender.getKey();
	receiverKey = receiver.getKey();
	timeStamp = time;
    std::string toHash = std::to_string(timeStamp) + senderKey + receiverKey + std::to_string(amount);
    transactionHash = hashGenerator(toHash);
}

// BLOCK

Block::Block(int idx, std::string pHash){
    //uint64_t current = timeStamp();
    timeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//time(&current);
	index = idx;
	prevHash = pHash;
	blockHash = mineBlock(target);
}

std::string Block::mineBlock(int target){
    std::string dificulty = "";
    std::string hash;
    for (int i = 0; i < target; i++){
        dificulty += "0";
    }
    do{
        nonce++;
        std::string toHash = std::to_string(index) + std::to_string(nonce) + prevHash + std::to_string(timeStamp);
        hash = hashGenerator(toHash);
    } while(hash.substr(0, target) != dificulty);

    cout << "Block mined: " << hash << endl;
    return hash;
}

std::string Block::getHash(){
	return blockHash;
}

std::string Block::getPrevHash(){
	return prevHash;
}

int Block::getIndex(){
	return index;
}

std::vector<Transaction> Block::getTransactions(){
    return transactions;
}

bool Block::getFull (){
    return full;
}

bool Block::isBlock(){
    std::string toHash = "";
    for (int i = 0; i < transactions.size(); i++){
        toHash = toHash + transactions[i].transactionHash;
    }
    if (hashGenerator(toHash) == getMerkel())
        return true;
    else
        return false;
}

void Block::setMerkel(Block & block, std::vector<std::string> tarp){
    if (tarp.size() > 1){
        int last = tarp.size() - 1;
        std::vector<std::string> v;
        for (int i = 0; i < tarp.size() / 2; i++){
            std::string toHash = "";
            toHash = toHash + tarp[i] + tarp[last - i];
            v.push_back(hashGenerator(toHash));
        }
        block.setMerkel(block, v);
    } 
    else{
        block.merkelRoot = tarp[0];
    }
    
}

std::string Block::getMerkel(){
    return merkelRoot;
}

// BLOCKCHAIN

BlockChain::BlockChain(){
    Block genesis = createGenesisBlock();
    chain.push_back(genesis);
}

std::vector<Block> BlockChain::getChain(){
    return chain;
}

Block BlockChain::createGenesisBlock(){
    Block genesis(0, " ");
    return genesis;
}

Block BlockChain::getLatestBlock(){
    return chain.back();
}

void BlockChain::addTransaction(std::vector<Transaction> data){
    int index = (int)chain.size();
    for (int i = 0; i < index; i++){
        if (!chain[i].getFull()){
            int to = chain[i].transactions.size();
            int from = chain[i].transactions.size();
            for (int y = chain[i].transactions.size(); y < 100; y++){
                chain[i].transactions.push_back(data[y]);
                to++;
            }
        chain[i].full = true;
        std::vector<std::string> vec;
        for (int y = 0; y < chain[i].transactions.size(); y++){
            vec.push_back(chain[i].transactions[y].transactionHash);
        }
        chain[i].setMerkel(chain[i], vec);
        vec.clear();
        data.erase(data.begin() + from, data.begin() + to);
        }
    }
    if (data.size() != 0 && !chain[index-1].getFull()){
        int to = chain[index-1].transactions.size();
        int from = chain[index-1].transactions.size();
        for (int i = chain[index-1].transactions.size(); i < 100; i++){
            chain[index-1].transactions.push_back(data[i]);
            to++;
        }
        chain[index-1].full = true;
        std::vector<std::string> vec;
        for (int y = 0; y < chain[index-1].transactions.size(); y++){
            vec.push_back(chain[index-1].transactions[y].transactionHash);
        }
        chain[index-1].setMerkel(chain[index-1], vec);
        vec.clear();
        data.erase(data.begin() + from, data.begin() + to); 
    }
    int countt = (int)chain.size() - 1;
    if (data.size() != 0 && chain[index-1].getFull()){
        while (data.size() != 0){
            std::string prevhash = chain[countt].blockHash;
            Block block(countt+1, prevhash);
            if (data.size() > 100){
                int to = 0;
                for (int i = 0; i < 100; i++){
                    block.transactions.push_back(data[i]);
                    to++;
                }
                block.full = true;
                std::vector<std::string> vec;
                for (int y = 0; y < block.transactions.size(); y++){
                    vec.push_back(block.transactions[y].transactionHash);
                }
                block.setMerkel(block, vec);
                vec.clear();
                data.erase(data.begin(), data.begin() + to); 
            }
            else {
                for (int i = 0; i < data.size(); i++){
                    block.transactions.push_back(data[i]);
                }
                if (block.transactions.size() == 100){
                    block.full = true;
                    std::vector<std::string> vec;
                    for (int y = 0; y < block.transactions.size(); y++){
                        vec.push_back(block.transactions[y].transactionHash);
                    }
                    block.setMerkel(block, vec);
                    vec.clear();
                }
                else {
                    std::vector<std::string> vec;
                    for (int y = 0; y < block.transactions.size(); y++){
                        vec.push_back(block.transactions[y].transactionHash);
                    }
                    block.setMerkel(block, vec);
                    vec.clear();}
                data.clear();
            }
            chain.push_back(block);
            countt++;
        }
    }
    else cout << "Kazkas blogai" << endl;
}


bool BlockChain::isChainValid(){
    std::vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it){
        Block currentBlock = *it;
        if (!currentBlock.isBlock()){
            return false;
        }
        
        if (it != chain.begin()){
            Block previousBlock = *(it - 1);
            if (currentBlock.getPrevHash() != previousBlock.getHash()){
                return false;
            }
        }
    }
    return true;
}

void BlockChain::printChain(){
    std::vector<Block>::iterator it;
    for (it = chain.begin(); it != chain.end(); ++it){
        Block currentBlock = *it;
        std::vector<Transaction> v = currentBlock.getTransactions();
        cout << "Block ===================================" << endl;
        cout << "Index: " << currentBlock.getIndex() << endl;
        cout << "Hash: " << currentBlock.getHash() << endl;
        cout << "Previous Hash: " << currentBlock.getPrevHash() << endl;
        cout << "Merkel Root: " << currentBlock.getMerkel() << endl;
        /*for (int i = 0; i < v.size(); i++){
            cout << "   Transactions ===================================" << endl;
            cout << "   Amount: " << v[i].amount << endl;
            cout << "   SenderKey: " << v[i].senderKey << endl;
            cout << "   ReceiverKey: " << v[i].receiverKey << endl;
            cout << "   Timestamp: " << v[i].timeStamp << endl;
        }*/
        cout << "Is Block Valid?: " << currentBlock.isBlock() << endl;
        cout << endl;
    }
}

std::string hashGenerator(std::string toHash){
    
    int hashvalue = 0;
    std::string hashFinal = "";

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