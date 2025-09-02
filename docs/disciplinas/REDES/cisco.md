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

Use o comando ping entre PCs, PCs e roteadores ou PCs e laptops para verificar se a comunicação funciona.

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

### 3.5 Testando conectividade

```bash
ping 192.168.10.3   // Testa envio e recebimento de pacotes
```

