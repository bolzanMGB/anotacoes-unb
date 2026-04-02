# Linux Kernel

## 1. O Papel do Kernel Linux em Sistemas Embarcados

### 1.1 Motivos pelo seu uso

**Abstração e Portabilidade:** O Linux funciona como um tradutor universal. Você desenvolve um software que fala com o kernel e o kernel fala com o hardware. Dessa forma, se você mudar o hardware, o seu código não vai para o lixo, você apenas precisa adaptar o kernel.

**Gerenciamento de Recursos (MMU):** O Linux exige uma MMU, um componente de hardware que o Kernel controla para criar uma memória virtual. Assim, cada programa acredita que tem toda a memória RAM só para ele, isolando os processos, de modo que se um programa travar, o kernel mata esse programa e mantém o resto do sistema vivo (importante em sistemas críticos).

**Pilha de Protocolos:** O Linux já vem com protocolos prontos para diferentes redes, arquivos e drivers. Assim, a empresa foca no seu produto final, em vez de perder tempo programando comunicações.

**Escalonamento:** Permite distribuir o tempo de CPU entre centenas de tarefas baseando-se em prioridades.

**Ecossistema e Open Source:** 

- Sem Licenciamento: Você não paga royalties por dispositivo vendido com Linux.
- Segurança Comunitária: Se alguma falha de segurança é descoberta, milhares de desenvolvedores ao redo do mundo corrigem em horas.
- Customização Extrema: Você pode remover todas as partes que você não usa, deixando-o minúsculo e rápido.

### 1.2 Responsabilidades

- Controlar dispositivos de I/O.
- Fazer o escalonamento de processos.
- Gerenciar compartilhamento de memória e os sinais de sistema.

## 2. Arquitetura de Camadas do Sistema

O Linux divide o sistema em camadas rigorosas para manter a segurança e a organização.

![Inserção](../../assets/pngs/93.png){align=center }

