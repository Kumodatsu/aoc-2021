int ds;
if (args.Length != 1 || !int.TryParse(args[0], out ds)) {
    Console.WriteLine("You must specify the number of days.");
    return -1;
}

var timers = new Int64[9];
Console.In.ReadToEnd().Split(',').Select(x => timers[Int64.Parse(x)]++).Count();

for (int d = 0; d < ds; d++) {
    Int64 zeroes = timers[0];
    for (int b = 1; b < timers.Length; b++)
        timers[b - 1] = timers[b];
    timers[6] += zeroes;
    timers[8] =  zeroes;
}

Console.Out.WriteLine(timers.Sum());
return 0;
