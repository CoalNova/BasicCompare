const std = @import("std");
const Instant = std.time.Instant;
const rngenerator = std.rand.DefaultPrng;

//declare and initialize pieces/parts to be used
const Account = struct {
    account_id: i32,
    current_bill: i32,
    balance: i32,
    paid_amount: i32,
};
var gpa = std.heap.GeneralPurposeAllocator(.{}){};
const allocator = gpa.allocator();

pub fn main() !void {
    //declare oper/iter size and timer parts
    var args = std.process.args();
    const argv = [_]?[]const u8{ args.next(), args.next(), args.next() };
    const opers: usize = if (argv[1] != null)
        try std.fmt.parseUnsigned(usize, argv[1].?, 10)
    else
        100;
    const iters: usize = if (argv[2] != null)
        try std.fmt.parseUnsigned(usize, argv[2].?, 10)
    else
        100;
    var min: usize = std.math.maxInt(usize);
    var max: usize = 0;
    var average: usize = 0;
    var total = try Instant.now();

    //Declare and begin iterations
    std.debug.print("Zig performing {} operations over {} iterations.\n", .{ opers, iters });
    for (0..iters) |iteration| {
        //start timer
        var start = try Instant.now();
        //initialize psuedo random seed
        var rng = rngenerator.init(@intCast(u64, iters + opers) + iteration);

        //initialize collection
        var accounts = std.ArrayList(Account).init(allocator);
        //free collection (defer'd)
        defer accounts.deinit();
        //fill collection
        for (0..opers) |i|
            try accounts.append(.{
                .account_id = @intCast(i32, i),
                .current_bill = @intCast(i32, rng.next() % 1000),
                .balance = @intCast(i32, rng.next() % 100),
                .paid_amount = @intCast(i32, rng.next() % 1000),
            });

        //process accounts for collection
        for (0..opers) |_|
            for (0..opers) |i| {
                const a: Account = accounts.items[i];
                const payment: i32 = if (a.balance < a.current_bill) a.balance else a.current_bill;
                accounts.items[i].paid_amount += payment;
                accounts.items[i].current_bill += a.current_bill - payment + @intCast(i32, rng.next() % 100);
                accounts.items[i].balance += @intCast(i32, rng.next() % 100);
            };

        //grab time
        var diff = (try Instant.now()).since(start);
        if (diff < min) min = diff;
        if (diff > max) max = diff;
        average += diff;
    }
    //print result
    std.debug.print("Done! after {d:.5} seconds\n", .{@intToFloat(f64, (try Instant.now()).since(total)) / 1e9});
    std.debug.print("\tmax: {}, min: {}, avg: {} nanoseconds\n\n", .{ max, min, average / iters });
}
