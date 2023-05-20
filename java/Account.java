
//declare and initialize pieces/parts to be used
public class Account {
    public int accountID;
    public int currentBill;
    public int balance;
    public int paidAmount;
    public Account(
        int accountID,
        int currentBill,
        int balance,
        int paidAmount)
    {
        this.accountID = accountID;
        this.currentBill = currentBill;
        this.balance = balance;
        this.paidAmount = paidAmount;
    }
}
