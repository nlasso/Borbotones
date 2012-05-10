module Competencia (Competencia, nuevaC, categoriaC,participantesC)

where
import Tipos
import Atleta
data Competencia = C Categoria 
	|Participar Atleta Competencia 
	|Finalizar [Int] [(Int, Bool)] Competencia deriving (Show)

nuevaC :: Deporte -> Sexo -> [Atleta] -> Competencia
nuevaC d s [a]
	| deporteIgual d [a] && sexoIgual s [a] && todosDistintos [a] = C (d,s) 
	| deporteIgual d [a] == False = error "Los participantes no pertenecen a la categoria"
	| todosDistintos [a] == False = error "Atletas repetidos"

sexoIgual :: Sexo -> [Atleta] -> Bool
sexoIgual s [] = True
sexoIgual s (x:xs)
	| not(s == (sexoA x))= False
	| s == (sexoA x) = sexoIgual s xs
	
deporteIgual :: Eq Deporte => Deporte -> [Atleta] -> Bool
deporteIgual d [] = True
deporteIgual d (x:xs)
	| not(d `elem` (deportesA x)) = False
	| d `elem` (deportesA x) = deporteIgual d xs

todosDistintos:: [Atleta] -> Bool
todosDistintos [] = True
todosDistintos [x] = True
todosDistintos (x:y:xs) = ciaNumberA x /= ciaNumberA y && todosDistintos (y:xs)

categoriaC:: Competencia -> (Deporte,Sexo)
categoriaC (C (d,s)) = (d,s)

participantesC:: Competencia ->[Atleta]
participantesC ( C _ ) = []
participantesC ( Participar a c ) = (a : participantesC c)
participantesC ( Finalizar _ _ c ) = participantesC c


