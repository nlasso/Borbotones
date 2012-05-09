
ultimo:: [Int] -> Int
ultimo [x] = x
ultimo (x:xs) = ultimo xs

principio:: [Int] -> [Int]
principio [x] = []
principio (x:xs) = x :(principio xs)

todosIguales:: Eq a => [a] -> Bool
todosIguales [] = True
todosIguales [x] = True
todosIguales (x:y:xs) = x == y && todosIguales (y:xs)

todosDistintos:: Eq a => [a] -> Bool
todosDistintos [] = True
todosDistintos [x] = True
todosDistintos (x:y:xs) = not(x == y) && todosDistintos (y:xs)

mismosElementos:: [Int] -> [Int] -> Bool
mismosElementos [] [] = True
mismosElementos [x] [h] = True
mismosElementos (x:xs)(h:hs) = xs == hs 

sacarTodos :: [Char] -> [Char] -> [Char]
sacarTodos x (y:ys)
   | length x > length (y:ys) = (y:ys)
   | length x == length (y:ys) = (sacarDelPrincipio x (y:ys))
   | (esPrefijo x (y:ys)) = (sacarTodos x (sacarPrefijo x (y:ys)))
   | (not (esPrefijo x (y:ys)))= (y:(sacarTodos x ys))

esPrefijo :: [Char] -> [Char] -> Bool
esPrefijo [] y = True
esPrefijo (x:xs) [] = False
esPrefijo (x:xs) (y:ys)
   | x==y = (esPrefijo xs ys)
   | otherwise = False

sacarPrefijo :: [Char] -> [Char] -> [Char]
sacarPrefijo [] y = y
sacarPrefijo (x:xs) (y:ys) = sacarPrefijo xs ys

sacarDelPrincipio :: [Char] -> [Char] -> [Char]
sacarDelPrincipio x y
   | (esPrefijo x y) = (sacarPrefijo x y)
   | (not (esPrefijo x y)) = y

sacarBlancosRepetidos :: [Char] -> [Char]
sacarBlancosRepetidos []       = []
sacarBlancosRepetidos (x:xs)
   | x==' '          = if (head xs)==' ' then (sacarBlancosRepetidos xs) else (x:(sacarBlancosRepetidos xs))
   | otherwise         = (x:(sacarBlancosRepetidos xs))

contarPalabras :: [Char] -> Integer
contarPalabras []    = 0
contarPalabras (x:[])    = 1
contarPalabras (x:xs)
   | x==' '   = if (head xs)==' ' then (contarPalabras xs) else 1 + (contarPalabras xs) 
   | otherwise = (contarPalabras xs)

palabraMasLarga :: [Char] -> [Char]
palabraMasLarga x = masLargo (palabras x)

masLargo :: [[Char]] -> [Char]
masLargo (x:[]) = x
masLargo (x:(y:ys))
   | length x >= length y    = masLargo (x:ys)
   | otherwise         = masLargo (y:ys)

palabras :: [Char] -> [[Char]]
palabras x
   | not(hayPalabra x)    = []
   | head x == ' '      = palabras (tail x)
   | otherwise         = p : (palabras (sacarPrefijo p x))
      where p = primerPalabra x

hayPalabra :: [Char] -> Bool
hayPalabra [] = False
hayPalabra (x:xs)
   | x == ' '    = hayPalabra xs
   | otherwise = True

primerPalabra :: [Char] -> [Char]
primerPalabra (x:[]) = [x]
primerPalabra (x:xs)
   | x == ' ' =  []
   | otherwise = x:(primerPalabra xs)

aplanar::[[Char]] -> [Char]
aplanar ((x:xs):[]) = (x:xs)
aplanar ((x:xs):(y:ys)) = (x:xs)++(aplanar (y:ys))

aplanarConBlancos:: [[Char]] -> [Char]
aplanarConBlancos ((x:xs):[]) = (x:xs)
aplanarConBlancos ((x:xs):(y:ys)) = (x:xs)++[' ']++(aplanarConBlancos(y:ys))

-- faltan los de los bits no tengo idea

nreduc :: Integer -> Integer
nreduc n = nrAux (reduc n) [n]

reduc :: Integer -> Integer
reduc n = prod (digitos n) * 2

digitos :: Integer -> [Integer]
digitos n   | 0 <= n && n < 10 = [n]
            | n >= 10 = digitos ( (n - (n `mod` 10)) `div` 10 ) ++ [n `mod` 10]

nrAux :: Integer -> [Integer] -> Integer
nrAux x y   | x `elem` y = primeraAparicion x y
            | x `notElem` y = nrAux (reduc x) (y ++ [x])

primeraAparicion :: Integer -> [Integer] -> Integer
primeraAparicion x y    | x == head y = 0
                | otherwise = 1 + primeraAparicion x (tail y)

prod :: [Integer] -> Integer
prod [] = 1
prod [0] = 0
prod n = head n * prod (tail n)

