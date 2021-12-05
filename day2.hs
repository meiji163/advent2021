--day 2

solve :: [(String, Int)] -> (Int, Int)
solve mvs = foldl inc (0,0) mvs
    where 
        inc (x,y) (dir,n)
            | dir == "forward" = (x+n,y)
            | dir == "up" = (x,y-n)
            | dir == "down" = (x,y+n)
            | otherwise = (x,y)

solve' :: [(String, Int)] -> (Int, Int, Int)
solve' mvs = foldl inc (0,0,0) mvs
    where 
        inc (x,y,z) (dir,n)
            | dir == "forward" = (x+n,y+z*n,z)
            | dir == "up" = (x,y,z-n)
            | dir == "down" = (x,y,z+n)
            | otherwise = (x,y,z)

readInt :: String -> Int
readInt = read

readTuple :: String -> (String, Int)
readTuple t = (x, readInt y)
    where x:y:[] = words t 

main = do
    contents <- readFile "input2.txt"
    --let list = [("forward",5),("down",5),("forward",8),("up",3),("down",8),("forward",2)]
    let list = map readTuple . lines $ contents
    let (x,y,_) = solve' list
    print (x*y)

