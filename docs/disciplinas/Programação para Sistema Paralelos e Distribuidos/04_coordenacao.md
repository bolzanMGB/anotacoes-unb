# Coordenação

## 1. Introdução

Depois de entender estrutura e comunicação, o próximo problema é a coordenação. Em sistemas distribuídos, não basta os processos conseguirem  comunica-se entre si, também é necessário organizar:

- Quem pode acessar um recurso.
- Adesso simultâneos a recursos.
- Em que ordem os eventos ocorrem.
- Como manter os dados consistentes entre vários nós.

Em um sistema local essa coordenação é mais simples, já que os processos compartilham apenas uma única memória, um único sistema operacional e um único reógio. Já nos SD, como cada parte está em uma máquina diferente e existe diferentes tempo, SOs e etc, a coordenação de processos é muito mais complexa e importante. Se dois processos tentam atualizar o mesmo recurso ao mesmo tempo, ou se diferentes nós precisam concordar sobre uma sequência de eventos, o sistema pode quebrar a consistência.

## 2. Sincronização de relógios

A primeira grande questão é o tempo. Em um sistema local, o tempo é simpls de usar já que todos os processos compartilham o mesmo tempo. Já em SDs, cada máquina tem seu próprio relógio, o que torna dificil saber a ordem real dos eventos apenas olhando o horário registrado por cada nó.

### 2.1 Cristal de Quartzo

Todo computador possui um mecanismo físico para medir o tempo que é baseado em cristal de quartzo. Quando esse crital recebe uma tensão elétrica ele vibra numa frequência estável, conhecida e previsível

**Relógio de Cristal de Quartzo:** O mecanismo para medir o tempo em um computador é baseado na vibração que o seu cristal de quartzo, acoplado no sue interior, produz ao receber uma tensão elétrica.

**Clock Tick:** O hardware do computador possui um contador que é decrementado a cada oscilação do cristal de quartz. Quando o contador atinge zero, o hardware gera uma interrupção chamada clock tick, indicando que uma unidade de tempo passou. O sistema operacional utiliza esses ticks para atualizar o relógio do sistema e executar tarefas periódicas,.

**Clock Skew/Drift:** Com o tempo, condições físicas e ambientais afetam a frequência de oscilação do cristal de quartzo, causando pequenas variações na taxa dos clock ticks. Essas diferenças se acumulam ao longo do tempo, resultando em uma disparidade no tempo dos relógios. 

Mesmo relógios digitais sendo precisos, o clock skew faz com que diferentes máquinas tenham percepções de tempo ligeiramente distintas, exigindo mecanismos de sincronização em sistemas distribuídos.

### 2.2 Algorítmo de Cristian

Aparece como uma solução prática para sincronizar um cliente com um servidor de tempo.

- Teve haver um servidor de tempo que é preciso e o cliente pode usar como referência.
- Cliente consulta um servidor confiável.
- Cliente registra o momento em que envia a requisição e o momento em que recebe a resposta.
- Cliente recebe a hora e estima o atraso da comunicação da rede para ajustar o próprio relógio.

### 2.3 Network Time Protocol (NTP)

