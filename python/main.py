import sys
import time
import random

#declare and initialize pieces/parts to be used
class Account:
    def __init__(self, accound_id, current_bill, balance, paid_amount):
        self.account_id = accound_id
        self.current_bill = current_bill
        self.balance = balance
        self.paid_amount = paid_amount

#declare oper/iter size and timer parts
opers = 100  
iters = 100  
if (len(sys.argv) > 1):
    opers = int(sys.argv[1])
if (len(sys.argv) > 2):
    iters = int(sys.argv[2])

total = time.time_ns()
min = 99999999
max = 0
average = 0

#Declare and begin iterations
print("Python performing " + str(opers) + " operations over " + str(iters) + " iterations.")
for iteration in range(iters):
    #start timer
    start = time.time_ns()
    #initialize psuedo random seed
    random.seed(opers + iters + iteration)
    #initialize collection
    accounts  = list([Account(0,0,0,0)])
    #fill collection
    for oper in range(opers):
        accounts.append(Account(oper, 
                                random.randint(0,1000),
                                random.randint(0,100),
                                random.randint(0,1000)))
    #process accounts for collection
    for _ in range(opers):
        for account in accounts:
            payment = {True: account.balance, False: account.current_bill} [account.balance < account.current_bill]  
            account.paid_amount += payment
            account.paid_amount >>= 2
            account.current_bill += account.current_bill - payment + random.randint(0,100)
            account.current_bill >>= 2
            account.balance += random.randint(0,100)
    #free collection
    accounts.clear()

    #grab time
    diff = time.time_ns() - start
    if (diff < min): 
        min = diff
    if (diff > max):
        max = diff
    average += diff

#print result
print("Done! after " + str((time.time_ns() - total) / 1e9) + " seconds")
print("\tmax: " + str(max) + ", min: " + str(min) + ", avg: " + str(int(average / iters)) + " nanoseconds\n")