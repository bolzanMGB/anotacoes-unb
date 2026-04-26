# Sistema de Arquivos

---

## 1. Introdução

**Arquivos:**

  * Permitem leitura e gravação de dados em discos.
  * Viabilizam o compartilhamento de dados entre processos.
  * São conjuntos de instruções ou dados.
  * Identificados por **nome.extensão** (ex.: `arquivo.txt`).

**Organização de arquivos:**

  * Conjunto de bytes estruturados ou não.
  * **Métodos de acesso:**

    * **Acesso sequencial:**

        * Usado em **fitas magnéticas**.
        * Dados só podem ser lidos na ordem em que foram gravados.
        * Gravação somente no final do arquivo.
        * Exemplo: para ler o registro `R5`, é necessário passar por `R0, R1, R2, R3, R4`.
    
    * **Acesso direto:**

        * Usado em **discos magnéticos**.
        * Permite ler ou gravar um registro diretamente, desde que se conheça seu número.
        * Todos os registros têm o mesmo tamanho.

    * **Acesso indexado:** usa um **índice (dicionário)** acessado por chaves.

* **Operações de entrada/saída (E/S):** rotinas de E/S dos sistemas de arquivos permitem:

    * Traduzir endereços.
    * Ler e gravar dados.
    * Criar e eliminar arquivos.

* **Atributos:**

    * Informações de controle sobre um arquivo.
    * Exemplos: tamanho, permissões, autor, data de criação, data de modificação.

---

## 2. Diretórios

Forma como o sistema organiza logicamente os arquivos.

**Tabela de arquivos:**

  * Contém todos os arquivos abertos no momento.

**Tipos de estruturas de diretórios:**

  * **Nível único:** um único diretório para todos os arquivos e usuários.
  * **UFD (User File Directory):** diretório particular para cada usuário.

    * **MFD (Master File Directory):** diretório principal que gerencia os diretórios individuais.
  * **Path (caminho):** sequência que referencia um arquivo dentro da hierarquia.
  * **Estrutura em árvore:** permite múltiplos subdiretórios por usuário.

---

## 3. Gerência de Espaço Livre em Disco

Métodos para identificar blocos disponíveis:

  * **Mapa de bits.**
  * **Lista encadeada.**
  * **Tabela de blocos livres.**

---

## 4. Gerência de Alocação de Espaço

**Alocação contígua:** Arquivo armazenado em blocos sequenciais.

* **Estratégias:**

    * *First-fit:* primeiro segmento livre de tamanho suficiente.
    * *Best-fit:* menor segmento livre de tamanho suficiente.
    * *Worst-fit:* maior segmento livre.

* **Problema:** fragmentação.

* **Solução:** desfragmentação, reorganizando arquivos para concentrar o espaço livre. Arquivos podem ter tamanhos variáveis.

**Alocação encadeada:**

  * Arquivo organizado em blocos ligados logicamente por ponteiros.
  * Elimina fragmentação de espaço livre.
  * **Problemas:**

    * Fragmentação do arquivo (blocos espalhados).
    * Leitura lenta: necessário percorrer blocos em sequência.
    * Solução parcial: desfragmentação para tornar blocos contíguos.

**Alocação indexada:**

  * Uso de **blocos de índice**.
  * Permite acesso direto a qualquer bloco do arquivo.

---

## 5. Proteção de Acesso

Como o disco é compartilhado por vários usuários, é necessário:

  * Proteger dados gravados.
  * Permitir compartilhamento controlado.

**Tipos de concessões:**

  * Leitura.
  * Gravação.
  * Execução.
  * Exclusão.

**Mecanismos de proteção:**

  * **Senha de acesso:** acesso liberado apenas com senha.
  * **Grupos de usuários:**

    * Arquivos podem ser compartilhados dentro de um grupo.
    * Proteções definidas em três níveis:

      * **Owner** (dono).
      * **Group** (grupo).
      * **All** (todos).
  
  * **Lista de Controle de Acesso (ACL):** Cada arquivo possui uma lista especificando usuários e seus direitos de acesso.

---

## 6. Implementação de Caches

**Problema:** disco é muito mais lento que a memória principal.

  * Está fisicamente distante do processador.
  * Possui partes mecânicas.
  * Discos magnéticos são especialmente lentos.

**Buffer Cache:**

  * Área da memória principal que armazena temporariamente blocos de disco usados com frequência.
  * Antes de acessar o disco, verifica-se primeiro no cache.
  * Se não estiver, o acesso vai ao disco.
  * **Políticas de substituição:**

    * FIFO (First In, First Out).
    * LRU (Least Recently Used).

**Problema de consistência:** 

Se a máquina perder energia, dados no cache podem ser perdidos.
  
  * **Soluções:**
    * **Atualização periódica:** grava blocos no disco em intervalos de tempo.

        * Menos operações de escrita.
        * Maior risco de perda em caso de falha de energia.

    * **Atualização imediata (*write-through*):**

        * Toda alteração no cache é escrita imediatamente no disco.
        * Mais seguro, porém mais lento.

