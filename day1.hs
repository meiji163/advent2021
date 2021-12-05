-- advent of code day 1
solve :: [Int] -> Int
solve [] = 0
solve xs = fst $ foldl inc (0,head xs) xs
    where inc (acc,y) x = if x>y then (acc+1,x) else (acc,x)

solve' :: [Int] -> Int
solve' (x:y:z:xs) = fst $ foldl inc (0,x:y:z:[]) xs 
    where inc (acc,y:z:w:[]) x = if x>y then (acc+1,z:w:x:[]) else (acc,z:w:x:[])
solve' _ = 0

readInt :: String -> Int
readInt = read

main = do
    contents <- readFile "input.txt"
    let list = map readInt . words $ contents
    --let list=[199,200,208,210,200,207,240,269,260,263]
    print (solve' list)
