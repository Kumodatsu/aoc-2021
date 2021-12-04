global using static Global;

static class Global {
    public static IEnumerable<string> GetInputLines() {
        string? line;
        while ((line = Console.ReadLine()) is not null)
            yield return line!;
    }
}

static class Extensions {
    public static T Then<T>(this T obj, Action action) {
        action();
        return obj;
    }

    public static T Then<T>(this T obj, object x) => obj;
}

class Sequencer {
    public Sequencer() {}

    public Sequencer Firstly(Action<Sequencer> action)
        => this.Then(() => action(this));

    public Sequencer Let<T>(Func<T> x, Action<T> f)
        => this.Then(() => f(x()));

    public Sequencer Let<T>(T x, Action<T> f)
        => Let(() => x, f);

    public Sequencer If(Func<bool> condition, Action f)
        => condition() ? this.Then(f) : this;

    public Sequencer While(Func<bool> condition, Action f)
        => condition() ? this.Then(f).While(condition, f) : this;
}
