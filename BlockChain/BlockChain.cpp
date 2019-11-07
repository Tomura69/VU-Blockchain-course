#include "Headers.h"

int main(){
    
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> rangeInt(111111, 999999);
    std::uniform_int_distribution<int> userr(0, 1000);
    std::uniform_real_distribution<double> rangeDouble(0, 121);

    std::vector<User> user;
    for (int i = 0; i < 5000; i++){
        User usser("Tomas" + std::to_string(i), "Klevas" + std::to_string(i), rangeInt(rng), rangeDouble(rng));
        user.push_back(usser);
    }

    std::vector<Transaction> transaction;
    for (int i = 0; i < 302; i++){
        time_t transactionTime;
        int ammountt = rangeDouble(rng);
        User senderr = user[userr(rng)];
        if (ammountt <= senderr.getBalance()){
            Transaction transactionn(ammountt, senderr, user[userr(rng)], std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
            transaction.push_back(transactionn);
        }
        else {
            //cout << "Tranzakcijai neuztenka pinigu: " << endl;
        }
    }

    BlockChain tomasCoin;

    tomasCoin.addTransaction(transaction);

    tomasCoin.printChain();

    cout << "Is chain valid? " << tomasCoin.isChainValid() << endl;
    
    return 0;
}