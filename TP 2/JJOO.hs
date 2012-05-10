module JJOO (JJOO, nuevoJ, anioJ)
where

import Tipos


data Atleta = A String Sexo Int Pais Int [(Deporte, Int)] deriving (Show)

data Competencia = C Categoria | Participar Atleta Competencia | Finalizar [Int] [(Int, Bool)] Competencia deriving (Show)

data JJOO = J Int [Atleta] Int | NuevoDia [Competencia] JJOO deriving (Show)

nuevoJ :: Int -> [Atleta] -> [[Competencia]] -> JJOO
nuevoJ anio atletas comp = agregarDia (J anio atletas 1) comp

anioJ :: JJOO -> Int 
anioJ (J anio _ _) = anio

--------------AUXILIARES----------------
agregarDia :: JJOO -> [[Competencia]] -> JJOO
agregarDia jjoo [] = jjoo
agregarDia jjoo (x:xs) = agregarDia (NuevoDia x jjoo) xs

