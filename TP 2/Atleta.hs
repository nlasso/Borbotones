module Atleta (Atleta, nuevoA, nombreA, sexoA, anioNacimientoA,
nacionalidadA, ciaNumberA, deportesA, capacidadA,
entrenarDeporteA)
where
import Tipos
data Atleta = A String Sexo Int Pais Int [(Deporte, Int)] deriving (Show)

nuevoA:: String -> Sexo -> Int -> Pais -> Int -> Atleta
nuevoA nom s a nac cia = A (nom s a nac cia [])

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
deportesA (A _ _ _ _ _ [d]) = [d]

capacidadA:: Atleta -> Deporte -> Int
capacidadA (A _ _ _ _ _ (r,d)) = cantdecapacidad r d

entrenarDeporteA:: Atleta -> Deporte -> Int -> Atleta
entrenarDeporteA (A n s a p c) = A n s a p c 



