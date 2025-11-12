# Medição de Software

---

## Introdução a Medição

### 1.1 O que é medição

- Medição é o processo de atribuir números a atributos de entidades de forma que descreva suas propriedade.
- É muito importante na obserção científica e no melhoramento de processos.
- Também está presente diariamente no nosso dia a dia: temperatura, peso, tempo, velocidade.
- Exemplo:
    - Entidade: código-fonte.
    - Atributo: tamanho.
    - Medida: número de linhas de códig0 = 1250.


### 1.2 Problema da medição
- Alguns atributos são medidos objetivamente (como a temperatura).
- Outros são conceitos abstratos e não podem ser medidos objetivamente (como a felicidade).
- Logo devem ser mensurados através de indicadores observáveis que devem ser claros e consistentes.
- **Regra dos Cinco:** há 93,75% de chance de que a mediana de uma população esteja entre o menor e o maior valor de uma amostra aleatória de cinco elementos.
    - Exemplo: medição da quantidade de linhas média de um projeto
    - Em vez de medir todo o código, meça 5 métodos aleatórios.
    - Se eles têm 10, 15, 25, 45 e 50 linhas, então o tamanho médio das funções do projeto está entre 10 e 50 linhas.


### 1.3 Negligência da falta de medição

A engenharia de software deve aplicar métodos científicos com coleta de dados, análise, modelagem, teste e validação. Algumas consequências comuns da negligência de medição:
    - Estimativas imprecisas: sem medir produtividade, não há como prever prazos.
    - Qualidade indefinida: não se sabe se o produto é bom.
    - Avaliação subjetiva: sucesso é baseado em opiniçao, não em evidência.
    - Promessas vazias: marketing ou gestores falam em ganhos altos sem dados que sustentem.
    - Além de improvisação, desperdício e resultados inconsistentes.

### 1.4  Os Três Propósitos da medição

De forma geral os três propósitos da medição são: 

- Compreensão: entender o que está acontecendo no projeto.
- Controle: monitorar progresso e qualidade.
- Melhoria: identificar padrões e aperfeiçoar processos.

Assim, esses propósitos podem aplicados a reduzir a incerteza sobre:

- Custo e esforço.
- Coleta de dados.
- Qualidade e confiabilidade.
- Complexidade de software.
- Manutenibilidade e segurança.

### 1.5 Objetivos da medição em software

Para gerentes:

- Avaliar custo e produtividade de processos.
- Determinar qualidade do código e confiabilidade do produto.
- Descobrir gargalos e melhorar processos.
- Estimar satisfação do cliente.

Para desenvolvedores:

- Verificar se requisitos são testáveis.
- Quantificar defeitos encontrados.
- Medir se metas de desempenho e qualidade foram atingidas.
- Fazer previsões futuras (ex: se a taxa de defeitos cairá).


### 1.6 Relação entre medição e modelo
A medição é base para construir modelos:

- Modelos de Custo.
- Modelos de Confiabilidade.
- Modelos de Qualidade

## 2. Tipos de Medidas

### 2.1 Medidas Objetivas e Medidas Subjetivas

Medidas objetivas: mensurável sem julgamento humano direto. Exemplo: linhas de código e tempo.

Medidas Subjetivas: envolve opnião, mas ainda pode ser quantificada com escalas (Likert 1-5). Exemplo: interface amigável. Para serem úteis elas devem ter sido:

- Coletadas ded forma consistente.
- Aplicada sobre o mesmo contexto.
- Avaliadas com critérios claros.

### 2.2 Medidas Diretas e Medidas Indiretas

Medidas Diretas: são obtididas sem cálculos intermediários. Exemplo: tempo de execução.

Medidas Indiretas/Derivadas: são obtidas a partir de outras medidas, como densidade = massa / volume. Exemplos clássicos:

- Produtividade = Linhas de código / Esforço (horas).
- Densidade de defeitos = Defeitos / Tamanho do software.
- Eficiência de testes = Defeitos encontrados / Esforço gasto.

### 2.3 Medidas Válidas e Medidas significativas

Medidas válidas: são aquelas que realmente medem o atributo que elas pretendiam medir. Exemplo: para pedir complexidade de código, contar linha de código não é uma medida valida, jáque número de linhas não refleto encessariamente a complexidade lógica.

Medidas significativas: são aquelas cujo resultados e operações matemáticas fazem sentido dentro do tipo de escala. Exemplo: se temos uma escala ordinal de satisfação (1,2,3,4,5),o resultado de uma média de 1, 2 e 4, por exemplo, resulta em 2,33, o que não faz sentido dentro da escala.

## 3. Escalas de Medição

Escalas são as regras que definem como os número são atribuitos aos atributos.As quatro principais escalas de medição são:

| Tipo de escala | Características| Exemplo| Operações válidas|
| -------------- | ---------------------------------------------------- | ---------------------------------------- | -------------------------------------- |
| **Nominal**    | Apenas identifica categorias                         | Linguagem usada (C, Python, Java)        | Igualdade / diferença                  |
| **Ordinal**    | Permite ordenar, mas sem saber quanto maior é        | Nível de satisfação (Baixo, Médio, Alto) | Comparações (“maior que”, “menor que”) |
| **Intervalar** | Diferenças têm significado, mas não há zero absoluto | Temperatura em °C                        | Soma, subtração                        |
| **Razão**      | Zero absoluto e proporções válidas                   | Tempo, linhas de código, defeitos        | Todas as operações matemáticas         |

Medidas que respeitem o tipo de escala usada são chamadas de medidas significativas. 

# 4. Confiabilidade da medição
Para confiar em uma métrica é necessário verificar:

- Consistência: mesmos resultados em medições repetidas.
- Precisão: nível de detalhe adequado.
- Validade: mede o que realmente se propõee a medir.