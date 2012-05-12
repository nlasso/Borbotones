module JJOO (JJOO, nuevoJ, anioJ, atletasJ, cantDiasJ, cronogramaJ,
jornadaActualJ, dePaseoJ)
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

--medalleroJ JJOO -> [(Pais,[Int])]
--medalleroJ (J anio atletas diaActual) = []
--medalleroJ (NuevoDia competencias jjoo)
--	|competencias == [] = []
--	|competencias /= [] =  concatenarMedallero x :

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
fueronAPasear :: JJOO -> [Atleta] -> [Atleta] 
fueronAPasear (J _ [] _) [] = []
fueronAPasear (NuevoDia competencias jjoo) [] = []
fueronAPasear (NuevoDia competencias jjoo) (x:xs)
	|(atletaNoPertenece competencias x) = x : fueronAPasear (NuevoDia competencias jjoo) xs
	|(atletaNoPertenece competencias x) == False = fueronAPasear (NuevoDia competencias jjoo) xs

atletaNoPertenece :: [Competencia] -> Atleta-> Bool
atletaNoPertenece [] x = True
atletaNoPertenece (x:xs) y
	|(compararAtleta atleta (participantesC x)) == False = atletaNoPertenece xs y
	|(compararAtleta atleta (participantesC x)) = False

compararAtleta :: Atleta -> [Atleta] -> Bool
compararAtleta atleta [] = False
compararAtleta atleta (x:xs)
	|ciaNumberA atleta == ciaNumberA x = True
	|ciaNumberA atleta /= ciaNumberA x = compararAtleta atleta xs

----------------------AUXILIARES EJERICICIO MEDALLERO---------------
devolverMedallero :: [Competencia] -> JJOO -> [(Pais,[Int])]
devolverMedallero (x:xs) jjoo = [()]

----------------------AUXILIARES EJERICICIO BOICOT POR DISCIPLINA---------------



 




