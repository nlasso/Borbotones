module Atleta (Atleta, nuevoA, nombreA, sexoA, anioNacimientoA,
nacionalidadA, ciaNumberA, deportesA, capacidadA,
entrenarDeporteA)
where
import Tipos

data Atleta = A String Sexo Int Pais Int [(Deporte, Int)] deriving (Show)

--instance Eq Atleta where 
	--(==) a1 a2 = (nombreA(a1)==nombreA(a2) && sexoA(a1) == sexoA(a2) && anioNacimientoA(a1) == anioNacimientoA(a2) && nacionalidadA(a1) == nacionalidadA(a2) && ciaNumberA(a1) == ciaNumberA(a2) && deportesA(a1) == deportesA(a2) && capacidadA(a1) == capacidadA(a2))

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
deportesA (A _ _ _ _ _ [(d,_)]) = [d]

capacidadA:: Atleta -> Deporte -> Int
capacidadA (A n s r p c ((x,xs):xss)) d
	| x == d = xs
	| x /= d = capacidadA (A n s r p c xss) d

entrenarDeporteA:: Atleta -> Deporte -> Int -> Atleta
entrenarDeporteA (A n s a p c (xss)) d cap
	| todosDistintos xss && deportesOrdenados xss && cap<100 = (A n s a p c (deportesFinal d xss cap))
	| not(todosDistintos xss) = error "Los deportes no pueden repetirse"
	| not(deportesOrdenados xss) = error "Los deportes deben ingresarse ordenados" 
	| cap>100 = error "La capacidad debe estar entre 0 y 100"

deportesFinal:: Deporte -> [(Deporte,Int)] -> Int -> [(Deporte,Int)]
deportesFinal d [] cap = [(d,cap)] 
deportesFinal d ((x,xs):xss) cap
	| d == x = error "El deporte ya pertenece a la lista"
	| d /= x = insertarOrdenado ((x,xs):xss) d cap
	
insertarOrdenado :: [(Deporte,Int)] -> Deporte -> Int -> [(Deporte,Int)]
insertarOrdenado [] d cap = [(d,cap)]
insertarOrdenado ((x,xs):xss) d cap
	| x > d  = ((d,cap):(x,xs):xss)
	| otherwise = (x,xs): insertarOrdenado xss d cap

todosDistintos:: [(Deporte,Int)] -> Bool
todosDistintos [] = True
todosDistintos [(x,xs)] = True
todosDistintos ((x,xs):(y,ys):xss) = not(x == y) && todosDistintos ((y,ys):xss)

deportesOrdenados::[(Deporte,Int)]->Bool
deportesOrdenados[] = True
deportesOrdenados [(x,xs)] = True
deportesOrdenados ((x,xs):(y,ys):xss) = x<=y && deportesOrdenados ((y,ys):xss)
	
