module JJOO (JJOO, nuevoJ, anioJ, atletasJ, cantDiasJ, cronogramaJ,
jornadaActualJ,dePaseoJ,medalleroJ,boicotPorDisciplinaJ,losMasFracasadosJ,
liuSongJ,stevenBradburyJ,sequiaOlimpicaJ, transcurrirDiaJ,deportesNoOlimpicosJ,atletaProdigioJ)
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
cantDiasJ (J _ _ _) = 0 
cantDiasJ (NuevoDia competencias jjoo) = 1 + (cantDiasJ jjoo)

cronogramaJ :: JJOO -> Int -> [Competencia]
cronogramaJ (J _ _ _) dia = []
cronogramaJ (NuevoDia competencias jjoo) dia
	|dia == (contarDias (NuevoDia competencias jjoo)) = competencias
	|otherwise = cronogramaJ jjoo dia

jornadaActualJ :: JJOO -> Int 
jornadaActualJ (J _ _ diaActual) = diaActual 
jornadaActualJ (NuevoDia competencias jjoo) = jornadaActualJ jjoo

dePaseoJ :: JJOO -> [Atleta]
dePaseoJ (J _ atletas _) = atletas 
dePaseoJ (NuevoDia competencias jjoo) = buscarAtletasDePaseo (NuevoDia competencias jjoo) (atletasJ (NuevoDia competencias jjoo))

medalleroJ :: JJOO -> [(Pais,[Int])]
medalleroJ (J _ _ _) = []
medalleroJ (jjoo) = ordenar(paisesMedallas (sinRep ( concatenoPaisesGanadores (oroSinRep) (plataSinRep) (bronceSinRep))) (competenciasFinalizadas (todasLasCompetencias (jjoo))))
	where
	oroSinRep=(sinRep(paisesOro (competenciasFinalizadas (todasLasCompetencias (jjoo)))))
	plataSinRep=(sinRep(paisesPlata (competenciasFinalizadas (todasLasCompetencias (jjoo)))))
	bronceSinRep=(sinRep(paisesBronce (competenciasFinalizadas (todasLasCompetencias (jjoo)))))
	
boicotPorDisciplinaJ :: JJOO -> (Deporte, Sexo) -> Pais -> (Int, JJOO)
boicotPorDisciplinaJ (J anio atletas diaActual) (deporte, sexo) p = (0,(J anio atletas diaActual))
boicotPorDisciplinaJ (NuevoDia [] jjoo) (deporte,sexo) p = (0,jjoo)
boicotPorDisciplinaJ (NuevoDia (x:xs) jjoo) (deporte, sexo) p
	|categoriaC x == (deporte,sexo) = ((participantesExtraidos (participantesC x) p), (juegoSinParticipantes jjoo (deporte, sexo) p))
	|otherwise = boicotPorDisciplinaJ jjoo (deporte,sexo) p
	
losMasFracasadosJ::JJOO -> Pais -> [Atleta]
losMasFracasadosJ (J _ _ _) p = []
losMasFracasadosJ (NuevoDia competencias jjoo) p = dameUltraFracasados(dameFracasados losSinPodio) participaronMucho
	where
	losSinPodio = (atletasDelPaisSinPodio(atletasSinPodio(competenciasFinalizadas(todasLasCompetencias (jjoo) )))p)
	participaronMucho = (masParticiparon (atletasRep (todosLosParticipantes (todasLasCompetencias jjoo))) (atletasRep (todosLosParticipantes (todasLasCompetencias jjoo))))

liuSongJ:: JJOO -> Atleta -> Pais -> JJOO
liuSongJ (J anio a diaact) at p = (J anio (igualSalvoPais a at p) diaact)
liuSongJ (NuevoDia competencias jjoo) at p = (NuevoDia (cambioLiu competencias at p) (liuSongJ jjoo at p))

stevenBradburyJ:: JJOO -> Atleta
stevenBradburyJ (J _ _ _) = error "no hay competencias ni medallas"
stevenBradBuryJ (NuevoDia competencias jjoo) = dameElMenosCapaz(minimo (capacidadDeLosQueGanaron)) (capacidadDeLosQueGanaron) 
	where 
	capacidadDeLosQueGanaron = (capacidadDeGanadores( atletasGanadores(competenciasFinalizadas(todasLasCompetencias (jjoo)))))

uyOrdenadoAsiHayUnPatronJ:: JJOO -> Bool
uyOrdenadoAsiHayUnPatronJ (J _ _ _) = True
uyOrdenadoAsiHayUnPatronJ jjoo = (hayPatron (reverso2(listaMejoresPaises jjoo)) (listaPatron (reverso2(listaMejoresPaises jjoo)) (posicion ((reverso2(listaMejoresPaises jjoo))!!0) (tail(reverso2(listaMejoresPaises jjoo))))))

sequiaOlimpicaJ :: JJOO -> [Pais]
sequiaOlimpicaJ jjoo = dameLosMasSecos (cuantoDuraron (paisesJ jjoo) jjoo ) (maximo (cuantoDuraron (paisesJ jjoo) jjoo ))

transcurrirDiaJ :: JJOO -> JJOO
transcurrirDiaJ (J anio atletas diaActual) = (J anio atletas (diaActual + 1))
transcurrirDiaJ (NuevoDia competencias jjoo)
	|jornadaActualJ (NuevoDia competencias jjoo) == (contarDias (NuevoDia competencias jjoo)) =  (NuevoDia (terminarDia (cronogramaJ (NuevoDia competencias jjoo)  (jornadaActualJ jjoo))) (transcurrirDiaJ jjoo))
	|otherwise = (transcurrirDiaJ jjoo)


deportesNoOlimpicosJ :: JJOO -> [Deporte]
deportesNoOlimpicosJ jjoo = juntarDeportes
	where	juntarDeportes = sinRep(buscarDeportesNoOlimp (atletasJ jjoo) (todosLosDeportesJ jjoo (cantDiasJ jjoo)))

atletaProdigioJ :: [JJOO] -> (Deporte,Sexo) -> Atleta
atletaProdigioJ [] _ = error "No hay JJOO"
atletaProdigioJ (js) (dep,sex) = masJoven (minimo(atletasGanadoresDeLaCat js (dep,sex)))(atletasGanadoresDeLaCat js (dep,sex))


--------------AUXILIARES----------------
--------------AUXILIARES NUEVOJ------------
agregarDia :: JJOO -> [[Competencia]] -> JJOO
agregarDia jjoo [] = jjoo
agregarDia jjoo (x:xs) = agregarDia (NuevoDia x jjoo) xs

--------------AUXILIARES CRONOGRAMAJ----------------
contarDias :: JJOO -> Int
contarDias (J _ _ _) = 0
contarDias (NuevoDia competencias jjoo) = 1 + contarDias jjoo

-------------------AUXILIARES EJERCICIO DE PASEO---------------------
buscarAtletasDePaseo :: JJOO -> [Atleta] -> [Atleta]
buscarAtletasDePaseo (J _ _ _) atletas = atletas
buscarAtletasDePaseo (NuevoDia competencias jjoo) atletas = buscarAtletasDePaseo jjoo (fueronAPasear (NuevoDia competencias jjoo) atletas)

fueronAPasear :: JJOO -> [Atleta] -> [Atleta] 
fueronAPasear (J _ [] _) [] = []
fueronAPasear (J _ _ _) []  = []
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
	|otherwise = paisesOro xs
	
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

sinRep::(Eq a) => [a] -> [a]
sinRep [] = []
sinRep (x:xs)
	| x `elem` xs = sinRep xs
	| otherwise = x:sinRep xs
		
concatenoPaisesGanadores:: [Pais] -> [Pais] -> [Pais] -> [Pais]
concatenoPaisesGanadores x y z = x++y++z
	
paisOro :: Pais -> [Competencia] -> Int
paisOro p [] = 0
paisOro p (x:xs)
	| length(rankingC x) > 0 && p == nacionalidadA((rankingC x)!!0) = 1 + paisOro p xs
	| otherwise =  paisOro p xs
	
paisPlata :: Pais -> [Competencia] -> Int
paisPlata p [] = 0
paisPlata p (x:xs)
	| length(rankingC x) > 1 && p == nacionalidadA((rankingC x)!!1) = 1 + paisPlata p xs
	| otherwise =  paisPlata p xs	

paisBronce :: Pais -> [Competencia] -> Int
paisBronce p [] = 0
paisBronce p (x:xs)
	| length(rankingC x) > 2  && p == nacionalidadA((rankingC x)!!2) = 1 + paisBronce p xs
	| otherwise =  paisBronce p xs
		
paisesMedallas :: [Pais] -> [Competencia] -> [(Pais,[Int])]
paisesMedallas [] c = []
paisesMedallas (x:xs) c =(x,[(paisOro x c)]++[(paisPlata x c)]++[(paisBronce  x c)]):paisesMedallas xs c

competenciasFinalizadas :: [Competencia] -> [Competencia]
competenciasFinalizadas [] = []
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
juegoSinParticipantes (NuevoDia competencias jjoo) (deporte, sexo) p
	|(categoriaPertenece competencias (deporte, sexo)) = (NuevoDia (modificarCompetencias competencias (deporte,sexo) p) jjoo)
	|otherwise = (NuevoDia competencias (juegoSinParticipantes jjoo (deporte,sexo) p))

categoriaPertenece :: [Competencia] -> (Deporte, Sexo) -> Bool
categoriaPertenece [] (deporte, sexo) = False
categoriaPertenece (x:xs) (deporte, sexo)
	|categoriaC x == (deporte,sexo) = True
	|otherwise = categoriaPertenece xs (deporte,sexo)

modificarCompetencias :: [Competencia] -> (Deporte,Sexo) -> Pais -> [Competencia]
modificarCompetencias [] (deporte,sexo) p = []
modificarCompetencias (x:xs) (deporte, sexo) p
	|categoriaC x == (deporte, sexo) = (modificarCompetencia x (deporte,sexo) p):xs
	|otherwise = x:(modificarCompetencias xs (deporte, sexo) p)

modificarCompetencia :: Competencia -> (Deporte, Sexo) -> Pais -> Competencia
modificarCompetencia competencia (deporte,sexo) p
	|finalizadaC competencia = finalizarC competencia (listadoEnCiaNumber(quitarParticipantes (rankingC competencia) p)) (sacarlosDelControl (quitarParticipantes (lesTocoControlAntiDopingC competencia) p) competencia)
	|otherwise = nuevaC deporte sexo (quitarParticipantes (participantesC competencia) p)
	
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
	| length(rankingC x) > 3 = losFracasados (rankingC x) 1 ++ (noFinalizaron (participantesC x) (ciaNumbersA (rankingC x))) ++ atletasSinPodio xs
	| otherwise = (noFinalizaron (participantesC x) (ciaNumbersA (rankingC x))) ++ atletasSinPodio xs

noFinalizaron:: [Atleta] -> [Int] -> [Atleta]
noFinalizaron [] _ = []
noFinalizaron (x:xs) ys
	| ciaNumberA x `elem` ys = noFinalizaron xs ys
	| not(ciaNumberA x `elem` ys) = x:(noFinalizaron xs ys) 

losFracasados:: [Atleta] -> Int -> [Atleta]
losFracasados [] _ = []
losFracasados (x:xs) pos 
	| pos == 4 = x:(losFracasados xs (pos +1))
	| pos > 4 = x:(losFracasados xs (pos + 1))
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

todosLosParticipantes:: [Competencia] -> [Atleta]
todosLosParticipantes [] = []
todosLosParticipantes (x:xs) = (participantesC x )++ todosLosParticipantes xs

atletasRep:: [Atleta] -> [(Atleta,Int)]
atletasRep [x] = [(x,1)]
atletasRep (x:xs) = (x,rep1 x (x:xs)):atletasRep xs
	
rep1 :: Atleta -> [Atleta] -> Int	
rep1 x [] = 0
rep1 x (y:ys)
	|ciaNumberA x == ciaNumberA y = 1 + rep1 x ys
	|ciaNumberA x /= ciaNumberA y = 0 + rep1 x ys

masParticiparon:: [(Atleta,Int)] -> [(Atleta,Int)] -> [Atleta]
masParticiparon [] ys = [] 
masParticiparon ((x,xs):xss) ys
	| maximo2 ys (x,xs) = x:masParticiparon xss ys
	|otherwise = masParticiparon xss ys

maximo2::[(Atleta,Int)]->(Atleta,Int) -> Bool
maximo2 [] (y,ys) = True
maximo2 ((x,xs):xss) (y,ys)
	| ys >= xs = maximo2 xss (y,ys)
	|otherwise = False

dameUltraFracasados:: [Atleta] -> [Atleta] -> [Atleta]
dameUltraFracasados [] ys = []
dameUltraFracasados (x:xs) ys
	| ciaNumberA x `elem` ciaNumbersA ys = x:dameUltraFracasados xs ys
	|otherwise= dameUltraFracasados xs ys
	
ciaNumbersA :: [Atleta] -> [Int]
ciaNumbersA [] = []
ciaNumbersA (x:xs) = (ciaNumberA x):(ciaNumbersA xs)

------------------------Auxiliares LiuSong---------------------------------

cambioLiu:: [Competencia] -> Atleta -> Pais -> [Competencia]
cambioLiu [] a p = []
cambioLiu (x:xs) a p 
	|not(finalizadaC x) = (nuevaC (fst(categoriaC x)) (snd(categoriaC x)) (igualSalvoPais (participantesC x) a p)):(cambioLiu xs a p)
	|otherwise = (finalizarC (nuevaC (fst(categoriaC x)) (snd(categoriaC x)) (igualSalvoPais (participantesC x) a p)) ciaNumbersDelRanking ciaNumbersYBoolDeDop ):(cambioLiu xs a p)
	where 
	ciaNumbersDelRanking = (listadoEnCiaNumber2(igualSalvoPais (rankingC x) a p))
	ciaNumbersYBoolDeDop = (listadoEnCiaNumberConDupla(igualSalvoPaisDupla(valoresDeDop (lesTocoControlAntiDopingC x) x) a p))
	
listadoEnCiaNumberConDupla :: [(Atleta,Bool)] -> [(Int,Bool)]
listadoEnCiaNumberConDupla [] = []
listadoEnCiaNumberConDupla ((x,xs):xss) = ((ciaNumberA x),xs):(listadoEnCiaNumberConDupla xss)
		
igualSalvoPaisDupla:: [(Atleta,Bool)] -> Atleta -> Pais -> [(Atleta,Bool)]
igualSalvoPaisDupla [] a p = []
igualSalvoPaisDupla ((x,xs):xss) a p
	| ciaNumberA x ==  ciaNumberA a = ((atletaCambio a p),xs):(igualSalvoPaisDupla xss a p)
	| otherwise = (x,xs):(igualSalvoPaisDupla xss a p)

valoresDeDop:: [Atleta] -> Competencia -> [(Atleta,Bool)] 
valoresDeDop [] _ = []
valoresDeDop (x:xs) c = (x, leDioPositivoC c x):(valoresDeDop xs c)
	
listadoEnCiaNumber2 :: [Atleta] -> [Int]
listadoEnCiaNumber2 [] = []
listadoEnCiaNumber2 (x:xs) = (ciaNumberA x) : listadoEnCiaNumber2 xs 

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

todasLasCompetencias2:: JJOO -> [Competencia]
todasLasCompetencias2 (J _ _ _) = []
todasLasCompetencias2 (NuevoDia competencias jjoo) 
	| length(competencias)==0 = todasLasCompetencias2 jjoo
	| otherwise = (competencias++ todasLasCompetencias jjoo)
	
paisesGanadores:: [Competencia] -> [Pais]
paisesGanadores [] = []
paisesGanadores (x:xs)
	|length (rankingC x) >0 = (nacionalidadA ((rankingC x)!!0)):(paisesGanadores xs)
	|otherwise = paisesGanadores xs
	
mejorPaisRep:: [Pais] -> [(Pais,Int)]
mejorPaisRep [] = []
mejorPaisRep [x] = [(x,1)]
mejorPaisRep (x:xs) = (x,rep x (x:xs)):mejorPaisRep xs
	
rep :: Pais -> [Pais] -> Int	
rep x [] = 0
rep x (y:ys)
	|x == y = 1 + rep x ys
	|x /= y = 0 + rep x ys
	
maximo::[(Pais,Int)]-> Int
maximo [] = 0
maximo [(x,xs)] = xs
maximo ((x,xs):xss) 
	| xs >= maximo xss = xs
	| otherwise = maximo xss

mejorPais:: Int -> [(Pais,Int)] -> Pais
mejorPais _ [] = []
mejorPais num [(x,xs)] = x
mejorPais num ((x,xs):(y,ys):xss)
	| num == xs && xs /= ys = mejorPais num ((x,xs):xss)
	| num == xs && xs == ys && x <= y = mejorPais num ((x,xs):xss)
	| num == xs && xs== ys && x > y = mejorPais num ((y,ys):xss)
	| num /= xs = mejorPais num ((y,ys):xss)

listaMejoresPaises:: JJOO -> [Pais]
listaMejoresPaises (J _ _ _) = []
listaMejoresPaises (NuevoDia competencias jjoo) 
	| length(competencias)== 0 = listaMejoresPaises jjoo
	|hayGanador competencias == False = listaMejoresPaises jjoo
	|otherwise = (mejorPais(maximoPais) (mejorPaisRepetido)):(listaMejoresPaises jjoo)
	where
	maximoPais = (maximo(mejorPaisRep(paisesGanadores(competenciasFinalizadas competencias))))
	mejorPaisRepetido = (mejorPaisRep(paisesGanadores(competenciasFinalizadas competencias)))

hayGanador :: [Competencia] -> Bool
hayGanador [] = False
hayGanador (x:xs)
	| finalizadaC x = True
	| not(finalizadaC x) = hayGanador xs
	
reverso2 :: [Pais] -> [Pais]
reverso2 [] = []
reverso2 (x:xs) = agregarAtras2 x (reverso2 xs)

agregarAtras2::Pais->[Pais]->[Pais]
agregarAtras2 x [] = [x]
agregarAtras2 x (y:ys) = y:(agregarAtras2 x ys) 

posicion:: Pais -> [Pais] -> Int
posicion x [] = 0
posicion x (y:ys)
	| x /= y = 1 + posicion x ys
	| x == y = 1
	
listaPatron :: [Pais] -> Int -> [Pais]
listaPatron [] num = []
listaPatron (x:xs) num
	|num > 0 = x:(listaPatron xs (num-1))
	|num == 0 = []

comparoLista:: [Pais] -> [Pais] -> Bool
comparoLista _ [] = True
comparoLista [] _ = True
comparoLista (x:xs) (y:ys)
	| x==y = comparoLista xs ys
	| not(x==y) = False

eliminarPatron :: [Pais] -> [Pais] -> [Pais]
eliminarPatron [] ys = ys
eliminarPatron (x:xs) (y:ys) = eliminarPatron xs ys

hayPatron:: [Pais] -> [Pais] -> Bool
hayPatron [] listpatro = False
hayPatron [x] listpatro = comparoLista listpatro [x]
hayPatron (x:xs) listpatro
	| length(x:xs) == length(listpatro) = comparoLista listpatro (x:xs)
	| length(x:xs) > length(listpatro) && comparoLista listpatro (x:xs) = hayPatron (eliminarPatron listpatro (x:xs)) listpatro
	| length(x:xs) > length(listpatro) && not(comparoLista listpatro (x:xs)) = False
	| length(x:xs) < length(listpatro) = comparoLista listpatro (x:xs)

------------------------------AUXILIARES SEQUIA OLIMPICA------------------------

dameLosMasSecos:: [(Pais,Int)] -> Int -> [Pais]
dameLosMasSecos [] numseco = []
dameLosMasSecos ((x,xs):xss) numseco
	| xs == numseco = x:dameLosMasSecos xss numseco
	|otherwise = dameLosMasSecos xss numseco

cuantosDiasSinGanar:: Pais -> JJOO -> Int -> [Int]
cuantosDiasSinGanar p (J _ _ _) pos = [pos]
cuantosDiasSinGanar p (NuevoDia competencias jjoo) pos
	| (ganoMedallaEseDia competencias p) == False = cuantosDiasSinGanar p jjoo (pos+1)
	| otherwise = (pos: ( cuantosDiasSinGanar p jjoo 0))

cuantoDuraron:: [Pais] -> JJOO -> [(Pais,Int)]
cuantoDuraron [] jjoo = []
cuantoDuraron (x:xs) jjoo = (x , maxDias(cuantosDiasSinGanar x jjoo 0)): cuantoDuraron xs jjoo
	
maxDias:: [Int] -> Int
maxDias [x] = x
maxDias (x:xs) | x >= maxDias xs = (x)
	|otherwise = maxDias xs

ganoMedallaEseDia :: [Competencia]-> Pais -> Bool
ganoMedallaEseDia [] p = False
ganoMedallaEseDia (x:xs) p
	|finalizadaC x && (length (rankingC x)) >= 1 && (p == nacionalidadA((rankingC x)!!0))  = True
	|finalizadaC x && (length (rankingC x)) >= 2 && (p == nacionalidadA((rankingC x)!!1))  = True
	|finalizadaC x && (length (rankingC x)) >= 3 && (p == nacionalidadA((rankingC x)!!2))  = True
	|otherwise = ganoMedallaEseDia xs p

paisesJ :: JJOO -> [Pais]
paisesJ jjoo = sinRep (paises (atletasJ jjoo))

paises :: [Atleta] -> [Pais]
paises [] = []
paises (x:xs) = nacionalidadA x : paises xs

-------------------------AUXILIARES TRANSCURRIR DIA-----------------------
terminarDia :: [Competencia] -> [Competencia]
terminarDia [] = []
terminarDia (x:xs)
	|finalizadaC x = x : terminarDia xs
	|finalizadaC x == False = (finalizarC x ranking doping) : terminarDia xs
	where
		ranking = listadoEnCiaNumber3(ordenarPorCapacidad (listaCapacidades (participantesC x) x))
		doping = (crearControlAntiDoping ranking)

listaCapacidades :: [Atleta] -> Competencia -> [(Atleta,Int)]
listaCapacidades [] _ = []
listaCapacidades (x:xs) competencia = (x,capacidadA x (fst (categoriaC competencia))) : listaCapacidades xs competencia

ordenarPorCapacidad::[(Atleta,Int)]->[(Atleta,Int)]
ordenarPorCapacidad [] = []
ordenarPorCapacidad (xss) = (maximo3 xss):(ordenarPorCapacidad xssSinMax)
	where xssSinMax = sacarUnaAparicion2 (maximo3 xss) xss

maximo3::[(Atleta,Int)]->(Atleta,Int)
maximo3 [(x,xs)] = (x,xs)
maximo3 ((x,xs):xss) | xs >= snd(maximo3 xss) = (x,xs)
	|otherwise = maximo3 xss

sacarUnaAparicion2:: (Atleta,Int)->[(Atleta,Int)]->[(Atleta,Int)]
sacarUnaAparicion2 (y,(ys)) ((x,(xs)):xss)
	| ciaNumberA x== ciaNumberA y = xss
	| otherwise = (x,(xs)):(sacarUnaAparicion2 (y,(ys)) xss)

listadoEnCiaNumber3 :: [(Atleta,Int)] -> [Int]
listadoEnCiaNumber3 [] = []
listadoEnCiaNumber3 ((x,xs):xss) = (ciaNumberA x) : listadoEnCiaNumber3 xss 	
	
crearControlAntiDoping :: [Int] -> [(Int,Bool)]
crearControlAntiDoping [] = []
crearControlAntiDoping (x:xs) = [(x, False)]

----------------------------------------------DEPORTES NO OLIMPICOS J------------------
buscarDeportesNoOlimp :: [Atleta] -> [Deporte] -> [Deporte]
buscarDeportesNoOlimp [] deportes = []
buscarDeportesNoOlimp (x:xs) deportes = (deportesDistintos (deportesA x) deportes) ++ buscarDeportesNoOlimp xs deportes

deportesDistintos :: [Deporte] -> [Deporte] -> [Deporte]
deportesDistintos [] xs = []
deportesDistintos (x:xs) ys
	|not(x `elem` ys) = x : deportesDistintos xs ys
	|otherwise = deportesDistintos xs ys

todosLosDeportesJ :: JJOO -> Int -> [Deporte]
todosLosDeportesJ jjoo 0 = []
todosLosDeportesJ jjoo x = transformarADeporte (cronogramaJ jjoo x) ++ todosLosDeportesJ jjoo (x-1)

transformarADeporte :: [Competencia] -> [Deporte]
transformarADeporte [] = []
transformarADeporte (x:xs) = fst (categoriaC x) : transformarADeporte xs

--------------------------------------- AuxiliaresAtletaProdigioJ-----------------------------

minimo2::[(Atleta,Int)]->Int
minimo2 [(x,xs)] = xs
minimo2 ((x,xs):xss) 
	| xs <= minimo2 xss = xs
	|otherwise = minimo2 xss

masJoven:: Int -> [(Atleta,Int)] -> Atleta
masJoven y [(x,xs)] = x
masJoven y ((x,xs):xss)
	| y == xs = x
	| otherwise = masJoven y xss

atletasGanadoresDeLaCat:: [JJOO] -> (Deporte,Sexo) -> [(Atleta,Int)]
atletasGanadoresDeLaCat [] _ = []
atletasGanadoresDeLaCat (j:js) (dep,sex) = (atletaGanadorConEdad(competenciasFinalizadas (todasLasCompetencias j)) (dep,sex) (anioJ j))++(atletasGanadoresDeLaCat js (dep,sex))

atletaGanadorConEdad:: [Competencia] -> (Deporte,Sexo) -> Int -> [(Atleta,Int)]
atletaGanadorConEdad [] (dep,sex) anio = []
atletaGanadorConEdad (x:xs) (dep,sex) anio
	| categoriaC x == (dep,sex) && length(rankingC x) >0 = ((rankingC x)!!0, anio - anioNacimientoA ((rankingC x)!!0)):atletaGanadorConEdad xs (dep,sex) anio
	|otherwise = atletaGanadorConEdad xs (dep,sex) anio

------------------------------------------------ TESTING ------------------------------------------------

a1 = nuevoA "Atleta1" Masculino 1989 "Argentina" 10
ad1 = entrenarDeporteA a1 "Futbol" 54
add1 = entrenarDeporteA ad1 "Handball" 12
addd1 = entrenarDeporteA add1 "Volley" 33

a2 = nuevoA "Atleta2" Masculino 1990 "Holanda" 12
ad2 = entrenarDeporteA a2 "Futbol" 99
add2 = entrenarDeporteA ad2 "Handball" 43
addd2 = entrenarDeporteA add2 "Volley" 28

a3 = nuevoA "Atleta3" Femenino 1991 "EEUU" 27
ad3 = entrenarDeporteA a3 "Volley" 99

a4 = nuevoA "Atleta4" Masculino 1990 "Holanda" 99
ad4 = entrenarDeporteA a4 "Futbol" 74

a5 = nuevoA "Atleta5" Masculino 1990 "Peru" 90
ad5 = entrenarDeporteA a5 "Futbol" 74

a6 = nuevoA "Atleta6" Masculino 1990 "Peru" 93
ad6 = entrenarDeporteA a6 "Futbol" 74

a7 = nuevoA "Atleta7" Masculino 1970 "Japon" 22
ad7 = entrenarDeporteA a7 "Futbol" 74

c1 = nuevaC "Futbol" Masculino [ad7,add2,addd1]
c2 = nuevaC "Handball" Masculino [add1,add2]
c3 = nuevaC "Volley" Femenino [ad3]

cf1 = finalizarC c1 [12,22,10] [(99,False)]
cf2 = finalizarC c1 [10,12] [(12,True),(99,False)]
cf3 = finalizarC c2 [10,12] [(99,False)]
cf1_prima = finalizarC c1 [12,99] [(99,False)]

j2 = nuevoJ 2012 [add1, add2, ad3, ad4,ad5,ad6] [[cf1,cf1,cf1_prima,cf1_prima]]

j3 = nuevoJ 2012 [addd1, add2, ad3, ad4,ad5,ad6] [[],[cf1,cf2,cf2,c3],[cf2],[c1],[cf1],[cf2],[]]

j4 = nuevoJ 2010 [add1, add2,ad7] [[cf1],[cf2],[cf1],[cf1]]

j5 = nuevoJ 2010 [add1, addd2,ad7] [[cf1,cf1,cf2],[cf2],[],[c1],[c2],[cf1,cf2,cf2]]

j6 = nuevoJ 2012 [add1,addd2,ad7] [[cf1],[cf2],[cf1],[cf2],[c1]]
