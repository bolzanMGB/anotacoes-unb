### 6. Algoritmos de Eleição

Em muitos sistemas, é necessário escolher dinamicamente um coordenador. Isso acontece quando o coordenador atual falha ou quando o sistema precisa reorganizar sua liderança. 

Os algoritmos de eleição são baseados em uma rede de overlay em nós e resolvem esse problema: eles determinam qual nó vai assumir o papel de coordenador e fazem com que todos os demais descubram esse resultado. Quando um processo é eleito a coordenador, ele não para com a atividade q estava executando, ele passa a trabalhar em turnos.

#### 6.1 Algortimo Bully

Nele, o nó com maior identificador vence. Note que não é maior timestamp, e sim ID. O ID é atribuido pelo administrador do sistema e geralmente indica potência. Funcionamento:

- Um nó percebe que o coordenador não responde e inicia uma eleição **(ELECTION)** enviando uma mensagem para os nós maiores que ele.
- Se alguém responder **OK**, significa que há um nó mais forte vivo e você é desclassificado.
- Processos que derem OK também dao ELECTION.
- Quando ninguém mais responder, achou-se o maior e anuncia-se o vencedor **(COORDINATOR)**.

O nome “Bully” vem dessa lógica: o nó mais alto acaba “empurrando” os demais até assumir a coordenação. 

**Vantagens:**

- Simples.
- Termina com clareza.

**Desvantagens:**

- Depende de mensagens ELECTION, OK e COORDINATOR.
- Assume que os nós conseguem identificar corretamente quem está ativo.

imagem 113


#### 6.2 Algoritmo Anel

Aqui, o critério também é quem possui o maior identificador, porém, os nós estão organizados em uma estrutura cíclica e cada nó conhece seu sucessor. Funcionamento:

- Quando um processo percebe falha do coordenador, ele declara uma **ELECTION:** cria uma lista, assina seu ID e passa para o próximo nó.
- A lista é repassada e os nós vão acrescentando seus próprios identificadores.
- Se o sucesso não responder, ele é pulado.
- A mensagem percorre o ciclo até retornar ao iniciador.
- O iniciador olha o maior número e anuncia o vencedor **(COORDINATOR)** 


