-- deve retornar so nome
-- deve utilizar filter e map

type Nome = String
type Nota = Float

data Aluno = Aluno Nome Nota deriving (Show)

a1 = Aluno "Joao" 4
a2 = Aluno "Maria" 5
a3 = Aluno "Pedro" 6
alunos = [a1,a2,a3]


filtrarAprovados array = filter ver array where
    ver (Aluno nome nota) = nota >= 5

mapAprovados array = map ver array where   
    ver (Aluno nome nota) = nome

listaAprovados array = mapAprovados (filtrarAprovados array)


ghci> listaAprovados alunos
["Maria","Pedro"]
