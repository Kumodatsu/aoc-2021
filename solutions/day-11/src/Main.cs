const int GridW = 10, GridH = 10, Steps = 100;

int p;
if (args.Length != 1 || !int.TryParse(args[0], out p) || p is not (1 or 2)) {
    System.Console.WriteLine("You must specify the part (either 1 or 2).");
    return;
}

var grid = new int[GridW, GridH];

for (int y = 0; y < GridH; y++) {
    var line = Console.In.ReadLine();
    var octs = line!.Select(c => c - '0').ToArray();
    for (int x = 0; x < GridW; x++) {
        grid[x, y] = octs[x];        
    }
}

int total_flashes = 0;
for (int step = 0; p is 2 || step < Steps; step++) {
    bool flash = false;
    int current_flashes = 0;
    for (int y = 0; y < GridH; y++) {
        for (int x = 0; x < GridW; x++) {
            grid[x, y] += 1;
            if (grid[x, y] == 10)
                flash = true;
        }
    }
    while (flash) {
        flash = false;
        for (int y = 0; y < GridH; y++) {
            for (int x = 0; x < GridW; x++) {
                if (grid[x, y] >= 10) {
                    flash = true;
                    current_flashes++;
                    grid[x, y] = 0;

                    grid
                        .TryMap(x - 1, y - 1, o => o == 0 ? o : o + 1)
                        .TryMap(x,     y - 1, o => o == 0 ? o : o + 1)
                        .TryMap(x + 1, y - 1, o => o == 0 ? o : o + 1)
                        .TryMap(x - 1, y    , o => o == 0 ? o : o + 1)
                        .TryMap(x + 1, y    , o => o == 0 ? o : o + 1)
                        .TryMap(x - 1, y + 1, o => o == 0 ? o : o + 1)
                        .TryMap(x,     y + 1, o => o == 0 ? o : o + 1)
                        .TryMap(x + 1, y + 1, o => o == 0 ? o : o + 1);
                }
            }
        }
    }
    total_flashes += current_flashes;
    if (p is 2 && current_flashes == GridH * GridW) {
        Console.Out.WriteLine(step + 1);
        return;
    }
}

Console.Out.WriteLine(total_flashes);

static class Extensions {
    public static T[,] TryMap<T>(this T[,] a, int x, int y, Func<T, T> f) {
        if (x >= 0 && x < a.GetLength(0) && y >= 0 && y < a.GetLength(1))
            a[x, y] = f(a[x, y]);
        return a;
    }
}
