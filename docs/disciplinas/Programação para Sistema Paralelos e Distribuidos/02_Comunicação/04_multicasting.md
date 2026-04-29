# Multicasting

## 1. O problema do multicasting

Até aqui, a comunicação foi tratada principalmente como interações ponto a ponto (um sistema mandando para apena um outro). No entanto, em cenários de multicast, onde uma mesma mensagem precisa alcançar vários destinos, esse modelo se torna ineficiente. 

Uma possível solução seria usar um broker, como em sistemas de mensageria, mas em contextos como redes P2P isso quebra a descentralização e pode criar um gargalo central. 

Além disso, o multicast nativo da Internet possui uso limitado, pois exige suporte da infraestrutura de rede e pode consumir muita banda, tornando-se pouco viável em larga escala.


## 2. Overlay network

Como alternativa, surgiu o multicast em nível de aplicação (ao inves de níve de rede), no qual a própria aplicação implementa a lógica de disseminação das mensagens. 

### 2.1 Funcionamento

Isso é feito por meio de uma overlay network: uma rede lógica virtual formada por uma estrutura de dados onde um nó que quer enviar uma mensagem virá o nó raiz e os nós que querem receber a mensagem se inserem formando uma árvore.

Assim, o nó inicial não precisa enviar a mensagem para todos os participantes diretamente; ele envia para poucos, e os demais nós continuam a disseminação. Esse mecanismo distribui a carga de comunicação e torna o processo mais escalável em ambientes descentralizados.

```bash
        A
      /   \
     B     C
    / \     \
   D   E     F
```

- A envia para B e C.
- B repassa para D e E.
- C repassa para F.

### 2.2 Problema: Link Stress

O grande problema aqui é que, como a rede overlay não sabe como são os enlaces físicos, ou seja, como os cabos físicos da internet estão ligados no mundo real, uma única mensagem pode acabar passando pelo mesmo roteador físico várias vezes para alcançar caminhos virtuais diferentes. Isso gera um gargalo chamado **Estresse de Enlace (Link Stress).**

**Exemplo:** Tendo a árvore anterior, ela só correposnde a rede virutla, na vida real, por exemplo, pode acontece de:

- O caminho físco de A até B envolve passar por F e D.
- O caminho físco de A até C também envolve passar por F e D.
- Assim, a mensagem atravessa múltiplas vezes os mesmo enlaces físicos, resultando em desperdício de banda, congestionamento e gargalos.

**Switch-trees:** É um sistema que otimiza o problema do Link-Stress ao permitir que os nós mudem de pai dinamicamente para encontrar caminhos com menor latência e economiza banda.

## 3. Algoritmos de Disseminação

### 3.1 Flooding

É uma alternativa de multicast quando não é possivel construir uma estrutura organizada como uma árvore. A ideia principal é: quando um nó recebe uma mensagem, ele repassa essa mensagem para todos os seus vizinhos, esses vizinho fazem o mesmo, e assim por diante.  Se o nó já tiver visto a mensagem anteriormente, ele a ignora para evitar ciclos e duplicatas. Ideial quando:

**Quando usar:**

- Árvore não é viável.
- Não quer uma estrutura complexa.
- A rede é dinâmica.
- Você so quer garantir que chegue em todo mundo.

**Vantagens:** Simples e Robusto.

**Desvantagens:**

- Pode gerar uma explosão de mensagens.
- Desperdício de banda.

#### 3.1.1 Time-to-Live (TTL)

Uma otimização que define o número máximo de nós que a mensagem pode percorrer. Cada vez que passa por um nó esse valor diminui e quando chega a zero a mensagem é descartada, reduzindo o tráfego.

#### 3.1.2 Flooding Probabilístico

Mesmo com o TTL, o flooding ainda é pesado. Então outra otimização é: em vez de retransmitir sempre, cada nó retransmite com certa probabilidade. Isso reduz overhead, mas sacrifica garantia de alcance total. É um compromisso entre custo e confiabilidade.

#### 3.1.3 Disseminação Epidêmica (Gossip)

Em vez de enviar para todos os vizinhos, um nó escolhe e envia para alguns nós aleatórios da rede. Esses nós escolhidos (infectados) fazem a mesma coisa. Com o tempo, a informação se espalha pela rede de forma probabilística e exponencial, sendo muito mais eficiente. 

Assim, o gossip se relaciona com o termo **antientropia**: são otimos em garantir que todos os nós fiquem com o mesmo estado, por exemplo em relação a uma **atualização**, não somente espalhar de uma vez. Há 3 tipos de gossip:

**Push:** Um nó infectado escolhe outro nó e envia a informação para ele. No começo funciona bem pois, como poucos nós estão infectados, é quase garantido que todo contato gera um novo nó. Poém, quando quase todos os nós já estão infectados,um nó infectado pode acabar escolhendo um o nó que já está infectado, desperdidançando esforço.

**Pull:** Acontece o contrário: o nó não infectado é que toma iniciativa. Ele entra em contato com outro nó e pergunta: “você está infectado?. Se tiver, ele recebe. Esse modelo funciona melhor quando já existem poucos nós desatualizados, porque são justamente eles que vão atrás da informação. Isso evita o desperdício de mandar dados para quem já está atualizado.

**Push-Pull:** Combina os dois comportamentos. Quando dois nós se encontram, eles comparam seus estados e trocam o que estiver faltando dos dois lados. Ou seja, um pode enviar e o outro pode receber ao mesmo tempo. Esse modelo é mais eficiente no geral porque funciona bem em todas as fases da propagação. No início, ele se comporta como push e no final, ele se comporta como pull.
