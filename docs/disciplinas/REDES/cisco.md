# Introdução ao Cisco Packet Tracer

--- 

## 1. O que é:

O Cisco Packet Tracer é um simulador de redes desenvolvido pela Cisco que possibilita simular sem precisar do hardware físico.Ele permite criar topologias de rede virtuais, testar configurações e simular o comportamento de dispositivos de rede como:

- Roteadores
- Switches
- Computadores (PCs e laptops)
- Servidores
- Dispositivos móveis

--- 

## 2. Passos básico:

**1. Adicionar dispositivos**

- PC ou Laptop: Simula um computador na rede.
- Switch: Permite conectar múltiplos dispositivos na mesma rede local (LAN).
- Roteador: Permite a comunicação entre redes diferentes (WAN ou sub-redes).

**2. Conectar dispositivos**

- Cabo direto (Copper Straight-Through): PC → Switch, Switch → Roteador
- Cabo cruzado (Copper Cross-Over): PC → PC ou Switch → Switch

**3. Configuração de IP**

- Cada PC deve ter um IP único dentro da mesma rede/sub-rede do switch ou roteador.
- Configure o gateway padrão no PC, apontando para o IP do roteador.

**4. Testar conectividade**

**Por terminal** 

```bash
ping 192.168.1.2   

// vai aparecer algo assim caso der certo
Reply from 192.168.1.2: bytes=32 time<1ms TTL=128
Reply from 192.168.1.2: bytes=32 time<1ms TTL=128
Reply from 192.168.1.2: bytes=32 time<1ms TTL=128
Reply from 192.168.1.2: bytes=32 time<1ms TTL=128

Ping statistics for 192.168.1.2:
    Packets: Sent = 4, Received = 4, Lost = 0 (0% loss),
Approximate round trip times in milli-seconds:
    Minimum = 0ms, Maximum = 0ms, Average = 0ms

```
**Por pacotes**
- Ícone de cartinha em cima.
- Vai aparecer no canto inferior direito se deu certo ou não

## Coisas
- Comunicação entre redes
- Ligar dois routers

--- 

## 3. Comandos básicos de configuração 

### 3.1 Configuração básica

```bash
enable                  // Acessa modo privilegiado
configure terminal      // Acessa modo de configuração global
hostname NOME           // Altera o nome do switch/roteador
banner motd #MENSAGEM#  // Define a mensagem do dia
exit                    // Sai da configuração global
```

### 3.2 Configuração de senha e login

```bash
enable
configure terminal
line console 0           // Acessa a porta de console
password SENHA           // Define a senha
login                    // Força o login
```

### 3.3 Salvando e reiniciando configurações

```bash
do copy running-config startup-config   // Salva as alterações
do reload                              // Reinicia o equipamento

enable
erase startup-config   // Apaga todas as informações salvas
n                     // Não salva ao apagar
```

### 3.4 Ajustes adicionais

```bash
enable
configure terminal
no ip domain lookup    // Desativa a tradução de comandos inválidos
```

## 4. Conectar dois computadores
- Conectar um cabo cross-over via fast-ethernet;
- Colocar um IP em cada um dos pcs (PC - Desktop - Ip Config);
- Ex: 192.168.1.1 e 192.168.1.2;
- Testar conexão;

<p align="center">
  <img src="../../../assets/pngs/46.png" alt="A">
</p>

## 5. Star Topology
- Todos os PCs se conectam e comunicam por um switch;
- Conectar cada PC com o switch com um cabo straight-throught;
- Demora um pouco para estabilizar;
- Colocar os IPs nos computadores;
- Testar a conexão;

<p align="center">
  <img src="../../../assets/pngs/47.png" alt="A">
</p>


## 5. Conexão entre dois switchs
- Criar a star topology 1;
- Criar a star topology 2;
- Conectar os switchs com o cabo cross-over via fast-ethernet;
- Testar a conexão

<p align="center">
  <img src="../../../assets/pngs/48.png" alt="A">
</p>

## Conexão entre switchs com router
- Utilizar router sempre que os switches forem de sub-redes diferentes;
- Criar a star 1 com PCs de Ip 192.168.1.n e default gateway de 192.168.1.1
- Criar a star 2 com PCs de Ip 172.16.1.n e deafult gateway de 172.16.1.1
- Colocar como deafult gateway dos PCs o Ip da outra star;
- Conectar cada switch com o router atraves do gigaBitEthernet
- Conectar um Laptop e conectar no router com o cabo console via RS-232/Console
- Entrar no terminal do laptop e configurar router
    - Acessar config/GigabitEthernet0 e colocar o Ip da star 1;
    - Acessar config/GigabitEthernet0 e colocar o Ip da star 2;
    - Deixar Port Status On nos dois;

``` bash
enable
configure terminal

interface GigabitEthernet0/0/0
ip address 192.168.1.1 255.255.255.0
no shutdown
exit

interface GigabitEthernet0/0/1
ip address 172.16.1.1 255.255.255.0
no shutdown
exit

copy running-config startup-config
reload
```

<p align="center">
  <img src="../../../assets/pngs/49.png" alt="A">
</p>


## 6. Conexão de dois routers

## 7. Simular Server