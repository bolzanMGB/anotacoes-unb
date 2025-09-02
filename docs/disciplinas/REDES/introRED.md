# Introdução Redes de Computadores

---

## 1. O que é:

Conjunto de dois ou mais dispositivos interligados.

Permite compartilhar recursos: arquivos, impressoras, internet, aplicações.

Formada por computadores autônomos conectados via meios de transmissão e protocolos de comunicação.

---

## 2. Importância das Redes

- Compartilhamento e integração de recursos.

- Comunicação ágil e eficiente (e-mails, mensagens, videoconferência).

- Suporte a trabalho remoto e colaborativo.

- Redução de custos e maior produtividade.

---

## 3. Tipos de Rede

**LAN (Local Area Network)**: redes locais (escritórios, casas, escolas).

**MAN (Metropolitan Area Network)**: redes em escala de cidade.

**WAN (Wide Area Network)**: redes de longa distância (ex.: Internet).

**WLAN**: LAN sem fio (Wi-Fi).

**PAN (Personal Area Network)**: dispositivos pessoais (Bluetooth, USB).

---

### 4 Equipamentos de rede

- Roteador: conecta redes distintas.
- Switch: conecta dispositivos dentro de uma mesma rede local.
- Hub: distribui dados para todos os dispositivos (menos eficiente que switch).
- Firewall: controla acessos, protege contra ataques.
- Access Point: permite conexões sem fio (Wi-Fi).

---

## 5. Modelos de Arquitetura de Redes

<p align="center">
  <img src="../../../../assets/pngs/44.png" alt="Segmentação com Paginação">
</p>


### 5.1 Modelo OSI 
É um modelo conceitual. Suas camadas são:

**1. Física:** 

- Transmite bits no meio físico. 
- Hardware, sinal elétrico, bits.
- Exemplo: cabos (UTP, fibra), conectores.

**2. Enlace de Dados:** 

- Entrega "quadro a quadro" dentro de uma rede local. 
- Endereço físco, pontes, switches.
- Exemplo: Ethernet, Wi-Fi, VLAN.

**3. Rede:** 

- Faz o encaminhamento entre redes.
- Exemplo: IPv4, IPv6.

**4. Transporte:** 

- Conexões fim-a-fim e portas. 
- Exemplo: TCP.

**5. Sessão:** 

- Gerencia checkpoints. 
- Exemplo: RPC.

**6. Apresentação:** 

- Faz criptografia/compressão. 
- Exemplo: TLS/SSL.

**7. Aplicação:** 

- Protocolos que o usuário recebe. 
- Exemplo: HTTP/HTTPS

---

### 5.2 Modelo TCP/IP 
É o modelo seguido no mundo real. Suas camadas são:

**1. Acesso à rede (Interface de Rede):**

- Cuida da transmissão física dos dados em uma rede local.
- Como os dados chegam do roteador ao seu PC.
- Define o meio físico usado: cabo Ethernet, Wi-Fi.
- O switch usa endereços MAC para identificar os dispositivos que vão receber os dados/frames.

**2. Internet:** 

- Define o endereçamento lógico (IP) e o roteamento entre redes.
- Faz a comunicação entre meu roteador e o IP de destino.
- Escolhe a melhor rota para o pacote seguir.
- Firewall: protege a rede e controla quem pode se comunicar com quem.

**3. Transporte:** 

- Faz a comunicação fim a fim entre processos (porta origem -> porta destino). Podem ser:
- TCP: confiável (HTTP/HTTPS, email, SSH).
- UDP: rápido e leve (DNS, VoIP, streaming).


**4. Aplicação:** 

- São os protocolos que as aplicações do usuário usam diretamente. Exemplos:
- Web: HTTP/HTTPS.
- Email: SMTP, IMAP, POP3.
- Nomes: DNS.
- Administração: SSH, SNMP.


---

## 6. Endereçamento IP

### 6.1 Definição
Número único que identifica a rede e os dispositivos dentro dela.

- **IP Público:** é o IP que identifica a sua rede de internet, entregue pela operadora.

- **IP Privado:** é o IP que identifica cada dispositivo dentro da sua rede, distribuido pelo roteador.

---

### 6.2 Formato IPv4: 

Os IPs possuem 32 bits, divididos em 4 octetos (X.Y.Z.W).

Cada octeto possui 8 bits, ou seja, valem de 0 a 255.

``` c title="Exemplo: "
X.         Y.         Z.       W.
8 bits     8 bits     8 bits   8 bits
0-255.     0-255.     0-255.   0-255.
```

---

### 6.3 Classes de endereços IPv4

São divisões com máscaras pré-definidas do espaço de IPs, criadas para organizar redes grandes, médias e pequenas.


| Classe | Faixa de IP                 | Máscara padrão      | Bits de rede | Bits de host | Máx. hosts   |Uso típico                                     |
| ------ | --------------------------- | ------------------- | ------------ | ------------ | ------------ | ---------------------------------------------- |
| **A**  | 0.0.0.0   – 127.255.255.255   | 255.0.0.0 (/8)    | 8 bits       | 24 bits      | 16.777.214   |Grandes empresas e ISPs                        |
| **B**  | 128.0.0.0 – 191.255.255.255 | 255.255.0.0 (/16)   | 16 bits      | 16 bits      | 65.534       |Universidades, grandes corporações             |
| **C**  | 192.0.0.0 – 223.255.255.255 | 255.255.255.0 (/24) | 24 bits      | 8 bits       | 254          |Pequenas redes, LAN domésticas                 |
| **D**  | 224.0.0.0 – 239.255.255.255 | —                   | —            | —            | Multicast    |Multicast (envio para múltiplos destinatários) |
| **E**  | 240.0.0.0 – 255.255.255.255 | —                   | —            | —            | Experimental |Experimental, reservado                        |

---

### 6.4 Máscara de sub-rede:

Define qual parte do IP é da rede e qual parte é do host (dispositivos).

**Exemplo:** IP 192.168.1.10/24

- Classe: C
- Rede: primeiros 3 octetos, 192.168.1
- Host: ultimo octeto, 10
- Número máximo de hosts: 0 - 255, ou seja 256 
- Número de hosts usáveis: 256 - 2 = 254 (Endereço de Broadcast e ENdereço de Rede)

---

### 6.5 Sub-redes (Subnetting)

São usadas para dividir uma rede maior em partes menores, mesmo dentro de uma Classe.

Você pega emprestado alguns bits que originalmente eram de host e transforma em bits de rede.

**Benefícios:**

- Melhor para organizar dispositivos, melhorar segurança e desempenho.
- Evitam redes gigantes com milhares de dispositivos.
- Separa departamentos ou tipos de dispositivos.

**Exemplo:** 

Rede original: 192.168.1.0/24 → 254 hosts.

Se pegarmos 2 bits do último octeto para sub-redes, ficamos com:

- Bits de rede: 24 (originais) + 2 (novas sub-redes) = 26 bits → /26
- Cada sub-rede tem 6 bits para hosts → 2^6 - 2 = 62 hosts por sub-rede

Total sub-redes criadas: 2^2 = 4 sub-redes.

**Visualizando os endereços:**

| Sub-rede | Endereço de rede | Primeiro host | Último host   | Broadcast     |
| -------- | ---------------- | ------------- | ------------- | ------------- |
| 1        | 192.168.1.0      | 192.168.1.1   | 192.168.1.62  | 192.168.1.63  |
| 2        | 192.168.1.64     | 192.168.1.65  | 192.168.1.126 | 192.168.1.127 |
| 3        | 192.168.1.128    | 192.168.1.129 | 192.168.1.190 | 192.168.1.191 |
| 4        | 192.168.1.192    | 192.168.1.193 | 192.168.1.254 | 192.168.1.255 |


---

### 6.6 **Ferramentas de diagnóstico**:

**1. ipconfig/ip addr**

Mostra informações de configuração de rede do computador.

Principais informações:

- Endereço IP (IPv4 e IPv6).
- Máscara de sub-rede.
- Gateway padrão (roteador).
- Endereço MAC.
- DNS configurado.


**2. ping**

Testa a conectividade entre dois dispositivos na rede.

O que indica:

- Se há conectividade.
- Tempo de resposta (latência).
- Se há perda de pacotes (problema na rede).