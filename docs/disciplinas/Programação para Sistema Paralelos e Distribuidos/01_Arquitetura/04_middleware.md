
# Middleware e Sistemas Distribuídos

## 1. Introdução
O middleware é uma camada de software posicionada entra as aplicações e os sistemas operacionais. Seu principal objetivo é ocultar a complexidade/heterogeneidade do hardware e redes de modo a fornecer uma transparência do sistema para o usuário.

Além disso, ele também gerencia recursos e oferece serviços comuns — como protocolos de comunicação, segurança e persistência — que podem ser reutilizados por qualquer computador da rede. Isso evita que cada desenvolvedor tenha que "reinventar a roda" ao criar uma nova aplicação distribuída.


## 2. Sistemas Abertos e IDL

Um sistema distribuído bom é um sistema distribuído que pode ser expandido facilmente. Para isso, é necessário que ele tenha Interfaces Publicadas. 

Isso significa que o que o sistema faz e como ele funciona deve ser especificado e documentado em portais ou repositórios públicos onde qualquer desenvolvedor pode ter acesso.

Com as regras públicas, isso dá a liberdade de estender o sistema (colocar funções novas) ou até reimplementar partes dele de um jeito diferente, sem quebrar o resto.

Nessas interfaces públicas, para descrever a sintaxe e a semântica do sistema, é utilizado uma linguagem chamada IDL (Linguagem de Definição de Interface).

A IDL é uma linguagem neutra que defini uma ponte comum entre entre as outra linguagens, de modo a fornecer:

- Interoperabilidade: IDL define uma "ponte" comum,de modo que um componente escrito em Java pode interagir perfeitamente com um componente escrito em C++, pois ambos concordam com o contrato definido pela IDL.

- Extensibilidade: Qualquer novo componente que respeite a IDL pode ser integrado ao sistema existente sem esforço adicional de reescrita.

## 3. Integração de Sistemas

O problema: um componente legado (um sistema antigo que ainda funciona) de um sistema que já existe e que não pode, ou que seria inconveniente, ser reescrito para o IDL. Nesse sentido, surgem os:

**Wrappers/Adaptadores:** É uma casca que envolve o componente antigo. ELe traduz as chamadas da aplicação moderna para linguagem que o sistema antigo entende.

Novo problema: se você tiver 10 aplicações e 10 sistemas legados, você precisará de muitos adaptadores individuais. Para isso:

**Broker/Corretor:** É um mediador central. Todas as aplicações falam com o Broker, e o Broker, que é conectado aos wrappers, sabe como falar com cada sistema legado.

## 4. Interceptadores

O interceptador é um pedaço de código, geralmente dentro dos Stubs, que "entra no meio" do fluxo normal para fazer algo extra sem que a aplicação perceba.

**Como funciona:** Quando o cliente chama uma função, o interceptador "pausa" a execução, faz algo (como verificar se o usuário tem permissão ou criptografar o dado) e depois deixa a chamada seguir para a rede.

**Exemplo Prático:** Imagine um sistema bancário. Toda vez que você pede o saldo, um interceptador é disparado automaticamente para registrar um log (histórico) dessa consulta por motivos de segurança, sem que o programador precise escrever "salvar log" em cada função do app.

## 5. Problema da Transparência Absoluta

Esconder tudo nem sempre é bom. Se o middleware esconde totalmente que um servidor está em outro país, a aplicação pode tentar fazer milhares de chamadas rápidas, e o sistema ficará lento por causa da latência da rede. Se o usuário/desenvolvedor souber que o componente é remoto, ele pode otimizar o uso.

**Adaptabilidade Dinâmica (Hot-swapping):** Um bom middleware deve permitir que você troque uma "peça" (componente) enquanto ele está funcionando.

**Pragmatismo:** É como trocar o pneu de um carro com ele em movimento. Você "carrega" um novo interceptador de segurança ou "descarrega" um wrapper antigo sem precisar reiniciar o servidor principal. Isso garante a disponibilidade do sistema.

