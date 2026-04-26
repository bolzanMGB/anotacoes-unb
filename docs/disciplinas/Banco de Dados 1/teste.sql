create table Cursos(
    id_curso INT PRIMARY KEY,
    duracao INT NOT NULL
),

create table Aluno (
    id_aluno INT PRIMARY KEY,
    nome VARCHAR (100) NOT NULL,
    cpf INT UNIQUE,
    id_curso INT,
    FOREIGN KEY (id_curso) REFERENCES Cursos(id_curso)
);


create table Disciplina {
    CREATE TABLE Cursos (
    id_curso INT PRIMARY KEY,
    duracao INT NOT NULL
); -- Use ; aqui

CREATE TABLE Aluno (
    id_aluno INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL,
    cpf VARCHAR(11) UNIQUE, -- CPF como VARCHAR para não dar erro de tamanho
    id_curso INT,
    FOREIGN KEY (id_curso) REFERENCES Cursos(id_curso)
);

CREATE TABLE Disciplina (
    id_disciplina INT PRIMARY KEY,
    nome VARCHAR(100) NOT NULL, -- Corrigido para VARCHAR
    carga_horaria INT NOT NULL -- Removida a vírgula extra aqui
);

CREATE TABLE Matricula (
    id_aluno INT,
    id_disciplina INT,
    semestre INT NOT NULL,
    nota DECIMAL(4,2),
    -- Definindo as chaves no final (mais organizado para a prova)
    PRIMARY KEY (id_aluno, id_disciplina, semestre), 
    FOREIGN KEY (id_aluno) REFERENCES Aluno(id_aluno),
    FOREIGN KEY (id_disciplina) REFERENCES Disciplina(id_disciplina)
); INT PRIMARY KEY,
    nome INT NOT NULL,
    carga_horaria INT NOT NULL,
};


create table Matricula{
    id_aluno int,
    FOREIGN KEY (id_aluno) REFERENCES Aluno(id_aluno),
    id_disciplina int,
    FOREIGN KEY (id_disciplina) REFERENCES Disciplina(id_disciplina),
    semestre INT NOT NULL,
    nota DECIMAL (4,2)
};

