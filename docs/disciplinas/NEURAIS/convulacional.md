# Redes Neurais Convolucionais 

---

## 1. Introdução das Convolutional Neural Networks (CNNs)

### 1.1. Importância da visão computacional

A Visão Computacional é fundamental em diversas áreas, como:

- **Imagem Médica:** Auxilia no diagnóstico e no planejamento de tratamento;
- **Vigilância:** Usada para detectar e rastrear pessoas, veículos e para reconhecimento facial ou de placas;
- **Veículos Autônomos:** Permite tarefas como detecção de objetos, manutenção de faixa e reconhecimento de sinais de trânsito;
- **Aplicações Práticas:** Classificação, detecção e segmentação de imagens.

### 1.2. Limitações das Redes Feedforward

As redes neurais feedforward (totalmente conectadas) poderiam funcionar para problemas de visão computacional, mas com grandes limitações:

- **Grande Quantidade de Parâmetros:** Uma imagem de RM de 320×320 pixels, por exemplo, resultaria em um vetor com 102.400 entradas, o que poderia levar a 10 bilhões de parâmetros para peso, exigindo enorme esforço computacional;
- **Perda de Propriedades Estruturais:** Ao converter cada imagem em um vetor de entrada (achatando-a), as MLPs perdem as propriedades estruturais das imagens

### 1.3. Vantagens e propridades das CNNs

As Redes Neurais Convolucionais são a arquitetura ideal para dados estruturados em grade, como imagens, pois são mais eficientes e exigem menos parâmetros que as redes feedforward. Elas são projetadas para capturar duas propriedades estruturais principais das imagens:

- **Invariância à Translação:** A decisão de classificação da imagem (ex: "é um gato") é independente da posição do objeto na imagem (topo ou base).
- **Localidade:** A classificação não depende de pixels distantes do objeto de interesse (ex: pixels distantes correspondentes a um edifício ou árvore não anulam a classificação de um gato).


## 2. Estrutura da CNN
As CNNs trabalham analisando as imagens "pedaço por pedaço" e possuem uma estrutura básica composta por:

- **Camada Convolucional:** Utiliza a operação de convolução (ou correlação-cruzada, no contexto de redes) para extrair informações e padrões (mapas de características/recursos) das imagens;
- **Camada de Pooling:** Serve para reduzir a dimensão das imagens provenientes da camada convolucional. Tipos comuns incluem pooling máximo, médio e soma.

## 3. A Operação de Convolução

**Conceito:** É uma soma ponderada dos valores dos vizinhos de um ponto de entrada;

**Kernel (Filtro):** É a matriz de pesos aplicada na operação. Estes filtros são inicializados aleatoriamente e aprendidos durante o processo iterativo de treinamento da rede para extrair padrões das imagens (ex: bordas, texturas);

**Propriedade da Equivariância:** A operação de convolução é equivariante à translação da entrada. Se a imagem de entrada for transladada, o mapa de características de saída também será transladado da mesma forma.



### 4. Parâmetros e Técnicas da Convolução
**Zero Padding:** Técnica usada para manter a dimensão da imagem de saída igual à da imagem de entrada. Envolve preencher as posições além dos limites da entrada com zeros;


**Stride:** O número de posições (k) que o filtro (kernel) se desloca para cada saída. Strides maiores que 1 diminuem o tamanho da saída em relação à entrada.


**Dilatação (Dilated ou Atrous Convolution):** Intercala valores do kernel com zeros para combinar informações de uma região maior do input sem aumentar o número de parâmetros, mantendo a eficiência computacional.


**Canais:** Várias convoluções são aplicadas e empilhadas em "canais" (mapas de características) para evitar a perda de informação que ocorreria se apenas uma convolução fosse aplicada.

## 5. Regularização

### 5.1. Overfitting 

**O que é:** Ocorre quando o modelo aprende os dados de treinamento "bem demais", memorizando não apenas os padrões úteis, mas também o ruído e detalhes irrelevantes;


**Sintomas:** Excelente desempenho nos dados de treino (acurácia alta), mas desempenho ruim em dados novos (de validação/teste).


**Consequência:** O modelo perde a capacidade de generalização, tornando-se inútil para previsões no mundo real.

### 5.2. Técnicas de Regularização

Regularização é o ato de impor condições ou alterar a otimização para que a solução apresente um melhor comportamento, combatendo o overfitting.

| **Técnica** | **Descrição**| **Efeito**    |
|------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| **Funções Penalidades (L1 e L2)**        | Adicionar um termo de regularização (Rλ(θ)) à função de perda (L(θ)). A penalidade restringe a flexibilidade do modelo.                                                                                       | **L1 (Lasso)** usa a soma dos valores absolutos dos pesos. **L2 (Tikhonov)** usa a soma dos quadrados dos pesos.  |
| **Dropout**                              | Durante o treinamento, unidades (entradas ou neurônios artificiais) são desligadas aleatoriamente (removidas temporariamente junto com suas conexões de entrada e saída).                                   | Mitiga o **overfitting**, forçando a rede a não depender de neurônios específicos, melhorando o desempenho de generalização. Usualmente aplicado após cada camada totalmente conectada em CNNs.                                                                                                                             |
| **Batch Normalization (Normalização em Lote)** | Normaliza as entradas das camadas intermediárias ocultas, recentralizando-as pela média e redimensionando pelo desvio padrão.                                           | Promove um treinamento mais consistente, rápido e estável, atenuando problemas de gradientes. Também possui um efeito de regularização que ajuda na mitigação do **overfitting**.                                                                                                                                          |
| **Data Augmentation (Aumento de Dados)** | Aumenta artificialmente o conjunto de dados de treinamento, pois a escassez de dados favorece o **overfitting**.                                                      | Cria novas amostras de treinamento a partir das existentes (ex: rotação, corte, zoom, métodos baseados em histograma, **Generative Adversarial Networks**).                                                                                                                         |
