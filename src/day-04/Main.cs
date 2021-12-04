new Sequencer()
    .Firstly(seq => seq
    .Let(0, part => seq
    .If(() => !(args.Length == 1 && int.TryParse(args[0], out part)
            && part is 1 or 2), () => seq
        .Then(() => Console.WriteLine("{0} {1}",
            "You must specify a single argument which is either 1 or 2",
            "for Part 1 and Part 2 respectively."
        ))
        .Then(() => Environment.Exit(0))
    )
    .Let(() => new List<Chart>(), charts => seq
    .Let(GetInputLines, lines => seq
    .Let(() => new Queue<int>(lines.First().Split(',').Select(int.Parse)),
        numbers => seq
    .While(lines.GetEnumerator().MoveNext, () => seq
        .Let(() => new Chart(), chart => lines
            .Take(Chart.BingoSize)
            .Select(s => s
                .Split(' ', StringSplitOptions.RemoveEmptyEntries
                    | StringSplitOptions.TrimEntries)
                .Select(int.Parse)
            )
            .Select((xs, i) => seq
                .Then(xs
                    .Select((x, j) => chart.RowsAndColumns[i].Add(x)
                        .Then(chart.RowsAndColumns[5 + j].Add(x))
                        .Then(chart.Sum += x)
                    )
                    .Count()
                )
            )
            .Count()
            .Then(() => charts.Add(chart))
        )
    )
    .Let(charts.Count, n_charts => seq
    .Let(0, bingos => seq
    .While(() => numbers.Count > 0, () => seq
        .Let(numbers.Dequeue, n => charts
            .Where(chart => !chart.Bingo)
            .Select(chart => seq
                .Let(false, marked => chart.RowsAndColumns
                    .Select(roc => seq
                        .If(() => roc.Remove(n) && !marked, () => seq
                            .Then(() => marked = true)
                            .Then(() => chart.Sum -= n)
                        )
                    )
                    .Count()
                    .Then(() => seq
                        .If(() => chart.Bingo &&
                                (part is 1 || ++bingos == n_charts), () => seq
                            .Then(() => Console.WriteLine(chart.Sum * n))
                            .Then(() => Environment.Exit(0))
                        )
                    )
                )
            )
            .Count()
        )
    ))))))));

class Chart {
    public const int BingoSize = 5;

    public HashSet<int>[] RowsAndColumns { get; set; } =
        new HashSet<int>[2 * BingoSize];
    public int Sum { get; set; }

    public bool Bingo => RowsAndColumns.Any(roc => !roc.Any());

    public Chart() => Enumerable
        .Range(0, 2 * BingoSize)
        .Select(i => RowsAndColumns[i] = new())
        .Count();
}
