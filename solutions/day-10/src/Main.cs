using System.Collections.Generic;

int p;
if (args.Length != 1 || !int.TryParse(args[0], out p) || p is not (1 or 2)) {
    System.Console.WriteLine("You must specify the part (either 1 or 2).");
    return;
}

Dictionary<char, int>
    syntax_values = new() {
        { ')', 3     },
        { ']', 57    },
        { '}', 1197  },
        { '>', 25137 }
    },
    completion_values = new() {
        { '(', 1 },
        { '[', 2 },
        { '{', 3 },
        { '<', 4 }
    };

Stack<char> stack             = new();
List<Int64> completion_scores = new();
int         syntax_score      = 0;
string?     line              = null;

int corrupted = 0;
while ((line = Console.In.ReadLine()) is not null) {
    foreach (char c in line) {
        if (c is '(' or '[' or '{' or '<') {
            stack.Push(c);
            continue;
        } else if ((stack.Pop(), c) is
                ('(', ')') or ('[', ']') or ('{', '}') or ('<', '>')) {
            continue;
        } else {
            syntax_score += syntax_values[c];
            stack.Clear();
            corrupted++;
            break;
        }
    }
    if (stack.Count != 0) {
        Int64 completion_score = 0;
        while (stack.TryPop(out char c))
            completion_score = completion_score * 5 + completion_values[c];
        completion_scores.Add(completion_score);        
    }
}

switch (p) {
    case 1:
        Console.Out.WriteLine(syntax_score);
        break;
    case 2:
        completion_scores.Sort();
        Console.Out.WriteLine(completion_scores[completion_scores.Count / 2]);
        break;
}
