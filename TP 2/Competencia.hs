module Competencia (Competencia, nuevaC, categoriaC,participantesC, finalizadaC, rankingC, lesTocoControlAntiDopingC, leDioPositivoC, finalizarC, linfordChristieC)

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

finalizadaC:: Competencia -> Bool
finalizadaC ( C _) = False
finalizadaC (Finalizar rank dop c) = True
finalizadaC (Participar _ c) = finalizadaC c

rankingC:: Competencia -> [Atleta]
rankingC (C _) = error "La competencia debe estar finalizada"
rankingC (Finalizar rank dop c) = atletasCiaNumber (participantesC c) rank
rankingC (Participar _ c) = rankingC c

atletasCiaNumber:: [Atleta] -> [Int] -> [Atleta]
atletasCiaNumber [] xs = []
atletasCiaNumber (y:ys) xs
	| ciaNumberA y `elem` xs  = y: atletasCiaNumber ys xs 
	| not(ciaNumberA y `elem` xs)  = atletasCiaNumber ys xs

lesTocoControlAntiDopingC:: Competencia -> [Atleta]	
lesTocoControlAntiDopingC (C _) = error "La competencia debe estar finalizada"
lesTocoControlAntiDopingC (Finalizar rank dop c) = atletasCiaNumberDupla (participantesC c) dop
lesTocoControlAntiDopingC (Participar _ c) = lesTocoControlAntiDopingC c

atletasCiaNumberDupla:: [Atleta] -> [(Int,Bool)] -> [Atleta]
atletasCiaNumberDupla [] xss = []
atletasCiaNumberDupla (y:ys) ((x,xs):xss)
	| ciaNumberA y `elem` primerElemento((x,xs):xss)   = y: atletasCiaNumberDupla ys ((x,xs):xss) 
	| not(ciaNumberA y `elem` primerElemento((x,xs):xss)) = atletasCiaNumberDupla ys ((x,xs):xss)
	
primerElemento:: [(Int,Bool)] -> [Int]
primerElemento [] = []
primerElemento ((x,xs):xss) = x: primerElemento xss

leDioPositivoC:: Eq Atleta => Atleta -> Competencia -> Bool
leDioPositivoC a(Finalizar _ dop c) 
	| not(a `elem` lesTocoControlAntiDopingC c) = error "El atleta debe pertenecer a la lista de control antidoping"
	| a `elem` lesTocoControlAntiDopingC c = resultadoDoping a dop

resultadoDoping:: Atleta -> [(Int,Bool)] -> Bool
resultadoDoping (a) ((x,xs):xss)
	| ciaNumberA a == x = xs
	| not(ciaNumberA a == x) = resultadoDoping a xss

finalizarC:: Competencia -> [Int] -> [(Int,Bool)] -> Competencia
finalizarC (C (dep,sex)) _ _ = (C (dep,sex))
finalizarC (Participar a c) _ _ = (Participar a c)
finalizarC (Finalizar _ _ c) cia [(cian,dop)] = (Finalizar cia [(cian,dop)] c)
	
linfordChristieC :: Competencia -> Atleta -> Competencia
linfordChristieC (C (dep,sex)) at = (C (dep,sex))
linfordChristieC (Participar a (C (dep,sex))) at 
	| at /= a = (Participar a (C (dep,sex)))
	