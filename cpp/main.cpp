#include <iostream>
#include <chrono>
#include <vector>

//declare and initialize pieces/parts to be used
struct Account
{
    int32_t accountID;
    int32_t currentBill;
    int32_t balance;
    int32_t paidAmount;

    Account(int32_t id, int32_t bill, int32_t bal, int32_t paid) 
        :accountID(id), currentBill(bill), balance(bal), paidAmount(paid){}
};

int main(int argc, char ** argv)
{
    //declare oper/iter size and timer parts
    using namespace std;
    using namespace std::chrono;
    unsigned int 
        iters = (argc > 1) ? stoi(argv[1]): 100, 
        opers = (argc > 2) ? stoi(argv[2]): 100, 
        min = UINT32_MAX,
        max = 0, 
        average = 0;
    auto total = high_resolution_clock::now();
    
    //Declare and begin iterations
    cout << "C++ performing " << opers << " operations over " << iters << " iterations.\n";
    for (int iteration = 0; iteration < iters; iteration++)
    {
        //start timer
        auto start = high_resolution_clock::now();
        //initialize psuedo random seed
        srand(opers + iters + iteration);

        //initialize collection
        auto accounts = std::vector<Account>();
        //fill collection
        for (size_t i = 0; i < opers; i++)
            accounts.emplace_back(Account(i, rand() % 1000, rand() % 100, rand() % 1000));
        
        //process accounts for collection
        for (size_t i = 0; i < opers; i++)
            for (Account& account : accounts)
            {
                int payment = (account.balance < account.currentBill)?  account.balance : account.currentBill; 
                account.paidAmount += payment;
                account.currentBill += account.currentBill - payment + rand() % 100;
                account.balance += rand() % 100;
            }
        
        //free collection
        accounts.clear();
        
        //grab time
        unsigned int  diff = (duration_cast<nanoseconds>( high_resolution_clock::now() - start)).count();
        average += diff;
        if ( diff < min) min = diff;
        if ( diff > max) max = diff;
    }
    
    //print result
    cout << "Done! after " << ((double)(duration_cast<nanoseconds>( high_resolution_clock::now() - total)).count() / 1e9) << " seconds\n";
    cout << "\tmax: " << max << ", min: " << min << ", avg: " << average / iters << " nanoseconds\n" << endl;
}