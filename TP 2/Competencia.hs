module Competencia (Competencia, nuevaC, categoriaC,participantesC, finalizadaC, rankingC, lesTocoControlAntiDopingC, leDioPositivoC, finalizarC, linfordChristieC,
gananLosMasCapacesC, sancionarTrampososC)

where
import Tipos
import Atleta
data Competencia = C Categoria 
	|Participar Atleta Competencia 
	|Finalizar [Int] [(Int, Bool)] Competencia deriving (Show)

nuevaC :: Deporte -> Sexo -> [Atleta] -> Competencia
nuevaC d s atletas
	| deporteIgual d atletas && sexoIgual s atletas && todosDistintos atletas = agregarParticipantes atletas (C (d,s)) 
	| deporteIgual d atletas == False = error "Los participantes no pertenecen a la categoria"
	| todosDistintos atletas == False = error "Atletas repetidos"

categoriaC :: Competencia -> (Deporte,Sexo)
categoriaC (C (d,s)) = (d,s)
categoriaC (Participar _ comp) = categoriaC comp
categoriaC (Finalizar _ _ comp) = categoriaC comp

participantesC:: Competencia ->[Atleta]
participantesC ( C _ ) = []
participantesC ( Participar a c ) = (a : participantesC c)
participantesC ( Finalizar _ _ c ) = participantesC c

finalizadaC:: Competencia -> Bool
finalizadaC ( C _ ) = False
finalizadaC (Participar _ c) = False
finalizadaC (Finalizar rank dop c) = True


rankingC:: Competencia -> [Atleta]
rankingC (C _) = error "La competencia debe estar finalizada"
rankingC (Participar _ c) = error "La competencia debe estar finalizada"
rankingC (Finalizar rank dop c) = atletasCiaNumber rank (participantesC c)


lesTocoControlAntiDopingC :: Competencia -> [Atleta]	
lesTocoControlAntiDopingC (C _) = error "La competencia debe estar finalizada"
lesTocoControlAntiDopingC (Participar _ c) = error "La competencia debe estar finalizada"
lesTocoControlAntiDopingC (Finalizar rank dop c) = atletasCiaNumberDupla (participantesC c) dop
	
leDioPositivoC :: Competencia -> Atleta -> Bool
leDioPositivoC (Finalizar _ dop c) a = resultadoDoping a dop

finalizarC :: Competencia -> [Int] -> [(Int,Bool)] -> Competencia
finalizarC (C cat) rank dop = (Finalizar [] [] (C cat))
finalizarC (Participar a c) rank dop = Finalizar rank dop (Participar a c)
	
linfordChristieC ::  Competencia -> Atleta -> Competencia
linfordChristieC (Participar a c) at 
    | ciaNumberA a == ciaNumberA at = c
    | otherwise = Participar a (linfordChristieC c at)

gananLosMasCapacesC :: Competencia -> Bool
gananLosMasCapacesC (Finalizar rank _ c) = capacidadesOrdenadas(reverso (atletasCapaces (rank) (participantesC c) (categoriaC c)))

sancionarTrampososC :: Competencia -> Competencia
sancionarTrampososC (Finalizar rank dop c) = (Finalizar (rankSinDop rank (participantesDopados dop)) dop c)

----------------------------AUXILIARES--------------------------------------------
----------------------------Auxiliar NuevaC---------------------------------------

sexoIgual :: Sexo -> [Atleta] -> Bool
sexoIgual s [] = True
sexoIgual s (x:xs)
	| not(s == (sexoA x))= False
	| s == (sexoA x) = sexoIgual s xs
	
deporteIgual :: Deporte -> [Atleta] -> Bool
deporteIgual d [] = True
deporteIgual d (x:xs) = d `elem` (deportesA x) && deporteIgual d xs

todosDistintos:: [Atleta] -> Bool
todosDistintos [] = True
todosDistintos [x] = True
todosDistintos (x:y:xs) = ciaNumberA x /= ciaNumberA y && todosDistintos (y:xs)

-------------------------Auxiliar RankingC--------------------------

atletasCiaNumber:: [Int] -> [Atleta] -> [Atleta]
atletasCiaNumber [] _ = []
atletasCiaNumber (y:ys) (x:xs)
	| ciaNumberA x == y  = (atletaPorCiaNumber y xs):(atletasCiaNumber ys xs) 
	| otherwise  = atletasCiaNumber ys xs 
	
ciaNumbersA :: [Atleta] -> [Int]
ciaNumbersA [] = []
ciaNumbersA (x:xs) = (ciaNumberA x):(ciaNumbersA xs)

atletaPorCiaNumber :: Int -> [Atleta] -> Atleta
atletaPorCiaNumber cia (a:atletas)
	| ciaNumberA a == cia = a
	| otherwise = atletaPorCiaNumber cia atletas

-------------------------Auxiliar lesTocoControlAntiDopingC---------

atletasCiaNumberDupla:: [Atleta] -> [(Int,Bool)] -> [Atleta]
atletasCiaNumberDupla [] xss = []
atletasCiaNumberDupla (y:ys) ((x,xs):xss)
	| ciaNumberA y `elem` primerElemento((x,xs):xss)   = y: atletasCiaNumberDupla ys ((x,xs):xss) 
	| not(ciaNumberA y `elem` primerElemento((x,xs):xss)) = atletasCiaNumberDupla ys ((x,xs):xss)

primerElemento:: [(Int,Bool)] -> [Int]
primerElemento [] = []
primerElemento ((x,xs):xss) = x: primerElemento xss

------------------------Auxiliar leDioPositivoC---------------------

resultadoDoping:: Atleta -> [(Int,Bool)] -> Bool
resultadoDoping (a) ((x,xs):xss)
	| ciaNumberA a == x = xs
	| not(ciaNumberA a == x) = resultadoDoping a xss

------------------------Auxiliar gananLosMasCapacesC-----------------

atletasCapaces:: [Int] -> [Atleta] -> (Deporte,Sexo) -> [Int]
atletasCapaces [] (y:ys) (dep,sex) = []
atletasCapaces _ [] (dep,sex)= []
atletasCapaces (x:xs) (y:ys) (dep,sex)
	| x == ciaNumberA y = (capacidadA y dep) : (atletasCapaces xs ys (dep,sex))
	| not(x == ciaNumberA y) = atletasCapaces xs ys (dep,sex)

reverso:: [Int] -> [Int]
reverso [] = []
reverso (x:xs) = agregarAtras x (reverso xs)

agregarAtras::Int->[Int]->[Int]
agregarAtras x [] = [x]
agregarAtras x (y:ys) = y:(agregarAtras x ys) 

capacidadesOrdenadas::[Int]->Bool
capacidadesOrdenadas(x:(y:ys)) = x<=y && capacidadesOrdenadas (y:ys)
capacidadesOrdenadas _ = True

participantesDopados :: [(Int,Bool)] -> [Int]
participantesDopados [] = []
participantesDopados ((x,xs):xss)
    | xs == True = x:(participantesDopados xss)
    | xs == False = participantesDopados xss

rankSinDop :: [Int] -> [Int] -> [Int]
rankSinDop [] ys = []
rankSinDop (x:xs) ys
    | (x `elem` ys) = (rankSinDop xs ys)
    | not( x `elem` ys) = x:(rankSinDop xs ys)

compararAtleta :: Atleta -> [Atleta] -> Bool
compararAtleta atleta [] = False
compararAtleta atleta (x:xs)
	|ciaNumberA atleta == ciaNumberA x = True
	|ciaNumberA atleta /= ciaNumberA x = compararAtleta atleta xs
	
agregarParticipantes :: [Atleta] -> Competencia -> Competencia
agregarParticipantes [] comp = comp
agregarParticipantes (x:xs) comp = Participar x ( agregarParticipantes xs comp ) 
	
	
------------------------------------------------ TESTING ------------------------------------------------

a1 = nuevoA "Atleta1" Masculino 1989 "Argentina" 10
ad1 = entrenarDeporteA a1 "Futbol" 54
add1 = entrenarDeporteA ad1 "Handball" 12

a2 = nuevoA "Atleta2" Masculino 1990 "Brasil" 12
ad2 = entrenarDeporteA a2 "Futbol" 99
add2 = entrenarDeporteA ad2 "Handball" 43

a3 = nuevoA "Atleta3" Femenino 1991 "EEUU" 27
ad3 = entrenarDeporteA a3 "Volley" 99

a4 = nuevoA "Atleta4" Masculino 1990 "Holanda" 99
ad4 = entrenarDeporteA a4 "Futbol" 74

c1 = nuevaC "Futbol" Masculino [add1,add2,ad4]
c2 = nuevaC "Handball" Masculino [add1,add2]
c3 = nuevaC "Volley" Femenino [ad3]

cf1 = finalizarC c1 [12, 10] [(12,True),(99,False)]
cf1_prima = finalizarC c1 [10, 12] [(12,True),(99,False)]

test_nuevaC = [c1, c2, c3]

test_categoriaC = [ categoriaC c1, categoriaC c2, categoriaC c3]

test_participantesC = [ participantesC c1, participantesC c2, participantesC c3  ]

test_finalizadaC = [ finalizadaC c1, finalizadaC c2, finalizadaC c3, finalizadaC cf1 ]

test_rankingC = [rankingC cf1]

test_lesTocoControlAntiDopingC = [lesTocoControlAntiDopingC cf1]

test_leDioPositivoC = [(leDioPositivoC cf1 add2) == True, (leDioPositivoC cf1 ad4) == False]

test_finalizarC = [ c1, finalizarC c1 [12, 10] [(12,True),(99,False)]]

test_linfordChristieC = [participantesC c1, participantesC (linfordChristieC c1 add2) ]

test_gananLosMasCapacesC = [(gananLosMasCapacesC cf1) == True, (gananLosMasCapacesC cf1_prima) == False]

test_sancionarTrampososC = [ rankingC cf1,  rankingC (sancionarTrampososC cf1) ]
