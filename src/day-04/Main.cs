using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

const StringSplitOptions SplitOptions
    = StringSplitOptions.RemoveEmptyEntries
    | StringSplitOptions.TrimEntries;

int part = 0;
if (!(args.Length == 1 && int.TryParse(args[0], out part) && part is 1 or 2)) {
    Console.WriteLine(
        "You must specify a single argument which is either 1 or 2 for Part 1 "
        + "and Part 2 respectively."
    );
    return;
}

var charts  = new List<Chart>();
var lines   = GetInputLines();
var numbers = new Queue<int>(lines.First().Split(',').Select(int.Parse));
while (lines.GetEnumerator().MoveNext()) {
    var chart = new Chart();
    lines
        .Take(Chart.BingoSize)
        .Select(s => s.Split(' ', SplitOptions).Select(int.Parse))
        .Zip(Enumerable.Range(0, Chart.BingoSize))
        .Select(t => (t is var (xs, i))
            .Then(
                xs
                    .Select((x, j) => chart.RowsAndColumns[i]
                        .Add(x)
                        .Then(chart.RowsAndColumns[5 + j].Add(x))
                        .Then(chart.Sum += x)
                    )
                    .Force()
            )
        )
        .Force();
    charts.Add(chart);
}
var n_charts = charts.Count;
var bingos   = 0;
while (numbers.TryDequeue(out int n)) {
    foreach (var chart in charts) {
        if (chart.Bingo) continue;
        bool marked = false;
        foreach (var roc in chart.RowsAndColumns) {
            if (roc.Remove(n) && !marked) {
                marked = true;
                chart.Sum -= n;
            }
        }
        if (chart.Bingo && (part is 1 || ++bingos == n_charts)) {
            Console.WriteLine(chart.Sum * n);
            return;
        }
    }
}

IEnumerable<string> GetInputLines() {
    string? line;
    while ((line = Console.ReadLine()) is not null)
        yield return line!;
}

static class Extensions {
    public static IEnumerable<T> TakeUntil<T>(
        this IEnumerable<T> xs, Predicate<T> p
    ) => xs.TakeWhile(x => !p(x));

    public static T Then<T>(this T obj, Action action) {
        action();
        return obj;
    }

    public static T Then<T>(this T obj, object x) => obj;
    public static R Return<R>(this object obj, R x) => x;

    public static IEnumerable<T> Force<T>(this IEnumerable<T> e) {
        foreach (var _ in e);
        return e;
    }
}

class Chart {
    public const int BingoSize = 5;

    public HashSet<int>[] RowsAndColumns { get; set; } =
        new HashSet<int>[2 * BingoSize];
    public int Sum { get; set; }

    public bool Bingo => RowsAndColumns.Any(roc => !roc.Any());

    public Chart() {
        for (int i = 0; i < 2 * BingoSize; i++)
            RowsAndColumns[i] = new();
    }

    public override string ToString() {
        StringBuilder b = new();
        b.AppendLine($"Sum: {Sum}");
        for (int rc = 0; rc <= 1; rc++) {
            b.AppendLine(rc == 0 ? "Rows:" : "Columns:");
            for (int i = 0; i < BingoSize; i++) {
                b.Append("\t");
                foreach (var x in RowsAndColumns[i + rc * BingoSize])
                    b.Append($"{x} ");
                b.AppendLine();
            }
        }
        return b.ToString();
    }
}
