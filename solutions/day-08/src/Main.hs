module Main where

import qualified Data.Set as S
import Data.Set       ((\\), size, isSubsetOf, union)
import Data.Bifunctor (bimap)
import Data.Maybe     (mapMaybe)
import Data.List      (findIndex)

import System.Environment (getArgs)

main :: IO ()
main = do
    args <- getArgs
    let solve = case args of
            ["1"] -> solve1
            ["2"] -> solve2
            _     -> error "Invalid arguments."
    interact $ show . sum . map solve . parse
    where
        split xs = (take 10 xs, drop 11 xs)
        parse    = map (bimap (map S.fromList) (map S.fromList) . split . words)
                 . lines
        solve1 (signals, display) = r where
            r = length $ filter (flip elem [2, 3, 4, 7] . S.size) display
        solve2 (signals, display) = r where
            byCount n      = filter ((== n) . size) signals
            byUniqueCount  = head . byCount
            filterUnique p = head . filter p
            number         = (numbers!!)
            identify s     = findIndex (== s) numbers

            hook  = number 4 \\ number 1
            dash  = number 8 \\ number 0
            stick = hook     \\ dash
            poke  = number 0 \\ number 5 \\ number 1

            numbers = [
            {- 0 -} filterUnique (not . (hook `isSubsetOf`)) $ byCount 6,
            {- 1 -} byUniqueCount 2,
            {- 2 -} filterUnique (poke `isSubsetOf`) $ byCount 5,
            {- 3 -} filterUnique (\s -> s /= number 2 && s /= number 5) $ byCount 5,
            {- 4 -} byUniqueCount 4,
            {- 5 -} filterUnique (stick `isSubsetOf`) $ byCount 5,
            {- 6 -} poke `union` number 5,
            {- 7 -} byUniqueCount 3,
            {- 8 -} byUniqueCount 7,
            {- 9 -} number 8 \\ poke
                ]
            
            r = read $ concatMap show $ mapMaybe identify display
