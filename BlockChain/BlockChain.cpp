#include "Headers.h"

int main(){
    BlockChain tomasCoin;
    
    time_t transaction1Time;
    Transaction transaction1(1.5, "Tomas", "Jonas", time(&transaction1Time));
    tomasCoin.addBlock(transaction1);
    
    time_t transaction2Time;
    Transaction transaction2(0.2233, "Jonas", "Oskaras", time(&transaction2Time));
    tomasCoin.addBlock(transaction2);

    std::vector<Block> kazkas = tomasCoin.getChain();
    kazkas[0].mineBlock(4);
 
    tomasCoin.printChain();

    cout << "Is chain valid? " << tomasCoin.isChainValid() << endl;
    
    return 0;
}