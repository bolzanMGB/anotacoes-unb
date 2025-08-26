
# Gerência de dispositivos de entrada e saída

## 1. Classificações de dispositivos de E/S

**Bloco:**

  * Armazena informações de tamanho fixo;
  * Pode ser lido e escrito independentemente;
  * Ex: HDs, Blu-Rays, Pendrives.

**Caracteres:**

  * Envia e aceita um fluxo de caracteres sem estrutura de bloco;
  * Não é endereçável, não possui operações de busca;
  * Ex: impressoras, mouses, teclados.

---

## 2. Subsistemas de E/S

**Funções:**

  * Isolar a complexidade dos dispositivos físicos;
  * Realizar buffering;
  * Garantir proteção de acesso aos dispositivos;
  * Fornecer interface padronizada para inclusão de novos drivers ao instalar dispositivos.

**Rotinas de E/S:**

  * Conjunto de rotinas para comunicação com qualquer dispositivo conectado;
  * Usuário não precisa lidar com detalhes da implementação;
  * São independentes do dispositivo;
  * Responsáveis por funções comuns a todos dispositivos.

**Tipos de chamadas:**

  * **Explícitas:** realizadas diretamente no subsistema de E/S;
  * **Implícitas:** realizadas a partir de outra chamada de sistema de outro módulo do SO;
  * **Síncronas:** aplicação espera o término, ficando bloqueada;
  * **Assíncronas:** aplicação continua pronta após a chamada, sendo avisada quando terminar.

---

## 3. Device Drivers

**Funções:**

  * Fazer a comunicação entre subsistema e dispositivos (via controladores de E/S);
  * Lidar com particularidades de cada dispositivo;
  * Cada driver manipula um tipo específico de dispositivo (ex: impressora, disco, etc.);
  * Recebem comandos gerais do SO e traduzem para comandos específicos;
  * Geralmente são escritos pelo fabricante e fornecidos junto com o dispositivo.

---

## 4. Controladores

**Função:**

  * Manipular diretamente os dispositivos;
  * Receber instruções da CPU e repassar ao dispositivo;
  * Possuem memória e registradores próprios.

**Tipos de comunicação entre CPU e dispositivo:**

  * **E/S programada:**

    * Uso intenso do processador;
    * Muito tempo desperdiçado.
  * **E/S por interrupção:**

    * CPU envia ordem e continua trabalhando;
    * Quando o dispositivo termina, interrompe a CPU para avisar.

  * **DMA (Acesso Direto à Memória):**

    * CPU apenas inicia e finaliza;
    * Transferência feita pelo controlador DMA;
    * Dados vão direto para RAM sem passar pela CPU;
    * CPU é avisada no final com uma interrupção.

---

## 5. Tratadores de Interrupção

Uma interrupção é um sinal enviado por um dispositivo pedindo atenção ao processador.

**Processo:**

  1. Interrupção acontece;
  2. Registradores são salvos numa pilha;
  3. O sistema identifica a causa da interrupção;
  4. Executa a rotina de tratamento;
  5. Restaura os registradores salvos.

---

## 6. Discos Magnéticos (HDs)

**Estrutura:**

  * Conjunto de discos sobrepostos unidos por um eixo vertical girando a velocidade constante;
  * Discos possuem trilhas, divididas em setores → formam cilindros;
  * **Cabeçote:** agulha que lê/grava dados, preso a um braço mecânico.

**Funcionamento:**

  * Disco gira constantemente;
  * Braço move o cabeçote até a trilha correta;
  * Cabeçote espera o setor desejado passar;
  * Realiza leitura/escrita.

**Tempo de acesso depende de:**

  * **Tempo de seek:** movimento do braço até a trilha;
  * **Tempo rotacional:** espera até o setor girar;
  * **Tempo de transferência:** leitura/escrita de dados do disco para a memória.

---

## 7. RAID

Técnicas para melhorar desempenho e/ou confiabilidade dos discos.

Criam um **dispositivo virtual (array)**, conjunto de discos físicos tratados como um só.

**RAID 0 (Striping):**

  * Divide o disco em faixas (stripes);
  * Distribui operações entre discos;
  * Permite processamento paralelo.

**RAID 1 (Espelhamento):**

  * Duplica o conteúdo do disco principal;
  * Garante confiabilidade (redundância).

**RAID 5 (Paridade distribuída):**

  * Distribui dados entre os discos do array;
  * Redundância baseada em paridade;
  * Permite recuperação de dados.

**RAID 2 e 3:**

  * Trabalham com palavras em vez de faixas.

**RAID 4 e 6:**

  * Semelhantes ao RAID 5, com diferenças no nível de redundância.

