# O Ecossistema Node

## 1. Introdução

O ecossistema Node é modular, ou seja, nele temos o Node.js como base de execução e, a partir dele, podemos escolher e combinar diferentes linguagens, motores de rota e frameworks dependendo do objetivo do seu projeto.

## 2. Base Tecnológica
Todo projeto que utiliza do Node possui essas três tecnologias:

**Node.js**
- É o ambiente de execução.
- Permite rodar código JavaScript no terminal ou em um servidor, tirando a linguagem do isolamento do navegador como era antes.

**JavaScript**
- É a linguagem  de programação base.
- Todo código executado pelo Node precisa ser em JS.

**TypeScript**
- É um superset do JavaScript.
- Ele adiciona um extensor/camada de proteção em cima do JS.
- A base lógica é exatamente a mesma do JS, porém ele adiciona novos elementos à sintaxe (como definições de tipos, interfaces e contratos de dados) que não existem no JS puro.
- Já que o Node entente apenas JS, o TS é compilado para JS antes de ser enviado e executado pelo servidor.
- Por muitos anos o padrão do mercado era usar o Nodejs 100% apenas com JS puro, porém atualmente, apesar de ainda ser possível usar só JS, o padrão é com o uso do TS.

## 2. Frameworks Não-Opinativos (Minimalistas  )
São bibliotecas ou frameworks minimalistas que oferecem simplificações para criações de rotas e tratamento de requisições/respostas. Sem elas teríamos que lidar com o Node puro e consequentemente com muito código de baixo nível. Ponto importante: elas não fornecem regras de arquitetura e organização de pasta, você poderia colocar todo o sistema em um arquivo só de 5k de linhas e iria rodar. Os dois principais são:


**ExpressJS**
- É o mais tradicional e popular.
- Oferece os recursos essenciais.
- Mais simples

**Fastify**
- É a alternativa mais moderna e com desempenho significadamente superior.
- Foco em alta performance, tipagem e baixo overhead.
- Baseada em plugins

## 3. Frameworks Arquiteturais (Opinativos)

São frameworks que resolvem o problema da organização ao obrigar padrões rígidos de arquitetura, facilitando a manutenção e escalabilidade. Eles possui opiniões fortes sobre como você deve estruturar e desenvolver a aplicação. Podem ser incrementados com Frameworks de Frontend, como o React.

**NestJS**
- Framework arquitetural para Node.
- Baseado em Módulos, Controlados e Serviços.
- Utiliza internamente um motor HTTP como Express ou Fastify.

**AdonisJS**
- Framework fullstack opinativo 
- Possui seu próprio sistema HTTP, não dependendo de motores como Express ou Fastify.

- Já inclui diversos recursos integrados como autenticação, validação, sessões e migrações.

## 4. Frameworks Full-Stack Web
São frameworks que resolvem o problema da integração do frontend e backend, permitindo desenvolver interfaces, rotas de servidor e APIs em uma única aplicação. Podem ser combinados com frameworks arquiteturais para separar responsabilidades e aumentar a escalabilidade do backend.

**Next.js**
- Framework construído encima do React focado em aplicações web full-stack.
- Pode acessar bancos de dados diretamente e possui sua própria camada arquitetural.
- Sem a necessidade obrigatória de criar um backend separado com Express ou NestJS.

## 5. Exemplos de Combinações utilizadas no Mercado

### 5.1 Stack Minimalista

**Node.js + JavaScript/TypeScript + Express**

- Combinação simples e flexível.
- Muito utilizada em APIs pequenas, protótipos, microsserviços e aplicações que não exigem uma arquitetura muito rígida. 
- O Express fornece apenas os recursos essenciais para lidar com HTTP, deixando a organização sob responsabilidade da equipe.

### 5.2 Stack de Alta performance

**Node.js + TypeScript + NestJS + Fastify**

- Combina organização arquitetural com desempenho otimizado.
- Bastante utilizada em sistemas com alto volume de requisições, aproveitando a performance e o baixo overhead do Fastify.
- NestJS como camada arquitetural.
- Fastify como motor HTTP. 


### 5.3 Stack Corporativa
**Node.js + TypeScript + NestJS + Express**

- Uma das combinações mais populares. 
- Muito utilizada para por equipes que priorizam organização, padronização e ampla compatibilidade com bibliotecas do ecossistema Node.js.
- Express como motor HTTP. 
- NestJS como camada arquitetural.


### 5.4 Stack Web Full-Stack
**Node.js + TypeScript + Next.js**

- Focado na integração entre frontend e backend no mesmo projeto.
- Node como ambiente e o NextJS organizando tanto o backend quanto o frontend.

### 5.5 Stack Web Corporativa

**Node.js + TypeScript + Next.js + NestJS + Express**

- Combinação comum em aplicações grandes que precisam separar claramente frontend e backend.
- Muito utilizada em sistemas corporativos e plataformas escaláveis.
- Next.js focado no frontend e renderização no servidor.
- NestJS como camada arquitetural
- Express como motor HTTP 