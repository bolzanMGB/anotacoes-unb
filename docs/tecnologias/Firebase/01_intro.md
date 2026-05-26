# Introdução ao Firebase

## 1. Origem

- O Firebase nasceu em 2011, a partir de uma startup chamada **Envolve**, criada por James Tamplin e Andrew Lee.
- Originalmente a Envolve fornecia um sistema de chat para sites.
    - Bate-papo para jogos e fóruns.
    - Chat para Ecommerces.
- Esse sistema permita comunicações por texto instantâneas .
- Desenvolvedores que utilizam o desse passaram a utilizar a estrutura do chat para passar dados e sincronizar aplicativos em tempo real.
- Após perceberem isso, os fundadores resolveram separar o motor de sincronização em tempo real das mensagens de texto.
- Em 2012, eles lançaram o **Firebase** como um produto independente, tendo o **Real Time Database** como seu primeiro produto.
- Em 2014 o Firebase foi comprado pela Google.


## 2. Produtos

O Firebase se caracteriza como um **BaaS** (Backend-as-a-Service): ele fornece banco de dados, armazenamento de arquivos e hospedagem prontos, é necessários apenas instalar e configurar o SDK no seu frontend. Os principais serviços disponibilizados pelo Firebase são:

**1. Real Tima Database:** Banco de dados NoSQL original baseado em uma única grande árvore JSON.

**2. Cloud Firestore:**Banco de dados NoSQL moderno (mais organizado em coleções e documentos), que também funciona em tempo real.

**3. Firebase Cloud Messaging (FCM):** Sistema que envia notificações push instantâneas para os celulares dos usuários.

**4.Firebase Authentication (Login):** Serve apenas para validar se o e-mail e a senha estão certos ou processar o login com o Google. Ele não fica atualizando nada em tempo real; você faz o login, ele te dá a permissão e pronto.




## 3. Diferenças entre Realtiem Database e Cloud Firestore

### 3.1 Realtime Database: 

**Funcionamento:** Nele todos os dados são organizados em um única árvore dentro de um único arquivo .json gigante. Essa árvore possui nós e sub-nós.

**Plano Gratuito:** Nele você tem acesso à:

- Armazenamento: Até 1GB de dados.
- Tráfego de Rede: Até 10 GB por mês.
- Conexões Simultâneas: Até 100 dispositivos ao mesmo tempo

### 3.2 Cloud Firestore:

**Funcionamento:** Nele há várias coleções e essas coleções possum documentos (arquivos.json). Os dados são organizados em vários documentos.

**Plano Gratuito:** Nele você tem acesso à:

- Armazenamento: Até 1GB de dados.
- Escritas: Até 20.000 por dia.
- Leituras: Até 50.000 por dia.
- Deleções: Até 20.000 por dia.
