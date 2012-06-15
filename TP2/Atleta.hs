module Atleta (Atleta, nuevoA, nombreA, sexoA, anioNacimientoA,
nacionalidadA, ciaNumberA, deportesA, capacidadA,
entrenarDeporteA)
where
import Tipos

data Atleta = A String Sexo Int Pais Int [(Deporte, Int)] deriving (Show)

nuevoA:: String -> Sexo -> Int -> Pais -> Int -> Atleta
nuevoA nom s a nac cia = (A nom s a nac cia [])

nombreA :: Atleta -> String
nombreA (A n _ _ _ _ _ ) = n 

sexoA:: Atleta -> Sexo
sexoA (A _ s _ _ _ _ )  = s

anioNacimientoA:: Atleta -> Int
anioNacimientoA (A _ _ r _ _ _ ) = r

nacionalidadA:: Atleta -> Pais
nacionalidadA (A _ _ _ p _ _ ) = p

ciaNumberA:: Atleta -> Int
ciaNumberA (A _ _ _ _ c _ ) = c

deportesA:: Atleta -> [Deporte]
deportesA (A _ _ _ _ _ deportes ) = recorrerDeportes deportes

recorrerDeportes :: [(Deporte,Int)] -> [Deporte]
recorrerDeportes [] = []
recorrerDeportes (x:xs) = (fst x):(recorrerDeportes xs)

capacidadA::Atleta -> Deporte -> Int
capacidadA (A n s r p c ((x,xs):xss)) d
	| x == d = xs
	| x /= d = capacidadA (A n s r p c xss) d

entrenarDeporteA:: Atleta -> Deporte -> Int -> Atleta
entrenarDeporteA (A n s a p c (xss)) d cap
	| todosDistintos xss && deportesOrdenados xss && cap<100 = (A n s a p c (ordenar(agregarNuevoDeporte xss d cap)))
	| cap>100 = error "La capacidad debe estar entre 0 y 100"

todosDistintos:: [(Deporte,Int)] -> Bool
todosDistintos [] = True
todosDistintos [(x,xs)] = True
todosDistintos ((x,xs):(y,ys):xss) = not(x == y) && todosDistintos ((y,ys):xss)

deportesOrdenados::[(Deporte,Int)]->Bool
deportesOrdenados[] = True
deportesOrdenados [(x,xs)] = True
deportesOrdenados ((x,xs):(y,ys):xss) = x<=y && deportesOrdenados ((y,ys):xss)
	
agregarNuevoDeporte::[(Deporte,Int)] -> Deporte -> Int -> [(Deporte,Int)]
agregarNuevoDeporte [] dep cap = [(dep,cap)]
agregarNuevoDeporte ((x,xs):xss) dep cap
	| x == dep = agregarNuevoDeporte xss dep cap
	|otherwise = (x,xs):agregarNuevoDeporte xss dep cap
	
ordenar::[(Deporte,Int)]->[(Deporte,Int)]
ordenar [] = []
ordenar (xss) = (minimo xss):(ordenar xssSinMinimo)
	where xssSinMinimo = sacarUnaAparicion (minimo xss) xss
minimo::[(Deporte,Int)]->(Deporte,Int)
minimo [(x,xs)] = (x,xs)
minimo ((x,xs):xss) | x <= fst(minimo xss) = (x,xs)
	|otherwise = minimo xss
sacarUnaAparicion:: (Deporte,Int)->[(Deporte,Int)]->[(Deporte,Int)]
sacarUnaAparicion (y,ys) ((x,xs):xss)
	| x==y = xss
	| otherwise = (x,xs):(sacarUnaAparicion (y,ys) xss)