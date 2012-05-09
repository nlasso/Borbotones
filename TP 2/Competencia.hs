module Competencia (Competencia, nuevaC, categoriaC)

where
import Tipos
import Atleta
data Competencia = C Categoria 
	|Participar Atleta Competencia 
	|Finalizar [Int] [(Int, Bool)] Competencia deriving (Show)

nuevaC :: Deporte -> Sexo -> [Atleta] -> Competencia
nuevaC d s [a]
	| deporteIgual d [a] && todosDistintos [a] = C (d,s) 
	| deporteIgual d [a] == False = error "Los participantes no pertenecen a la categoria"
	| todosDistintos [a] == False = error "Atletas repetidos"


	
deporteIgual :: Eq Deporte => Deporte -> [Atleta] -> Bool
deporteIgual [] d = True
deporteIgual d (x:xs)
	| not(d `elem` (deportesA x)) = False
	| d `elem` (deportesA x) = deporteIgual d xs




todosDistintos:: [Atleta] -> Bool
todosDistintos [] = True
todosDistintos [x] = True
todosDistintos (x:y:xs) = ciaNumberA x /= ciaNumberA y && todosDistintos (y:xs)


	
categoriaC:: Competencia -> (Deporte,Sexo)
categoriaC (C (d,s)) = (d,s)


