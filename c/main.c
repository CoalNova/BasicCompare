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
        AccountCollection ac = InitCollection();
        //fill collection
        for (size_t i = 0; i < opers; i++)
        {
            Account account;
            account.accountID = i;
            account.balance = rand() % 1000;
            account.currentBill = rand() % 100;
            account.paidAmount = rand() % 1000;
            PushToCollection(&ac, account);
        }
        
        //process accounts for collection
        for (size_t i = 0; i < opers; i++)
        {
            for (size_t j = 0; j < ac.count; j++)
            {
                Account a = ac.data[j];
                int payment = (a.balance < a.currentBill)? a.balance : a.currentBill; 
                ac.data[j].paidAmount += payment;
                ac.data[j].currentBill += a.currentBill - payment + rand() % 100;
                ac.data[j].balance += rand() % 100;
            }
        }
        
        //free collection
        DeinitCollection(&ac);

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
    AccountCollection ac;
    ac.count = 0;
    ac.size = 4;
    ac.data = malloc(sizeof(Account) * ac.size);
    return ac;
}

void DeinitCollection(AccountCollection* ac)
{
    free(ac->data);
    ac->count = 0;
    ac->size = 0;
    ac->data = 0;
}

void PushToCollection(AccountCollection* ac, Account account)
{
    if (ac->count + 1 >= ac->size)
    {
        Account* newdata = malloc(sizeof(Account) * ac->size * 2);
        memcpy(newdata, ac->data, ac->size);
        free(ac->data);
        ac->data = newdata;
        ac->size *= 2;
    }
    ac->data[ac->count++] = account;
}