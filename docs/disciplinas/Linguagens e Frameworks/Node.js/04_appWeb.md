# Desenvolvendo aplicações web

## 1. Node Puro

### 1.2 Estrutura básica 

```js
var http = require('http');
var server = http.createServer(function(request, response){
    response.writeHead(200, {"Content-Type": "text/html"});
    response.write("<h1>Hello World!</h1>");
    response.end();
});
server.listen(3000);
```

**Importação do módulo:** Estamos importando um objeto pronto do núcleo do Node.js e o nomeando como `http`. Não estamos instanciando uma classe aqui, apenas trazendo esse objeto utilitário.

**Criação do servidor:** Estamos criando um servidor utilizando a função `createServer()` de dentro desse objeto http.

**Entendendo os argumentos:** Essa função recebe como parâmetro uma outra função (um callback), que por sua vez é executada pelo Node toda vez que alguém acessa o servidor. Essa função interna recebe dois objetos principais como argumentos: o `request` (a requisição que vem de alguém acessando o servidor) e o `response` (a resposta que vamos enviar).

- O Node vai utilizar a ordem dos argumentos para saber quem é quem. Ali, no lugar de response, poderia ser qualquer nome, como banana, por exemplo, desde que seja o segundo argumento.
- Cada um desses objetos injetados pelo Node possui diversas funções embutidas de fábrica.
- No caso do objeto de resposta (response), as três principais funções utilizadas para responder ao cliente são:
    - `writeHead(status, headers)`: Responsável por montar o cabeçalho HTTP (os metadados de controle). 
        - O Status indica o código de status HTTP (o número que diz o que aconteceu com a requisição, por exemplo: 200 é OK, 404 é Not Found). 
        - O Header indica o formato do arquivo da resposta (como text/html para páginas web ou application/json para APIs).
    - `write()`: Função utilizada para escrever o conteúdo do corpo da resposta de fato.
    - `end():` Avisa ao Node que a resposta terminou e que a conexão já pode ser fechada e enviada para o navegador.

**Comportamento das Rotas:** Como o código foi escrito em linha reta e sem nenhuma estrutura de decisão (if/else), nós definimos apenas uma resposta padrão. Por isso, independentemente do endereço (URL) que digitarmos no navegador, mesmo que a rota não exista, o servidor sempre vai ignorar o caminho, carimbar o Status 200 e exibir o "Hello World!".


### 1.2 Criar Rotas

```js
var http = require('http');

var server = http.createServer(function(request, response){
    if (request.url == "/"){
        response.writeHead(200, {"Content-Type": "text/html"});
        response.write("<h1>Página principal</h1>");
    } 
    else if(request.url == "/bemvindo"){
        response.writeHead(200, {"Content-Type": "text/html"});
        response.write("<h1>Bem-vindo :)</h1>");
    }
    else{
        response.writeHead(404, {"Content-Type": "text/html"});
        response.write("<h1>Página não encontrada</h1>");
    }
    response.end();
});
    server.listen(3000, function(){
    console.log('Servidor rodando!');
});
```
Com `request.url` podemos definir rotas através de laços.

### 1.3 Separando HTML do JS

`index.html`
```html
<h1>Hello World</h1>
```

`app.js`
```js
var http = require('http');
var fs = require('fs');

var server = http.createServer(function(request, response){
    fs.readFile(__dirname + '/index.html', function(err, html){
        response.writeHeader(200, {'Content-Type': 'text/html'});
        response.write(html);
        response.end();
        if (erro) throw erro;
        console.log(arquivo);
    });
});

server.listen(3000, function(){
    console.log('Rodando');
});
```

Aqui estamos utilizando o módulo `FS` (File System). E