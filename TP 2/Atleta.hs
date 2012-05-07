module Atleta (Atleta, nuevoA, nombreA, sexoA, anioNacimientoA,
nacionalidadA, ciaNumberA, deportesA, capacidadA,
entrenarDeporteA)
where
import Tipos
data Atleta = A String Sexo Int Pais Int [(Deporte, Int)] deriving (Show)


nuevoA:: (String, Sexo, Int, Pais, Int) -> Atleta
nuevoA (nom s a nac cia) = if (Sexo == Masculino) then (A nom Masculino a nac cia []) else (A nom Femenino a nac cia [])
--|s ==Femenino = (A n Masculino a p c [])
--|s ==Masculino = (A n Femenino a p c [])

queSexo::Sexo -> Sexo
queSexo s
| s == Masculino = Masculino
| s == Femenino = Femenino

nombreA :: Atleta -> String
nombreA (A n _ _ _ _ _ _) = n 

sexoA:: Atleta -> Sexo
sexoA (A _ s _ _ _ _ _)  = s

anioNacimientoA:: Atleta -> Int
anioNacimientoA (A _ _ r _ _ _ _) = r

nacionalidadA:: Atleta -> Pais
nacionalidadA (A _ _ _ p _ _ _) = p

ciaNumberA:: Atleta -> Int
ciaNumberA (A _ _ _ _ c _ _) = c

deportesA:: Atleta -> [Deporte]
deportesA (A _ _ _ _ _ [d] _) = [d]

capacidadA:: Atleta -> Deporte -> Int
capacidadA (A _ _ _ _ _ _ (r,d)) = cantdecapacidad r d

entrenarDeporteA:: Atleta -> Deporte -> Int -> Atleta
nuevoA (A n s a p c) = A n s a p c 



