import System.Environment

main :: IO ()
main = do
    args <- getArgs
    let move = case args of
            ["1"] -> move1
            ["2"] -> move2
            _     -> error "Invalid arguments."
    interact $ solve move
    where
        start      = (0, 0, 0)
        solve move = show . mul . foldl move start . map tup . map words . lines
        
        mul (_, x, y) = x * y
        tup [d, n]    = (d, read n)
        
        move1 (a, x, y) ("forward", n) = (a, x + n, y    )
        move1 (a, x, y) ("up",      n) = (a, x,     y - n)
        move1 (a, x, y) ("down",    n) = (a, x,     y + n)

        move2 (a, x, y) ("forward", n) = (a,     x + n, y + a * n)
        move2 (a, x, y) ("up",      n) = (a - n, x,     y        )
        move2 (a, x, y) ("down",    n) = (a + n, x,     y        )
