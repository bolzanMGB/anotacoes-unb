# Histórico do Node.js

## 1. Arquiteturas Bloqueantes (Blocking-Thread)

O Node foi criado em 2009 por Ryan Dahl, até então as principais tecnologias no desenvolvimento web eram:

- **PHP (via Apache).** 
- **Java (J2EE).**
- **NET(ASP.NET):**
- **Ruby on Rails**
- **Python Django** 

Todas essa tecnologias seguiam uma **Arquitetura Bloqueante** e o principal paradigma delas era o **Threads-per-Request:** o servidor criava um novo processo/thread para cada usuário que acessava o site.

Quando os usuários/servidor solicitavam alguma tarefa que incluía operações de I/0 — como ler um arquivo de disco, consultar o banco de dados ou esperar uma resposta de um sensor — a thread que estava cuidando daquela tarefa ficava parada (bloqueada):

- Caso houvessem filas formadas por requisições de acessos simultâneos, ficava esperando até sua vez de acessar o recurso.
- Na sua vez de acessar, tinha de esperar até o dado voltar.

**C10K Problem**

Isso se mostrou um design ineficiente pois, enquanto as threads ficavam bloqueadas, elas ainda estavam consumindo RAM e recursos da CPU. Assim, conforme o números de acesso aumenta, eventualmente a memória iria acabar e o servidor parava de responder.

Surgiu-se então o C10K Problem (The Concurrent 10 Kiloconnections Problem): a dificuldade que existia em 1999 que um servidor conseguir lidar com 10 mil requisições ao mesmo tempo sem travar.


**Onde são eficientes**

Apesar disso, os modelos bloqueantes ainda são muito utilizados atualmente principalmente para tarefas de **alta computação**, caracterizadas por ter cálculos matemáticos complexos — como renderizar videos, processar imagens, IA — que podem ser realizados em paralelo. Assim. aqui o principal gargalo não é a esperar por recursos, e sim o próprio processador.

## 2. Surgimento do Node.js

Até 2008, o JavaScript era interpretado. Isso significa que o código era lido e executado linha por linha em tempo real. O problema disso é que, se houvesse um loop que rodasse 1.000 vezes, o motor precisava interpretar a mesma instrução 1.000 vezes. Isso tornava a linguagem lenta e inviável para o processamento de aplicações mais complexas no servidor, que era o objetivo de Ryan Dahl.

Em 2008, o Google lançou o V8. Ele trouxe a técnica de compilação JIT (Just-in-Time). O V8 não compila o código inteiro de uma vez logo na primeira execução; ele interpreta o código para começar rápido e, conforme identifica trechos de código que são executados repetidamente (os hot paths), ele compila esses trechos específicos para código de máquina otimizado. Isso permite que a execução do JavaScript atinja uma performance comparável a linguagens como C++.

O V8 foi essencial para viabilizar o modelo não-bloqueante do Node.js. Como o processamento da lógica ficou muito rápido, a thread principal (o Event Loop) não perde tempo com cálculos lentos. O Node.js delega as operações de I/O - como ler arquivos, consultar banco de dados ou receber dados de sensores - para o sistema operacional através da biblioteca libuv. Assim, a thread principal fica livre imediatamente para continuar processando outras requisições enquanto aguarda o resultado da operação de I/O. Quando a tarefa termina, o sistema operacional avisa o Node, que executa a função de retorno (callback).

Em 2009, Ryan Dahl utilizou o V8 para o processamento do código e a biblioteca libuv (escrita em C++) para gerenciar as operações de sistema. Juntos, eles formam o ambiente de execução que permite rodar JavaScript diretamente no servidor.