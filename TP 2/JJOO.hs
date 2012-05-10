module JJOO (JJOO, nuevoJ, anioJ)
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
atletasJ (J _ atletas _) = atletas --el mismos importa?? porque estamos respetando un orden.
atletasJ (NuevoDia _ jjoo) = atletasJ jjoo

cantDiasJ JJOO -> Int
cantDiasJ (J _ _ _) = 1   --No suma porque no es un nuevo dia sino que es le caso base.
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
dePaseoJ 

--------------AUXILIARES----------------
agregarDia :: JJOO -> [[Competencia]] -> JJOO
agregarDia jjoo [] = jjoo
agregarDia jjoo (x:xs) = agregarDia (NuevoDia x jjoo) xs

buscaDia :: JJOO -> Int -> [Competencia]
buscaDia (NuevoDia competencias jjoo) dia
	| dia == 1 = competencias
	| dia > 1 = buscaDia jjoo (dia-1)
 




