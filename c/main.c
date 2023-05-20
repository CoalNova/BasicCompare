#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


//declare and initialize pieces/parts to be used
struct Account
{
    int accountID;
    int currentBill;
    int balance;
    int paidAmount;
};
typedef struct Account Account;


struct AccountCollection
{
    unsigned int count;
    unsigned int size;
    Account* data;
};
typedef struct AccountCollection AccountCollection;

struct AccountCollection InitCollection();
void DeinitCollection(struct AccountCollection* ac);
void PushToCollection(struct AccountCollection* ac,struct Account account);


int main(int argc, char ** argv)
{
    //declare oper/iter size and timer parts
    size_t 
        opers = (argc > 1)? atoi(argv[1]) : 100, 
        iters = (argc > 2)? atoi(argv[2]) : 100;
    clock_t 
        start, 
        end, 
        min = __LONG_MAX__, 
        max = 0, 
        average = 0, 
        diff, 
        total = clock();
        
    //Declare and begin iterations
    printf("C performing %zu operations over %zu iterations.\n", opers, iters);
    for (size_t iteration = 0; iteration < iters; iteration++)
    {           
        //start timer
        start = clock();
        //initialize psuedo random seed
        srand(opers + iters + iteration);
        
        //initialize collection
        AccountCollection accounts = InitCollection();
        //fill collection
        for (size_t i = 0; i < opers; i++)
        {
            Account account;
            account.accountID = i;
            account.balance = rand() % 1000;
            account.currentBill = rand() % 100;
            account.paidAmount = rand() % 1000;
            PushToCollection(&accounts, account);
        }
        
        //process accounts for collection
        for (size_t i = 0; i < opers; i++)
        {
            for (size_t j = 0; j < accounts.count; j++)
            {
                Account a = accounts.data[j];
                int payment = (a.balance < a.currentBill)? a.balance : a.currentBill; 
                accounts.data[j].paidAmount += payment;
                accounts.data[j].paidAmount >>= 2;
                accounts.data[j].currentBill += a.currentBill - payment + rand() % 100;
                accounts.data[j].currentBill >>= 2;
                accounts.data[j].balance += rand() % 100;
            }
        }
        
        //free collection
        DeinitCollection(&accounts);

        //grab time
        end = clock();
        diff = end - start;
        average += diff;
        if (diff < min) min = diff;
        if (diff > max) max = diff;
    }

    //print result
    printf("Done! after %f seconds\n", ((double)clock() - total) / CLOCKS_PER_SEC);
    printf("\tmax: %d, min: %d, avg: %d nanoseconds\n\n", 
        (int)(((double)max / CLOCKS_PER_SEC) * 1e9), 
        (int)(((double)min / CLOCKS_PER_SEC) * 1e9), 
        (int)((((double)average / iters) / CLOCKS_PER_SEC) * 1e9));
    return 0;
}


AccountCollection InitCollection()
{
    AccountCollection accounts;
    accounts.count = 0;
    accounts.size = 4;
    accounts.data = malloc(sizeof(Account) * accounts.size);
    return accounts;
}

void DeinitCollection(AccountCollection* accounts)
{
    free(accounts->data);
    accounts->count = 0;
    accounts->size = 0;
    accounts->data = 0;
}

void PushToCollection(AccountCollection* accounts, Account account)
{
    if (accounts->count + 1 >= accounts->size)
    {
        Account* newdata = malloc(sizeof(Account) * accounts->size * 2);
        memcpy(newdata, accounts->data, accounts->size);
        free(accounts->data);
        accounts->data = newdata;
        accounts->size *= 2;
    }
    accounts->data[accounts->count++] = account;
}
