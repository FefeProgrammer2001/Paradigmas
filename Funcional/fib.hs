fib :: Integer -> Integer
fib n
  | n < 0 = error "Negative number"
  | otherwise = fibHelper n 0 1

-- Tail Recursion

fibHelper :: Integer -> Integer -> Integer -> Integer
fibHelper 0 a _ = a
fibHelper n a b = fibHelper(n - 1) b (a + b)

main :: IO ()
main = do
    putStrLn "Type the value of N: "
    input <- getLine
    let n = read input :: Integer
    putStrLn $ "Fibonacci: " ++ show (fib n)
