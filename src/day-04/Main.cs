using System;
using System.Collections.Generic;
using System.Linq;
using static Global;

const StringSplitOptions SplitOptions
    = StringSplitOptions.RemoveEmptyEntries
    | StringSplitOptions.TrimEntries;

Seq
.Let(0, part => Seq
.If(() => !(args.Length == 1 && int.TryParse(args[0], out part) && part is 1 or 2), () => Seq
    .Then(() => Console.WriteLine("{0} {1}",
        "You must specify a single argument which is either 1 or 2",
        "for Part 1 and Part 2 respectively."
    ))
    .Then(() => Environment.Exit(0))
)
.Let(() => new List<Chart>(), charts => Seq
.Let(GetInputLines, lines => Seq
.Let(() => new Queue<int>(lines.First().Split(',').Select(int.Parse)), numbers => Seq
.While(lines.GetEnumerator().MoveNext, () => Seq
    .Let(() => new Chart(), chart => lines
        .Take(Chart.BingoSize)
        .Select(s => s.Split(' ', SplitOptions).Select(int.Parse))
        .Zip(Enumerable.Range(0, Chart.BingoSize))
        .Select(t => (t is var (xs, i))
            .Then(xs
                .Select((x, j) => chart.RowsAndColumns[i].Add(x)
                    .Then(chart.RowsAndColumns[5 + j].Add(x))
                    .Then(chart.Sum += x)
                ).Count()
            )
        ).Count()
        .Then(() => charts.Add(chart))
    )
)
.Let(charts.Count, n_charts => Seq
.Let(0, bingos => Seq
.While(() => numbers.Count > 0, () => Seq
    .Let(numbers.Dequeue, n => charts
        .Where(chart => !chart.Bingo)
        .Select(chart => Seq
            .Let(false, marked => chart.RowsAndColumns
                .Select(roc => Seq
                    .If(() => roc.Remove(n) && !marked, () => Seq
                        .Firstly(() => marked = true)
                        .Then(() => chart.Sum -= n)
                    )
                ).Count()
                .Then(() => Seq
                    .If(() => chart.Bingo && (part is 1 || ++bingos == n_charts), () => Seq
                        .Firstly(() => Console.WriteLine(chart.Sum * n))
                        .Then(() => Environment.Exit(0))
                    )
                )
            )
        ).Count()
    )
)))))));

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
}
