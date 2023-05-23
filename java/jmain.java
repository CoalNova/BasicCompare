import java.util.ArrayList;
import java.util.Random;

public class jmain{

    

    public static void main(String args[])
    {
        //declare oper/iter size and timer parts
        var opers = (args.length > 0)? Integer.parseInt(args[0]) : 100;
        var iters = (args.length > 1)? Integer.parseInt(args[1]) : 100;
        var total = System.nanoTime();
        long min = Long.MAX_VALUE, max = 0, average = 0;
        //Declare and begin iterations
        System.out.println("Java performing " + opers + " operations over " + iters + " iterations.");
        for (int iteration = 0; iteration < iters; iteration++) {
         
            //start timer
            var start = System.nanoTime();
            //initialize psuedo random seed
            Random rand = new Random(iters + opers + iteration);
            //initialize collection
            var accounts = new ArrayList<Account>();
            //fill collection
            for (int i = 0; i < opers; i++) {
                accounts.add(new Account(i, rand.nextInt(1000), rand.nextInt(100), rand.nextInt(1000)));
            }
            //process accounts for collection
            for (int i = 0; i < opers; i++) {
                for (Account account : accounts) {
                    var payment = (account.balance < account.currentBill)? account.balance : account.currentBill;
                    account.paidAmount += payment;
                    account.paidAmount >>= 2;
                    account.currentBill += account.currentBill - payment + rand.nextInt(100);
                    account.currentBill >>= 2;
                    account.balance += rand.nextInt(100);
                }
            }
            //free collection
            accounts.clear();
            //grab time
            var diff = System.nanoTime() - start;
            if (diff < min) min = diff;
            if (diff > max) max = diff;
            average += diff;
        }
        //print result

        System.out.println("Done! after " + String.valueOf((System.nanoTime() - total) / 1e9) + " seconds");
        System.out.println("\tmax: " + max + ", min: " + min + ", avg: " + (average / iters) + " nanoseconds\n");
    } 

}