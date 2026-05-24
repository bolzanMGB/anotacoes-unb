# Introdução ao Node

## 1. Instalação

**1.1 Instalação do NVM:**

```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
``` 

**1.2 Verificar instalação:**

```bash
nvm --version
``` 

**1.3 Teste pelo terminal:**

Comando `node` permite executar JS pelo terminal.

```bash
$ node
> console.log ("Hello World")
Hello World
undefined
> 
``` 

## 2. Módulos

O Node é considerado um ambiente modular. 

Um `Módulo` pode ser descrito como qualquer conjunto reutilizável de código. Podendo ser Bibliotecas, Frameworks, Pacotes ou mesmo Projetos.

### 2.1 packet.json

Todo módulo é acompanhado de um arquivo `package.json`. Esse arquivo é compostos por atributos responsáveis por descrever o módulo. Por exemplo:

```js
{
  "name": "nome-do-seu-projeto",
  "version": "1.0.0",
  "description": "Descrição curta sobre o que o seu projeto faz.",
  "main": "index.js",
  "private": true,
  "author": "Nome do Autor <seu-email@email.com>",
  "scripts": {
    "start": "node index.js",
    "dev": "nodemon index.js",
    "test": "echo \"Erro: nenhum teste configurado\" && exit 1"
  },
  "dependencies": {
    "nome-do-pacote-1": "1.0.0",
    "nome-do-pacote-2": "~1.0.0",
    "nome-do-pacote-3": "^1.0.0"
  },
  "devDependencies": {
    "nome-do-pacote-desenvolvimento": "*"
  }
}
```

Outro arquivo obrigatório é o `package-lock.json`, seu objeto é manter rastreada a versão exata de cada pacote que está instalado.
### 2.2 Gerenciador de Pacote (NPM)

Assim, como em outras linguagens, o Node possui um gerenciador de pacotes, chamado `NPM`, que é responsável por instalar, remover, atualizar e publicar módulos. Ele funciona como o Gems no Roby, Maven no Java e pip no Python.

**Exemplos de Comandos:**

`npm install` instala todas as dependências que estiverem no `package.json` e coloca-las na pasta `node_modules`.

`npm update` atualiza todas as dependências que estiverem no `package.json`.

`npm run ---`roda scripts que estiverem no `package.json`.


### 2.3 CommonJS

Os módulos em Node obedecem um sistema chamado `CommonJS`. Esse sistema possui funções que possibilitam interagir entre módulos:

- **require(module):** permite importar módulos.
- **exports.module:** permite exportar módulos.


**Exemplo:**

`dog.js`
```javascript
module.exports = function(){
    console.log("woof")
};
// exporta somente essa funcao anonima
```
`cat.js`
```javascript
exports.meow = function (){
    console.log ("meow");
};
exports.pur = function (){
    console.log ("pur");
};
// atalho utilizando funções anonimas
```

`human.js`
```javascript
module.exports = {
   hi: function(){
      console.log("hi");
   },
   hello: function(){
      console.log("hello");
   }
};
// exportando objeto de forma explicita
```

`app.js`
```javascript
var scoob = require('./dog');
var garfield = require('./cat');
var john = require('./human');

scoob();
garfield.meow();
garfield.pur();
john.hi();
john.hello();

// Terminal
woof
meow
pur
hi
hello
```

