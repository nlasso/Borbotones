module JJOO (JJOO, nuevoJ, anioJ, atletasJ, cantDiasJ, cronogramaJ,
jornadaActualJ,dePaseoJ,medalleroJ,boicotPorDisciplinaJ,losMasFracasadosJ,
liuSongJ,stevenBradburyJ,sequiaOlimpicaJ,transcurrirDiaJ)
where

import Tipos
import Atleta
import Competencia


data JJOO = J Int [Atleta] Int | NuevoDia [Competencia] JJOO deriving (Show)

nuevoJ :: Int -> [Atleta] -> [[Competencia]] -> JJOO
nuevoJ anio atletas comp = agregarDia (J anio atletas 1) comp

anioJ :: JJOO -> Int 
anioJ (J anio _ _) = anio
anioJ (NuevoDia _ jjoo) = anioJ jjoo

atletasJ :: JJOO -> [Atleta]
atletasJ (J _ atletas _) = atletas 
atletasJ (NuevoDia _ jjoo) = atletasJ jjoo

cantDiasJ :: JJOO -> Int
cantDiasJ (J _ _ _) = 1 
cantDiasJ (NuevoDia competencias jjoo) = 1 + (cantDiasJ jjoo)

cronogramaJ :: JJOO -> Int -> [Competencia]
cronogramaJ jjoo dia
	| dia < 1 || dia > (cantDiasJ jjoo) = error "El dia no esta contemplado"
cronogramaJ (NuevoDia competencias jjoo) dia
	|dia == (cantDiasJ jjoo) = competencias
cronogramaJ (NuevoDia competencias jjoo) dia = buscaDia jjoo (dia-1) 


jornadaActualJ :: JJOO -> Int 
jornadaActualJ (J _ _ diaActual) = diaActual 
jornadaActualJ (NuevoDia competencias jjoo) = jornadaActualJ jjoo

dePaseoJ :: JJOO -> [Atleta]
dePaseoJ (J anio atletas diaActual) = fueronAPasear (J anio atletas diaActual)  atletas
dePaseoJ (NuevoDia competencias jjoo) = dePaseoJ jjoo

medalleroJ :: JJOO -> [(Pais,[Int])]
medalleroJ (J _ _ _) = []
medalleroJ (NuevoDia competencias jjoo) = ordenar(paisesMedallas (paisesGanadoresSinRep ( concatenoPaisesGanadores (oroSinRep) (plataSinRep) (bronceSinRep))) (competenciasFinalizadas (todasLasCompetencias jjoo)))
	where
	oroSinRep=(paisesOroSinRep(paisesOro (competenciasFinalizadas (todasLasCompetencias jjoo))))
	plataSinRep=(paisesPlataSinRep(paisesPlata (competenciasFinalizadas (todasLasCompetencias jjoo))))
	bronceSinRep=(paisesBronceSinRep(paisesBronce (competenciasFinalizadas (todasLasCompetencias jjoo))))
	
boicotPorDisciplinaJ :: JJOO -> (Deporte, Sexo) -> Pais -> (Int, JJOO)
boicotPorDisciplinaJ (J anio atletas diaActual) (deporte, sexo) p = (0,(J anio atletas diaActual))
boicotPorDisciplinaJ (NuevoDia (x:xs) jjoo) (deporte, sexo) p
	|categoriaC x == (deporte,sexo) = ((participantesExtraidos (participantesC x) p), (juegoSinParticipantes jjoo (deporte, sexo) p))

losMasFracasadosJ::JJOO -> Pais -> [Atleta]
losMasFracasadosJ (J _ _ _) p = []
losMasFracasadosJ (NuevoDia competencias jjoo) p = dameFracasados(atletasDelPaisSinPodio(atletasSinPodio(competenciasFinalizadas(todasLasCompetencias (jjoo) )))p)

liuSongJ:: JJOO -> Atleta -> Pais -> JJOO
liuSongJ (J anio a diaact) at p = (J anio (igualSalvoPais a at p) diaact)
liuSongJ (NuevoDia competencias jjoo) at p = (NuevoDia (cambioLiu(todasLasCompetencias (jjoo)) at p) jjoo)

stevenBradburyJ:: JJOO -> Atleta
stevenBradburyJ (J _ _ _) = error "no hay competencias ni medallas"
stevenBradBuryJ (NuevoDia competencias jjoo) = dameElMenosCapaz(minimo(capacidadDeGanadores( atletasGanadores(competenciasFinalizadas(todasLasCompetencias (jjoo)))))) (capacidadDeGanadores( atletasGanadores(competenciasFinalizadas(todasLasCompetencias (jjoo))))) 

uyOrdenadoAsiHayUnPatronJ:: JJOO -> Bool
uyOrdenadoAsiHayUnPatronJ (J _ _ _) = error "No hay competencias que comparar para obtener patron"
uyOrdenadoAsiHayUnPatronJ (NuevoDia competencias jjoo) = (hayPatron(listaMejoresPaises jjoo) (listaPatron (listaMejoresPaises jjoo) (posicion (listaMejoresPaises jjoo!!0) (tail(listaMejoresPaises jjoo)))))

sequiaOlimpicaJ :: JJOO -> [Pais]
sequiaOlimpicaJ jjoo = secosOlimpicos (paisesJ jjoo) jjoo

transcurrirDiaJ :: JJOO -> JJOO
transcurrirDiaJ (J anio atletas diaActual) = (J anio atletas (diaActual + 1))
transcurrirDiaJ (NuevoDia compentencias jjoo) = (NuevoDia (terminarDia (cronogramaJ jjoo  (jornadaActualJ jjoo))) jjoo)



--------------AUXILIARES----------------
--------------AUXILIARES NUEVOJ------------
agregarDia :: JJOO -> [[Competencia]] -> JJOO
agregarDia jjoo [] = jjoo
agregarDia jjoo (x:xs) = agregarDia (NuevoDia x jjoo) xs

--------------AUXILIARES CRONOGRAMAJ----------------
buscaDia :: JJOO -> Int -> [Competencia]
buscaDia (NuevoDia competencias jjoo) dia
	| dia == 1 = competencias
	| dia > 1 = buscaDia jjoo (dia-1)
-------------------AUXILIARES EJERCICIO DE PASEO---------------------
fueronAPasear :: JJOO -> [Atleta] -> [Atleta] 
fueronAPasear (J _ [] _) [] = []
fueronAPasear (NuevoDia competencias jjoo) [] = []
fueronAPasear (NuevoDia competencias jjoo) (x:xs)
	|(atletaNoPertenece competencias x) = x : fueronAPasear (NuevoDia competencias jjoo) xs
	|(atletaNoPertenece competencias x) == False = fueronAPasear (NuevoDia competencias jjoo) xs

atletaNoPertenece :: [Competencia] -> Atleta-> Bool
atletaNoPertenece [] atleta = True
atletaNoPertenece (x:xs) atleta
	|(compararAtleta atleta (participantesC x)) == False = atletaNoPertenece xs atleta
	|(compararAtleta atleta (participantesC x)) = False

compararAtleta :: Atleta -> [Atleta] -> Bool
compararAtleta atleta [] = False
compararAtleta atleta (x:xs)
	|ciaNumberA atleta == ciaNumberA x = True
	|ciaNumberA atleta /= ciaNumberA x = compararAtleta atleta xs


----------------------AUXILIARES EJERCICIO MEDALLERO---------------

paisesOro:: [Competencia] -> [Pais]
paisesOro [] = []
paisesOro (x:xs)
	|length (rankingC x) >0 = (nacionalidadA ((rankingC x)!!0)):(paisesOro xs)
	
paisesPlata:: [Competencia] -> [Pais]
paisesPlata [] = []
paisesPlata (x:xs)
	|length (rankingC x) >1 = (nacionalidadA ((rankingC x)!!1)):(paisesPlata xs)
	|otherwise = paisesPlata xs
	
paisesBronce:: [Competencia] -> [Pais]
paisesBronce [] = []
paisesBronce (x:xs)
	|length (rankingC x) >2 = (nacionalidadA ((rankingC x)!!2)):(paisesBronce xs)
	|otherwise = paisesBronce xs

paisesOroSinRep:: [Pais] -> [Pais]
paisesOroSinRep [] = []
paisesOroSinRep (x:xs)
	| x `elem` xs = paisesOroSinRep xs
	| otherwise = x:paisesOroSinRep xs
	
paisesPlataSinRep:: [Pais] -> [Pais]
paisesPlataSinRep [] = []
paisesPlataSinRep (x:xs)
	| x `elem` xs = paisesPlataSinRep xs
	| otherwise = x:paisesPlataSinRep xs
	
paisesBronceSinRep:: [Pais] -> [Pais]
paisesBronceSinRep [] = []
paisesBronceSinRep (x:xs)
	| x `elem` xs = paisesOroSinRep xs
	| otherwise = x:paisesOroSinRep xs
	
concatenoPaisesGanadores:: [Pais] -> [Pais] -> [Pais] -> [Pais]
concatenoPaisesGanadores [] [] [] = []
concatenoPaisesGanadores x [] [] = x
concatenoPaisesGanadores [] y [] = y
concatenoPaisesGanadores [] [] z = z
concatenoPaisesGanadores x y [] = x++y
concatenoPaisesGanadores [] y z = y++z
concatenoPaisesGanadores x [] z = x++z
concatenoPaisesGanadores x y z = x++y++z

paisesGanadoresSinRep :: [Pais] -> [Pais]
paisesGanadoresSinRep [] = []
paisesGanadoresSinRep (x:xs)
	| x `elem`xs = paisesGanadoresSinRep xs
	| otherwise = x:paisesGanadoresSinRep xs
	
paisOro :: Pais -> [Competencia] -> Int
paisOro p [] = 0
paisOro p (x:xs)
	| p == nacionalidadA((rankingC x)!!0) && length(rankingC x) > 0 = 1 + paisOro p xs
	| otherwise = 0 + paisOro p xs
	
paisPlata :: Pais -> [Competencia] -> Int
paisPlata p [] = 0
paisPlata p (x:xs)
	| p == nacionalidadA((rankingC x)!!1) && length(rankingC x) > 1 = 1 + paisPlata p xs
	| otherwise = 0 + paisPlata p xs	

paisBronce :: Pais -> [Competencia] -> Int
paisBronce p [] = 0
paisBronce p (x:xs)
	| p == nacionalidadA((rankingC x)!!2) && length(rankingC x) > 0 = 1 + paisBronce p xs
	| otherwise = 0 + paisBronce p xs
		
paisesMedallas :: [Pais] -> [Competencia] -> [(Pais,[Int])]
paisesMedallas [] c = []
paisesMedallas (x:xs) c =(x,(paisOro x c):(paisPlata x c):[(paisBronce  x c)]):paisesMedallas xs c

competenciasFinalizadas :: [Competencia] -> [Competencia]
compentenciasFinalizadas [] = []
competenciasFinalizadas (x:xs)
	| finalizadaC x = x:(competenciasFinalizadas xs)
	| not(finalizadaC x) = (competenciasFinalizadas xs)
	
todasLasCompetencias:: JJOO -> [Competencia]
todasLasCompetencias (J _ _ _) = []
todasLasCompetencias (NuevoDia competencias jjoo) = (competencias++ todasLasCompetencias jjoo)

ordenar::[(Pais,[Int])]->[(Pais,[Int])]
ordenar [] = []
ordenar (xss) = (maximo1 xss):(ordenar xssSinMinimo)
	where xssSinMinimo = sacarUnaAparicion (maximo1 xss) xss
maximo1::[(Pais,[Int])]->(Pais,[Int])
maximo1 [(x,(xs))] = (x,(xs))
maximo1 ((x,(xs)):xss) | xs >= snd(maximo1 xss) = (x,(xs))
	|otherwise = maximo1 xss
sacarUnaAparicion:: (Pais,[Int])->[(Pais,[Int])]->[(Pais,[Int])]
sacarUnaAparicion (y,(ys)) ((x,(xs)):xss)
	| x==y = xss
	| otherwise = (x,(xs)):(sacarUnaAparicion (y,(ys)) xss)

----------------------AUXILIARES EJERICICIO BOICOT POR DISCIPLINA---------------
participantesExtraidos :: [Atleta] -> Pais -> Int
participantesExtraidos [] p = 0
participantesExtraidos (x:xs) p
	|nacionalidadA x == p = 1 + (participantesExtraidos xs p)
	|nacionalidadA x /= p = participantesExtraidos xs p

juegoSinParticipantes :: JJOO -> (Deporte, Sexo) -> Pais -> JJOO
juegoSinParticipantes (J anio atletas diaActual) (deporte, sexo) p = (J anio atletas diaActual)
juegoSinParticipantes (NuevoDia compentencias jjoo) (deporte, sexo) p
	|(categoriaPertenece compentencias (deporte, sexo)) = (NuevoDia (modificarCompetencias compentencias (deporte,sexo) p) jjoo)
	|otherwise = (NuevoDia compentencias (juegoSinParticipantes jjoo (deporte,sexo) p))

categoriaPertenece :: [Competencia] -> (Deporte, Sexo) -> Bool
categoriaPertenece [] (deporte, sexo) = True
categoriaPertenece (x:xs) (deporte, sexo)
	|categoriaC x == (deporte,sexo) = True
	|otherwise = categoriaPertenece xs (deporte,sexo)

modificarCompetencias :: [Competencia] -> (Deporte,Sexo) -> Pais -> [Competencia]
modificarCompetencias [] (deporte,sexo) p = []
modificarCompetencias (x:xs) (deporte, sexo) p
	|categoriaC x == (deporte, sexo) = (modificarCompetencia x (deporte,sexo) p):xs
	|otherwise = x:(modificarCompetencias xs (deporte, sexo) p)

modificarCompetencia :: Competencia -> (Deporte, Sexo) -> Pais -> Competencia
modificarCompetencia competencia (deporte,sexo) p = nuevaC deporte sexo (quitarParticipantes (participantesC competencia) p)
modificarCompetencia competencia (deporte,sexo) p
	|finalizadaC competencia = finalizarC competencia (listadoEnCiaNumber(quitarParticipantes (rankingC competencia) p)) (sacarlosDelControl (quitarParticipantes (lesTocoControlAntiDopingC competencia) p) competencia)

quitarParticipantes :: [Atleta] -> Pais -> [Atleta]
quitarParticipantes [] p = []
quitarParticipantes (x:xs) p 
	|nacionalidadA x == p = quitarParticipantes xs p
	|otherwise = x:(quitarParticipantes xs p)

listadoEnCiaNumber :: [Atleta] -> [Int]
listadoEnCiaNumber [] = []
listadoEnCiaNumber (x:xs) = (ciaNumberA x) : listadoEnCiaNumber xs 

sacarlosDelControl :: [Atleta] -> Competencia -> [(Int,Bool)]
sacarlosDelControl [] c = []
sacarlosDelControl (x:xs) c = (ciaNumberA x, leDioPositivoC c x):sacarlosDelControl xs c

----------------------AUXILIARES LOSMASFRACASADOSJ------------------------------

atletasSinPodio:: [Competencia] -> [Atleta]
atletasSinPodio [] = []
atletasSinPodio (x:xs)
	| length(rankingC x) > 3 = losFracasados (rankingC x) 1 ++ atletasSinPodio xs
	| otherwise = atletasSinPodio xs
	
losFracasados:: [Atleta] -> Int -> [Atleta]
losFracasados [] _ = []
losFracasados (x:xs) pos 
	| pos == 4 = (x):(losFracasados xs (pos +1))
	| pos > 4 = (x):(losFracasados xs (pos + 1))
	| otherwise = losFracasados xs (pos + 1)

atletasDelPaisSinPodio:: [Atleta] -> Pais -> [Atleta]
atletasDelPaisSinPodio [] _ = []
atletasDelPaisSinPodio (x:xs) p
	| nacionalidadA x == p = x:(atletasDelPaisSinPodio xs p)
	| otherwise = atletasDelPaisSinPodio xs p

dameFracasados::[Atleta] -> [Atleta]
dameFracasados [] = []
dameFracasados (x:xs)
	| compararAtleta x xs = dameFracasados xs
	| otherwise = x:dameFracasados xs


------------------------Auxiliares LiuSong---------------------------------

cambioLiu:: [Competencia] -> Atleta -> Pais -> [Competencia]
cambioLiu [] a p = []
cambioLiu (x:xs) a p = (nuevaC (fst(categoriaC x)) (snd(categoriaC x)) (igualSalvoPais (participantesC x) a p)):(cambioLiu xs a p)
	
igualSalvoPais:: [Atleta] -> Atleta -> Pais -> [Atleta]
igualSalvoPais [] a p = []
igualSalvoPais (x:xs) a p
	| ciaNumberA x ==  ciaNumberA a = (atletaCambio a p):(igualSalvoPais xs a p)
	| otherwise = x:(igualSalvoPais xs a p)

atletaCambio:: Atleta -> Pais -> Atleta
atletaCambio a p = entrenandoAtleta (nuevoA (nombreA a) (sexoA a) (anioNacimientoA a) p (ciaNumberA a) ) (juntandoCapacidad a (deportesA a))

juntandoCapacidad:: Atleta -> [Deporte] -> [(Deporte,Int)]
juntandoCapacidad a [] = []
juntandoCapacidad a (x:xs) = (x,capacidadA a x):(juntandoCapacidad a xs)

entrenandoAtleta:: Atleta -> [(Deporte,Int)] -> Atleta 
entrenandoAtleta a [] = a
entrenandoAtleta a ((x,xs):xss) = (entrenandoAtleta (entrenarDeporteA a x xs) xss)
	
--------------------------Auxiliares StevenBradbury-------------------	
	
atletasGanadores:: [Competencia] -> [(Atleta,(Deporte,Sexo))]
atletasGanadores [] = []
atletasGanadores (x:xs)
	| length(rankingC x)>0 = ((rankingC x)!!0, (categoriaC x)):atletasGanadores xs
	| otherwise = atletasGanadores xs
	
capacidadDeGanadores:: [(Atleta,(Deporte,Sexo))] -> [(Atleta, Int)]
capacidadDeGanadores [] = []
capacidadDeGanadores ((x,(xs,xss)):xsss)
	| capacidadA x xs > 0 = (x,capacidadA x xs):(capacidadDeGanadores xsss)
	| otherwise =(capacidadDeGanadores xsss)
	
minimo::[(Atleta,Int)]->Int
minimo [(x,xs)] = xs
minimo ((x,xs):xss) 
	| xs <= minimo xss = xs
	|otherwise = minimo xss

dameElMenosCapaz:: Int -> [(Atleta,Int)] -> Atleta
dameElMenosCapaz y [(x,xs)] = x
dameElMenosCapaz y ((x,xs):xss)
	| y == xs = x
	| otherwise = dameElMenosCapaz y xss

----------------------------Auxiliares uyOrdenadoAsiHayUnPatron-----------------
paisesGanadores:: [Competencia] -> [Pais]
paisesGanadores [] = []
paisesGanadores (x:xs)
	|length (rankingC x) >0 = (nacionalidadA ((rankingC x)!!0)):(paisesGanadores xs)
	
mejorPaisRep:: [Pais] -> [(Pais,Int)]
mejorPaisRep [x] = [(x,1)]
mejorPaisRep (x:xs) = (x,rep x (x:xs)):mejorPaisRep xs
	
rep :: Pais -> [Pais] -> Int	
rep x [] = 0
rep x (y:ys)
	|x == y = 1 + rep x ys
	|x /= y = 0 + rep x ys
	
maximo::[(Pais,Int)]-> Int
maximo [(x,xs)] = xs
maximo ((x,xs):xss) 
	| xs >= maximo xss = xs
	| otherwise = maximo xss

mejorPais:: Int -> [(Pais,Int)] -> Pais
mejorPais num [(x,xs)] = x
mejorPais num ((x,xs):(y,ys):xss)
	| num == xs && xs /= ys = mejorPais num ((x,xs):xss)
	| num == xs && xs == ys && x < y = mejorPais num ((x,xs):xss)
	| num == xs && xs== ys && x > y = mejorPais num ((y,ys):xss)
	| num /= xs = mejorPais num ((y,ys):xss)

listaMejoresPaises:: JJOO -> [Pais]
listaMejorespaises (J _ _ _) = []
listaMejoresPaises (NuevoDia competencias jjoo) = (mejorPais(maximo(mejorPaisRep(paisesGanadores(competenciasFinalizadas competencias))))(mejorPaisRep(paisesGanadores(competenciasFinalizadas competencias)))):(listaMejoresPaises jjoo)

posicion:: Pais -> [Pais] -> Int
posicion x (y:ys)
	| x /= y = 1 + posicion x ys
	| x == y = 1
	
listaPatron :: [Pais] -> Int -> [Pais]
listaPatron [] num = []
listaPatron (x:xs) num
	|num > 0 = x:(listaPatron xs (num-1))
	|num == 0 = []

comparoLista:: [Pais] -> [Pais] -> Bool
comparoLista [] _ = True
comparoLista (x:xs) (y:ys)
	| x==y = comparoLista xs ys
	| not(x==y) = False


eliminarPatron :: [Pais] -> [Pais] -> [Pais]
eliminarPatron [] ys = ys
eliminarPatron (x:xs) (y:ys)
	| x == y = eliminarPatron xs ys
	| x/= y = []

hayPatron:: [Pais] -> [Pais] -> Bool
hayPatron [] listpatro = False
hayPatron (x:xs) listpatro
	| length(x:xs) == length(listpatro) = comparoLista (x:xs) listpatro
	| length(x:xs) > length(listpatro) =hayPatron (eliminarPatron listpatro (x:xs)) listpatro
	| length(x:xs) < length(listpatro) = comparoLista (x:xs) listpatro

------------------------------AUXILIARES SEQUIA OLIMPICA------------------------

secosOlimpicos :: [Pais] -> JJOO -> [Pais]
secosOlimpicos [] jjoo = []
secosOlimpicos (x:xs) jjoo
	|total jjoo x == maxDiasSinMedallas jjoo = x : secosOlimpicos xs jjoo
	|otherwise = secosOlimpicos xs jjoo

maxDiasSinMedallas :: JJOO -> Int
maxDiasSinMedallas jjoo = maximoInt(todosLosPaisesYMedallas (paisesJ jjoo) jjoo)

todosLosPaisesYMedallas :: [Pais] -> JJOO -> [Int]
todosLosPaisesYMedallas [] jjoo = []
todosLosPaisesYMedallas (x:xs) jjoo = (total jjoo x) : todosLosPaisesYMedallas xs jjoo 

maximoInt :: [Int] -> Int
maximoInt [x] = x
maximoInt (x:xs)
	|x >= maximoInt xs = x
	|otherwise = maximoInt xs

maxDif :: [Int] -> [Int]
maxDif [] = []
maxDif [x] = []
maxDif (x:y:xs) = (y-x): maxDif (y:xs)

total :: JJOO -> Pais -> Int
total jjoo p = maximoInt(maxDif(reverso(masDiasSinMedallas jjoo p)))

masDiasSinMedallas :: JJOO -> Pais -> [Int]
masDiasSinMedallas (J _ _ _) p = [0]
masDiasSinMedallas (NuevoDia compentencias jjoo) p
	|ganoMedallaEseDia compentencias p =  jornadaActualJ(NuevoDia compentencias jjoo) : masDiasSinMedallas jjoo p
	|otherwise = masDiasSinMedallas jjoo p

ganoMedallaEseDia :: [Competencia]-> Pais -> Bool
ganoMedallaEseDia [] p = False
ganoMedallaEseDia (x:xs) p
	|finalizadaC x && (p == nacionalidadA((rankingC x)!!0) || (p == nacionalidadA((rankingC x)!!1)) || (p == nacionalidadA((rankingC x)!!2))) = True
	|otherwise = ganoMedallaEseDia xs p

paisesJ :: JJOO -> [Pais]
paisesJ jjoo = paisesSinRepetidos (paises (atletasJ jjoo))

paises :: [Atleta] -> [Pais]
paises [] = []
paises (x:xs) = nacionalidadA x : paises xs

paisesSinRepetidos :: [Pais] -> [Pais]
paisesSinRepetidos [] = []
paisesSinRepetidos (x:xs) = x : paisesSinRepetidos(extraerRepetidos x xs)

extraerRepetidos :: Pais -> [Pais] -> [Pais]
extraerRepetidos p [] = []
extraerRepetidos p (x:xs)
	|p == x = extraerRepetidos p xs
	|p /= x = x : extraerRepetidos p xs

reverso :: [Int] -> [Int]
reverso [] = []
reverso (x:xs) = agregarAtras x (reverso xs)

agregarAtras::Int->[Int]->[Int]
agregarAtras x [] = [x]
agregarAtras x (y:ys) = y:(agregarAtras x ys) 

-------------------------AUXILIARES TRANSCURRIR DIA-----------------------
terminarDia :: [Competencia] -> [Competencia]
terminarDia [] = []
terminarDia (x:xs)
	|finalizadaC x = x : terminarDia xs
	|finalizadaC x == False = (finalizarC x ranking doping) : terminarDia xs
	where
		ranking = listadoEnCiaNumber(ordenarPorCapacidad (listaCapacidades (participantesC x) x)(participantesC x) x )
		doping = (crearControlAntiDoping ranking)

listaCapacidades :: [Atleta] -> Competencia -> [Int]
listaCapacidades [] _ = []
listaCapacidades (x:xs) competencia = capacidadA x (fst (categoriaC competencia)) : listaCapacidades xs competencia

ordenarPorCapacidad :: [Int] -> [Atleta] -> Competencia -> [Atleta]
ordenarPorCapacidad [] atletas competencia = []
ordenarPorCapacidad xs atletas competencia = (devolverAtleta (maximoInt xs) atletas competencia) : (ordenarPorCapacidad xs (quitarAtleta atletas (devolverAtleta (maximoInt xs) atletas competencia)) competencia)

devolverAtleta :: Int -> [Atleta] -> Competencia -> Atleta
devolverAtleta capacidad [] competencia = error "Esa capacidad no está contemplada"
devolverAtleta capacidad (x:xs) competencia
	|(capacidadA x (fst(categoriaC competencia))) == capacidad = x
	|otherwise = devolverAtleta capacidad xs competencia

quitarAtleta :: [Atleta] -> Atleta -> [Atleta]
quitarAtleta [] atleta = []
quitarAtleta (x:xs) atleta
	|ciaNumberA x == ciaNumberA atleta = quitarAtleta xs atleta
	|otherwise = x : quitarAtleta xs atleta

crearControlAntiDoping :: [Int] -> [(Int,Bool)]
crearControlAntiDoping [] = []
crearControlAntiDoping (x:xs) = [(x, False)]
