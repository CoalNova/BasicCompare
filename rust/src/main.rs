use rand::Rng;

//declare and initialize pieces/parts to be used
#[derive(Debug, Copy, Clone)]
struct Account{
    account_id: i32,
    current_bill: i32,
    balance: i32,
    paid_amount: i32,
}

fn main() {
    
    //declare oper/iter size and timer parts
    let argv : Vec<String> = std::env::args().collect();
    let opers: u32 = if argv.len() > 1 { str::parse::<u32>(&argv[1]).unwrap() } else {100};
    let iters: u32 = if argv.len() > 2 { str::parse::<u32>(&argv[2]).unwrap() } else {100}; 
  
    let mut min = std::time::Duration::new(9999, 0); 
    let mut max = std::time::Duration::new(0, 0); 
    let mut average = std::time::Duration::new(0, 0);
    let total = std::time::Instant::now();

    //Declare and begin iterations
    print!("Rust performing {} operations over {} iterations.\n", opers, iters);
    for _ in 0..iters{
        //start timer
        let start = std::time::Instant::now();
        //initialize psuedo random seed
        let mut rng = rand::thread_rng();

        //initialize collection
        let mut accounts = Vec::<Account>::new();

        //fill collection
        for i in 0..opers {
            accounts.push(Account{
                account_id : i as i32,
                current_bill : rng.gen::<i32>() % 100,
                balance: rng.gen::<i32>() % 100,
                paid_amount: rng.gen::<i32>() % 100
            });
        }
        
        //process accounts for collection
        for _ in 0..opers{
            for account in accounts.iter_mut(){
                let payment: i32 = if account.balance < account.current_bill 
                    {account.balance} 
                else 
                    {account.current_bill};
                account.paid_amount += payment;
                account.paid_amount >>= 2;
                account.current_bill += account.current_bill - payment + rng.gen::<i32>() % 100;
                account.current_bill >>= 2;
                account.balance += rng.gen::<i32>() % 100;

            }
        }

        //free collection
        accounts.clear();

        //grab time
        let diff = start.elapsed();
        if diff < min { min = diff };
        if diff > max { max = diff };
        average += diff;
    }
    //print result
    print!("Done! after {:?}\n", total.elapsed());
    print!("\tmax: {:?}, min: {:?}, avg: {:?} nanoseconds\n\n", max.subsec_nanos(), min.subsec_nanos(), (average / iters).subsec_nanos());
}
