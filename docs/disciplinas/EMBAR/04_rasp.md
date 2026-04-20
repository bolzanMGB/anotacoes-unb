# Raspberry Pi

## 1. Configuração Inicial
Com base no passo a passo do [GitLab](https://gitlab.com/fse_fga/raspberry-pi/roteiro-de-configuracao-incial)

### 1.1 Baixar o Raspberry Pi Imager
Fazer o download a partir do [repositório da Raspberry Pi](https://github.com/raspberrypi/rpi-imager/releases/tag/v1.9.6)

### 1.1 Baixar o Sistema Rasoberry Pi OS
Fazer o download a partir do [site da Raspberry Pi](https://downloads.raspberrypi.com/raspios_armhf/images/raspios_armhf-2025-12-04/2025-12-04-raspios-trixie-armhf.img.xz)


### 1.2 Configuração da Imagem

1. Abrir o Raspberry Pi Imager

2. Tele Inicial:
- Dispositivo: Raspberry Pi 3.
- Sistema Operacional: clicar em `Use Custom` e escolher o baixado.
- Armazenamento: inserir o cartão de memória no computador e selecioná-lo em `Escolher Armazenamento`.
- Clicar no botão `Seguinte` e clicar em **Editar Definições`.

3. Aba Geral:

    3.1. Configurar usuário e senha como:
    - username: pi
    - password: raspberry

    3.2 Configurar as credenciais de 
    - SSID: FSE-WIFI
    - Senha:

    3.3 Definir o idioma e região
    - Fuso horário: America/São Paulo
    - Disposição de teclado: us

4. Aba Serviços: ativar SSH com autentificação por senha.

5. Gravação de imagem: confirmar as modificações e clicar no botão `Sim`

6. Iniciar e fazer acesso remoto à RaspBerry Pi

1. Insira o SDCard na Raspberry Pi.
2. Connecte o cabo de energia (Micro USB) para ligar a placa.
3. Realizar o acesso remoto via SSH

```bash
# Para realizar o acesso remoto via SSH
ssh pi@rasp<NUMERO_DA_PLACA>.local

# Para desligar a placa
sudo poweroff

```
## 2. Funcionamento do GPIO
A `GPIO` (General Purpose Input/Output) é formada pelos pinos que conectam o processador da Raspberry Pi com o mundo real.

- `Output:` O software envia um sinal elétrico para o pino. Isso serve para acender um LED, ligar um motor ou ativar um relé.
- `Input:` O software "lê" se há eletricidade chegando no pino. Isso serve para saber se alguém apertou um botão ou se um sensor de presença foi ativado.

A Raspberry Pi tem 40 pinos físicos, cuja numeração pode ser conferida no esquema abaixo:

<div style="text-align: center;">
  <img src="../../assets/pngs/109.png" alt="Inserção" />
  <p><em>Detalhamento <a href="https://pinout.xyz/">aqui</a></em></p>
</div>

## 3. Exercícios
