using Int = System.Int64;

Int p;
if (args.Length != 1 || !Int.TryParse(args[0], out p) || p is not (1 or 2)) {
    Console.WriteLine("You must specify the part (1 or 2).");
    return -1;
}

var ns = Console.In.ReadToEnd()
    .Split(',').Select(Int.Parse).OrderBy(x => x).ToArray();
Int max      = ns[ns.Length - 1];
Int min      = ns[0];
Int min_cost = int.MaxValue;
for (Int i = min; i < max; i++) {
    Int cost = 0;
    foreach (Int n in ns)
        cost += Cost(i, n);
    min_cost = cost < min_cost ? cost : min_cost;
}
Console.Out.WriteLine(min_cost);
return 0;

Int Cost(Int i, Int n) => p is 2 ? Triangle(Distance(i, n)) : Distance(i, n);
Int Triangle(Int n) => (n * (n + 1)) / 2;
Int Distance(Int i, Int n) => Math.Abs(i - n);
