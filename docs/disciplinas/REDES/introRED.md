# Introdução Redes de Computadores

## 1. O que é:

Conjunto de dois ou mais dispositivos interligados.

Permite compartilhar recursos: arquivos, impressoras, internet, aplicações.

Formada por computadores autônomos conectados via meios de transmissão e protocolos de comunicação.

## 2. Importância das Redes

- Compartilhamento e integração de recursos.

- Comunicação ágil e eficiente (e-mails, mensagens, videoconferência).

- Suporte a trabalho remoto e colaborativo.

- Redução de custos e maior produtividade.

## 3. Tipos de Rede

**LAN (Local Area Network)**: redes locais (escritórios, casas, escolas).

**MAN (Metropolitan Area Network)**: redes em escala de cidade.

**WAN (Wide Area Network)**: redes de longa distância (ex.: Internet).

**WLAN**: LAN sem fio (Wi-Fi).

**PAN (Personal Area Network)**: dispositivos pessoais (Bluetooth, USB).

## 4. Arquitetura de Redes

**Modelo OSI (7 camadas)**

- Física
- Enlace de Dados
- Rede
- Transporte
- Sessão
- Apresentação
- Aplicação

**Modelo TCP/IP (4 camadas)**

- Acesso à rede (Interface de Rede)
- Internet
- Transporte
- Aplicação

**Equipamentos de rede**

- Roteador: conecta redes distintas.
- Switch: conecta dispositivos dentro de uma mesma rede local.
- Hub: distribui dados para todos os dispositivos (menos eficiente que switch).
- Firewall: controla acessos, protege contra ataques.
- Access Point: permite conexões sem fio.

## 5. Protocolos de Comunicação

**Definição**: conjunto de regras que padronizam a comunicação entre dispositivos.

**TCP/IP**:

- Protocolo padrão da Internet.
- Exige configuração mínima: endereço IP + máscara de sub-rede.
- Pode incluir gateway e DNS.

**Protocolo comuns**:

- **HTTP/HTTPS**: navegação web.
- **SMTP/IMAP/POP3**: e-mail.
- **FTP/SFTP**: transferência de arquivos.
- **DNS**: tradução de nomes de domínio em IP.

## Endereçamento IP

**O que é IP:**

- Número único que identifica cada dispositivo em uma rede.
- Formato IPv4: X.Y.Z.W (0 a 255).
- Ex.: 192.168.1.1.

- Pirvado

- publico

**Classes de endereços IPv4:**

- Classe A: redes muito grandes.
- Classe B: redes médias.
- Classe C: redes pequenas.
- Classe D: multicast.
- Classe E: experimental.

**Sub-redes (Subnetting)**:

- Dividem uma rede maior em partes menores.
- Máscara de sub-rede define o tamanho da rede.
- Ex.: /24 = 255.255.255.0 → até 254 hosts.

**Ferramentas de diagnóstico**:

- ipconfig (Windows).
- ifconfig / ip addr (Linux).
- ping (testar conectividade).