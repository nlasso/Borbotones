module Competencia (Competencia, nuevaC, categoriaC, participantesC,
finalizadaC, rankingC, lesTocoControlAntiDopingC,
leDioPositivoC, finalizarC, linfordChristieC,
gananLosMasCapacesC, sancionarTrampososC)
where
import Tipos
import Atleta
data Competencia = C Categoria Participar Atleta Competencia Finalizar [Int] [(Int, Bool)] Competencia deriving (Show)

nuevaC :: Deporte -> Sexo -> [Atleta] -> Competencia

categoriaC:: Competencia -> (Deporte,Sexo)
categoriaC (C cat _ _ _ _ _ _) = cat

participantesC:: Competencia -> [Atleta]
participantesC (C _ [p] _ _ _ _ _) = [p]

finalizadaC:: Competencia -> Bool
