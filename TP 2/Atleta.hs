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
deportesA (A _ _ _ _ _ [(d,_)]) = [d]

capacidadA:: Atleta -> Deporte -> Int
capacidadA (A n s r p c ((x,xs):xss)) d
	| x == d = xs
	| x /= d = capacidadA (A n s r p c xss) d

entrenarDeporteA:: Atleta -> Deporte -> Int -> Atleta
entrenarDeporteA (A n s a p c (xss)) d cap = (A n s a p c (deportesFinal d xss cap))

deportesFinal:: Deporte -> [(Deporte,Int)] -> Int -> [(Deporte,Int)]
deportesFinal d [] cap = [(d,cap)] 
deportesFinal d ((x,xs):xss) cap
	| d == x = error "El deporte ya pertenece a la lista"
	| d /= x = (x,xs):deportesFinal d xss cap

	
