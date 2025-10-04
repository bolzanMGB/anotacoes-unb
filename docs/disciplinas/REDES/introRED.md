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

**VLAN (Virtual Local Area Network)**: uma LAN lógica criada dentro de um switch físico.

---

### 4 Equipamentos de rede

- **Roteador:** conecta redes distintas.
- **Switch:** conecta dispositivos dentro de uma mesma rede local.
- **Hub:** distribui dados para todos os dispositivos (menos eficiente que switch).
- **Firewall:** controla acessos, protege contra ataques.
- **Access Point:** permite conexões sem fio (Wi-Fi).

---

## 5. Modelos de Arquitetura de Redes

<p align="center">
  <img src="../../../../assets/pngs/44.png" alt="Segmentação com Paginação">
</p>


### 5.1 Modelo OSI 
É um modelo conceitual. Suas camadas são (FERTSAA):

**1. Camada Física:** 

- Transmite bits no meio físico. 
- Hardware, sinal elétrico, bits.
- Exemplo: cabos (UTP, fibra), conectores.

**2. Camada de Enlace de Dados:** 

- Entrega "quadro a quadro" dentro de uma rede local. 
- Dispositivos: pontes, switches.
- Exemplo: Ethernet, Wi-Fi, VLAN.

**3. Camada de Rede:** 

- Faz o encaminhamento entre redes.
- Dispositivos: roteadores;
- Exemplo: IPv4, IPv6.

**4. Camada de Transporte:** 

- Conexões fim-a-fim e portas. 
- Exemplo: ping, TCP, UDP

**5. Camada de Sessão:** 

- Gerencia conexões entre aplicações. 
- Exemplo: RPC.

**6. Camada de Apresentação:** 

- Faz criptografia/compressão. 
- Exemplo: TLS/SSL.

**7. Camada de Aplicação:** 

- Protocolos que o usuário recebe e interage.
- Exemplo: HTTP/HTTPS

---

### 5.2 Modelo TCP/IP 
É o modelo seguido no mundo real. Suas camadas são (RITA):

**1. Acesso à rede (Interface de Rede):**

- Cuida da transmissão física dos dados em uma rede local.
- Como os dados chegam do roteador ao seu PC.
- Define o meio físico usado: cabo Ethernet, Wi-Fi.
- O switch usa endereços MAC para identificar os dispositivos que vão receber os dados/frames.

**2. Internet (Camada de Rede):** 

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

- **IP de Rede**: termina em .0 (ex.: 192.168.1.0) e identifica toda a rede; não deve ser atribuído a um dispositivo.

- **IP de Broadcast**: termina em .255 (ex.: 192.168.1.255) e envia mensagens a todos os dispositivos da rede.

- **IP válido para hosts**:  são os IPs entre 192.168.1.1 e 192.168.1.254 (no exemplo /24). São atribuidos a dispositivos: PCs, roteadores e etc.

- **IP Público X IP Privado**:
    -**Público**: é o IP que identifica a sua rede de internet, entregue pela operadora. Não é algo como 192.168.x.x.
    - **Privado:** é o IP que identifica cada dispositivo dentro da sua rede, distribuido pelo roteador (ex.: 192.168.1.1, 192.168.1.2, 192.168.1.3).

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

- **Bits de rede**: indicam quantas redes podem ser criadas.
- **Bits de host**: indicam quantos dispositivos podem existir em cada rede.

Quanto maior a quantidade de bits de redes, menor a quantidade de hosts. Ou seja, podemos ter um número grande de redes pequenas. 

Quanto menor a quantidade de bits de redes, maior a quantidade de hosts. Ou seja, podemos ter um número pequeno de redes grandes.


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


### 7. **VLAN**:

- É uma técnica de segmentação lógica de rede, que divide uma rede física em várias redes lógicas independentes.
- Cada VLAN funciona como uma sub-rede separada, isolando o tráfego de broadcast de outras VLANs.
- No switch:
    - Você cria as VLANs com um ID e um nome (vlan 10, name Engenharia).

    - Atribui as portas a cada VLAN (interface range fa0/1-5, switchport access vlan 10).

    - Para conectar a várias VLANs ao mesmo cabo (para o router ou outro switch), você configura a porta como trunk (switchport mode trunk).

- No router (ou Layer 3 switch):

    - Criam-se subinterfaces para cada VLAN no link trunk (g0/0/0.1, g0/0/0.2).

  - Cada subinterface recebe um IP correspondente à VLAN e a encapsulação 802.1Q (encapsulation dot1q 10).

  - Para permitir que dispositivos em VLANs diferentes obtenham IP de um servidor DHCP em outra rede, utiliza-se o comando ip helper-address.

- Benefícios:

    - Isolamento de tráfego, aumentando segurança e desempenho.

    - Organização da rede por departamentos ou funções.

    - Facilita o gerenciamento de endereçamento IP e políticas de rede.

### 8. **Servidores**:

**Servidor DNS**: faz a tradução de nomes de domínio em endereços IP.
**Servidor DHCP**: faz uma distribuição de IP automática para os dispositivos da rede.

vlan 20
name vlan A
vlan 30
name vlam V

int g0/0/1
sw mode trunk
sw trunk access vlan all

interface range fa0/1-5
sw access vlan2
interface fa0/6-10
sw access vlan3

int g0/0/0.1
encapsulation dot1q 1
ip add 192.168.1.1 255.255.255.0
ip helper-address 192.168.1.2

int g0/0/0.2
encapsulation dot1q 2
ip add 192.168.20.1 255.255.255.0
ip helper-address 192.168.1.2

int g0/0/0.3
encapsulation dot1q 3
ip add 192.168.30.1 255.255.255.0
ip helper-address 192.168.1.2


Router>enable
Router#config t
r1(config)#line console 0
r1(config-line)#password SENHA
r1(config-line)#login
r1(config-line)#exit
r1(config)#enable secret SENHA
r1(config)#banner motd #aviso#
r1(config)#do copy running-config startup-config
r1(config)#do reload



int g0/0/1
sw access trunk mode
sw access trunk vlan all

vlan 20 name a
vlan 30 name b

int fa0/1-5
sw acces vlan 20


int g0/0/0.1
encalpsilation dot1q 1
ip add


vlan A name a
vlan B

int fa0/1-5
sw access vlan 20

int g0/0/0.1
encapsulation dot1q 1
ip add
ip heloe

