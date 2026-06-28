# Desenvolvimento de Sistemas Embarcados

---

## 1. Cross-Platform

### 1.1 Definição de Cross-Platform

Quando você programa um aplicativo para Windowns, você escreve e testa no próprio Windowns. Em sistemas, isso raramente acontece porque o hardware final (Target) geralmente não tem teclado, tela ou poder de processamento suficiente para rodar uma IDE pesada. Cria-se, então, o conceito de Cross-Platform.

**Host:** É o computador de desenvolvimento potente, um PC rodando Linux, Windows ou macOS. É aqui você escreve o código de rápida e confortável.

**Target**: É a placa embarcada, como uma Raspberry Pi. É o hardware final que vai receber e executar o código.

**Compilador Nativo:** É o compilador comum de um PC. Ele gera arquivos executáveis/binários compatíveis apenas com processadores Intel/x86, ou seja, arquivos `.exe` ou `.elf`.

**Cross-Compiler:** É um compilador, como o GCC, que roda no seu Host Intel/x86, mas que vai gerar os arquivos binários compatíveis com a arquitetura do seu Target (geralmente ARM).

**Cross-Platform:** É o processo de desenvolvimento onde um Host escreve, edita e traduz o código através de um Cross-Compiler para uma linguagem (binário) que o processador do Target seja capaz de entender e executar.

---

### 1.2 Configuração de Conexão (Topologia)

Há três formas de organizar a relação entre um PC e a placa:

**Linked Setup (Conectado):** Existe um cabo físico (Serial, Ethernet, USB ou JTAG).Permite o uso de NFS (Network File System), onde a placa "enxerga" uma pasta do seu PC como se fosse o disco rígido dela.

**Removable Storage (Mídia Removível):** Você compila no PC, grava em um Cartão SD/Pendrive e o insere na placa. O Target precisa apenas de um Bootloader mínimo para ler essa mídia.

**Standalone (Independente):** O compilador e o editor rodam direto na placa. É pouco usado para projetos grandes devido à baixa velocidade do hardware embarcado.

---

### 1.3 Acesso Remoto
Como muitas vezes o Target não tem monitor, usamos a rede para controlá-lo:

**SSH (Secure Shell):** Abre um terminal remoto. Você digita comandos no seu PC e eles são executados na CPU da placa.

**SCP (Secure Copy):** Protocolo para copiar o arquivo binário (o código pronto) do seu PC para dentro da placa através do Wi-Fi ou cabo de rede.

---

### 1.4 A Toolchain e o Cross-Compiler (GCC)

Um compilador comum de PC gera arquivos executáveis/binários compatíveis apenas com processadores Intel (x86), ou seja, arquivos `.exe` ou `.elf`. Então, para sistemas embarcados, precisamos de uma Toolchain.

**Toolchain:** Um conjunto de ferramentas, incluindo Cross-Compiler, Linker e Debugger, configurado para gerar código para outra arquitetura (geralmente ARM).

**GCC (GNU Compiler Collection):** É o motor principal. No Linux, você instala as ferramentas (build-essential) e depois o compilador específico para a sua placa.

**Configuração de Ambiente:** É necessário adicionar o endereço da pasta do compilador na variável PATH do sistema (editando o arquivo .bashrc). Isso permite que você chame o compilador de qualquer lugar do terminal.

## 2. Recursos do Sistema Linux

### 2.1 Tipos de Arquivos

No Linux, a comunicação com um pen drive, uma câmera, um sensor de temperatura  ou um simples documento de texto na tela é tratada da mesma forma pelo programador: abrindo, lendo e fechando um "arquivo".

O sistema classifica esses "arquivos" em categorias:

**Arquivos Regulares:** Arquivos de dados reais. Podem ser:

- **Binários:** Onde o conteúdo da instruções de máquina, como programas executáveis.
- **Texto:** Arquivos legíveis por humano, por exemplo arquivos.txt.

**Diretórios:** Arquivos especiais usados apenas para agrupar r organizar outros arquivos.

**Dispositivos (Hardware):** Representação de um componente físico. Se você quiser ler os dados do teclado, o Linux lê o arquivo /dev/input/keyboard. Podem ser:

- **De bloco:** Utilizam buffer para leitura/gravação de dados, por exemplo unidade de disco (HDs, SSDs, Pendrive).
- **De caractere:** Não utilizam buffer para leitura/gravação, por exemplo dispositivos como impressoras, mouse e teclado.

**Links:** São arquivos utilizados para fazer referência a um outro arquivo localizado em outro local. Podem ser:

- **Simbólicos:** Fazem uma referência ao arquivo através de seu endereço lógico, por exemplo atalhos de arquivos.
- **Absolutos:** Fazem referência ao arquivo através do seu endereço físico no disco rígido ou memória, por exemplo cópias de arquivos.

### 2.2 Acesso a Arquivos
Existem duas formas principais de lidar com a entrada e saída (I/O) de dados em C. A escolha depende se você busca facilidade e portabilidade ou performance e controle de hardware.

| Característica | Biblioteca Padrão C (stdio.h) | Interface UNIX / POSIX |
| :--- | :--- | :--- |
| **Identificador** | Ponteiro de Arquivo (`FILE *fp`) | Descritor de Arquivo (`int fd`) |
| **Buffering** | Sim (Automático) | Não (Direto / Raw) |
| **Portabilidade** | Alta (Funciona em quase tudo) | Limitada (Sistemas Unix/POSIX) |
| **Velocidade** | Melhor para muitos arquivos pequenos | Melhor para controle de hardware e drivers |
| **Principais Funções** | `fopen`, `fclose`, `fread`, `fwrite` | `open`, `close`, `read`, `write` |
| **Uso Ideal** | Aplicações de desktop, logs, processamento de texto. | Drivers, comunicação entre processos, sensores. |

#### 2.2.1 Biblioteca Padrão C (stdio.h):
Esta é a camada de alto nível. Ela não fala diretamente com o Kernel, mas sim com uma biblioteca que gerencia os dados para você.

**Características:**

- Buffered I/O: Acumula dados em uma memória temporária (buffer) antes de enviar ao disco, o que evita o uso excessivo de recursos do sistema.
- Portabilidade: O mesmo código funciona em Windows, Linux ou macOS.
- Tipagem: Trabalha com ponteiros de arquivos (FILE *).
- Facilidade: Permite leitura e escrita formatada (converte números em texto automaticamente).

**Exemplo Prático:**

```c
#include <stdio.h>

int main() {
    FILE *fp = fopen("teste_c.bin", "wb+");
    float pi = 3.14, lido;

    // Escrita formatada/binária com buffer
    fwrite(&pi, sizeof(float), 1, fp);
    
    rewind(fp); // Volta ao início

    // Leitura
    fread(&lido, sizeof(float), 1, fp);
    printf("Lido via C Standard: %f\n", lido);

    fclose(fp);
    return 0;
}
```

#### 2.2.2 Biblioteca UNIX/POSIX

**Características:**

- Unbuffered I/O: O dado sai do programa e vai direto para o driver/dispositivo. Ideal para hardware em tempo real.
- File Descriptors: Não usa ponteiros complexos, apenas números inteiros (int fd) para identificar o arquivo.
- Raw Data: Não formata nada. Ele trata tudo como uma sequência bruta de bytes.
- Específico: Feito para sistemas baseados em Unix (Linux, macOS, Android).


**Exemplo Prático:**

```c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    // Abre o arquivo e recebe um ID (File Descriptor)
    int fd = open("teste_unix.bin", O_RDWR | O_CREAT, 0644);
    float pi = 3.14, lido;

    // Escrita bruta (Direto para o Kernel)
    write(fd, &pi, sizeof(float));

    lseek(fd, 0, SEEK_SET); // Volta ao início (equivalente ao rewind)

    // Leitura bruta
    read(fd, &lido, sizeof(float));
    printf("Lido via UNIX: %f\n", lido);

    close(fd);
    return 0;
}
```