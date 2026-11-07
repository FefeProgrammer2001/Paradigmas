import Text.Read (readMaybe)

type Church = forall a. (a -> a) -> a -> a

zero :: Church
zero _ x = x

sucessor :: Church -> Church
sucessor n f x = f(n f x)

paraChurch :: Integer -> Church
paraChurch n
    | n <= 0 = zero
    | otherwise = sucessor(paraChurch(n - 1))

paraInteiro :: Church -> Integer
paraInteiro n = n (+ 1) 0

main :: IO()
main = do
    putStr "Digite um inteiro positivo: "
    entrada <- getLine

    case readMaybe entrada :: Maybe Integer of
        Just n | n > 0 -> do
            let resultado = paraInteiro (sucessor (paraChurch n))
            putStrLn("O sucessor de " ++ show n ++ " eh " ++ show resultado)

        _ -> putStrLn "Entrada invalida: digite um inteiro positivo"