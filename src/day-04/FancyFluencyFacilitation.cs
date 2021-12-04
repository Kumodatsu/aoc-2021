using System.Collections.Generic;
using System.Linq;

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
}

static class Global {
    public static IEnumerable<string> GetInputLines() {
        string? line;
        while ((line = Console.ReadLine()) is not null)
            yield return line!;
    }

    public static readonly Sequencer Seq = Sequencer.Firstly();
}

class Sequencer {
    private Sequencer() {}
    public static Sequencer Firstly() => new();

    public Sequencer Firstly(Action action) => this.Then(action);

    public Sequencer Let<T>(Func<T> x, Action<T> f) {
        f(x());
        return this;
    }

    public Sequencer Let<T>(T x, Action<T> f)
        => Let(() => x, f);

    public Sequencer If(Func<bool> condition, Action f)
        => condition() ? this.Then(f) : this;

    public Sequencer While(Func<bool> condition, Action f)
        => condition() ? this.Then(f).While(condition, f) : this;
}
