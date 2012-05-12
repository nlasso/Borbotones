module JJOO (JJOO, nuevoJ, anioJ, atletasJ, cantDiasJ, cronogramaJ,
jornadaActualJ,medalleroJ)
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
medalleroJ (NuevoDia competencias jjoo) = paisesMedallas ( paisesGanadoresSinRep ( concatenoPaisesGanadores (paisesOroSinRep (paisesOro (competenciasFinalizadas (todasLasCompetencias jjoo)))) (paisesPlataSinRep(paisesPlata (competenciasFinalizadas (todasLasCompetencias jjoo)))) (paisesBronceSinRep(paisesBronce (competenciasFinalizadas (todasLasCompetencias jjoo)))))) (competenciasFinalizadas (todasLasCompetencias jjoo))

boicotPorDisciplinaJ :: JJOO -> (Deporte, Sexo) -> Pais -> (Int, JJOO)
boicotPorDisciplinaJ (J anio atletas diaActual) (deporte, sexo) p = (0,(J anio atletas diaActual))
boicotPorDisciplinaJ (NuevoDia (x:xs) jjoo) (deporte, sexo) p
	|categoriaC x == (deporte,sexo) = ((participantesExtraidos (participantesC x) p), (juegoSinParticipantes jjoo (deporte, sexo) p))

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
	|categoriaC x == (deporte, sexo) = (modificarCompetencia x p):xs
	|otherwise = x:(modificarCompetencias xs (deporte, sexo) p)

modificarCompetencia :: Competencia -> Pais -> Competencia
modificarCompetencia (Finalizar ranking doping competencia) p = Finalizar (quitarDelRanking ranking p (participantesC competencia)) (quitarParticipantes doping p) (Participar ((quitarParticipantes (participantesC competencia) p) (C categoriaC(competencia))))
modificarCompetencia (Participar participantes competencia) p = Participar ((quitarParticipantes participantes p) (C categoriaC(competencia))) 
modificarCompetencia C categoria = C categoria

quitarParticipantes :: [Atleta] -> Pais -> [Atleta]
quitarParticipantes [] p = []
quitarParticipantes (x:xs) p 
	|nacionalidadA x == p = quitarParticipantes xs p
	|otherwise = x:(quitarParticipantes xs p)

quitarDelRanking :: [Int] -> Pais -> [Atleta] -> [Int]
quitarDelRanking [] p atletas = []
quitarDelRanking (x:xs) p (y:ys)
	|nacionalidadA x == p = (ciaNumberA x): quitarDelRanking xs p
	|otherwise = quitarDelRanking xs p


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
fueronAPasear :: Eq Atleta => JJOO -> [Atleta] -> [Atleta] 
fueronAPasear (J _ [] _) [] = []
fueronAPasear (NuevoDia competencias jjoo) [] = []
fueronAPasear (NuevoDia competencias jjoo) (x:xs)
	|(atletaNoPertenece competencias x) = x : fueronAPasear (NuevoDia competencias jjoo) xs
	|(atletaNoPertenece competencias x) == False = fueronAPasear (NuevoDia competencias jjoo) xs

atletaNoPertenece ::Eq Atleta => [Competencia] -> Atleta-> Bool
atletaNoPertenece [] x = True
atletaNoPertenece (x:xs) y
	|(compararAtleta atleta (participantesC x)) == False = atletaNoPertenece xs y
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


----------------------AUXILIARES EJERICICIO BOICOT POR DISCIPLINA---------------



