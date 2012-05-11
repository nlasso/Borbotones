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

atletasJ JJOO -> [Atleta]
atletasJ (J _ atletas _) = atletas 
atletasJ (NuevoDia _ jjoo) = atletasJ jjoo

cantDiasJ JJOO -> Int
cantDiasJ (J _ _ _) = 1 
cantDiasJ (NuevoDia competencias jjoo) = 1 + (cantDiasJ jjoo)

cronogramaJ JJOO -> Int -> [Competencia]
cronogramaJ jjoo dia
	| dia < 1 || dia > (cantDiasJ jjoo) = error "El dia no esta contemplado"
cronogramaJ (NuevoDia competencias jjoo) dia
	|dia == (cantDiasJ jjoo) = competencias
cronogramaJ (NuevoDia competencias jjoo) dia = buscaDia jjoo (dia-1) 

jornadaActualJ JJOO -> Int 
jornadaActualJ (J _ _ diaActual) = diaActual 
jornadaActualJ (NuevoDia competencias jjoo) = jornadaActualJ jjoo

dePaseoJ JJOO -> [Atleta]
dePaseoJ (J anio atletas diaActual) = fueronAPasear (J anio atletas diaActual)  atletas
dePaseoJ (NuevoDia competencias jjoo) = dePaseoJ jjoo

medalleroJ JJOO -> [(Pais,[Int])]
medalleroJ (J anio atletas diaActual)
medalleroJ (NuevoDia competencias jjoo)

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
	|not(y `elem` participantesC x) = atletaNoPertenece xs y
	|(y `elem` participantesC x) = False

----------------------AUXILIARES EJERICICIO MEDALLERO---------------




 




